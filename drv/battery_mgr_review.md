# battery_mgr 模块审阅与流程说明

## 1. 模块定位

`battery_mgr` 是 3C 新国标电池安全管理模块，负责：

| 职责 | 数据来源 | 判断方 |
|------|---------|--------|
| 过压/欠压检测与禁用 | CW1573 AFE 电芯电压 | **TFT 本地** |
| 温度计算 (NTC→℃) | 主机(020) I2C 下发 NTC 阻值 | TFT 本地换算 |
| 温度保护警告 | 主机(020) I2C 下发 ntc_status | **主机判定** |
| 异常记录 (Flash) | 本地温度/电压 + 阈值 | TFT 本地 |

## 2. 主循环调用链

```
main() while(1):
  cw1573_proc()          → 读取 CW1573 电芯电压/NTC/电流 (500ms)
  battery_mgr_proc()     → ★ 本模块: OV/UV 检测 + 温度换算 + 异常记录
  i2c_slave_proc()       → apply_host_data(): 主机数据 → ui_data
  [sync block]           → battery_mgr getter → ui_data 同步
  ui_proc()              → 显示
```

**关键时序**: `battery_mgr_proc()` 在 `i2c_slave_proc()` **之前**运行，因此读到的 `ui_data.bat_ntc1/ntc_status` 是上一轮循环的值（延迟 ≤500ms，温度变化慢可接受）。

## 3. battery_mgr_proc() 详细流程

```
battery_mgr_proc()                   500ms 周期
│
├─ CW1573 未就绪? ───→ return
├─ 距上次不足 500ms? ───→ return
├─ 已被禁用? ───→ return          (OV/UV 锁死, 需重新上电)
│
├─ cw1573_calc_data()              原始数据 → 工程值 (mV, mA, Ω)
│
├─ [1] 温度计算
│   ├─ bat_ntc1 ≠ 0 → ntc_resistance_to_temp() → t1
│   ├─ bat_ntc2 ≠ 0 → ntc_resistance_to_temp() → t2
│   └─ temperature_01c = max(t1, t2)  取较高者(最坏情况)
│       (单 NTC 有效则只用该值, 双无效保持上次)
│
├─ [2] detect_chg_state()          USB端口状态 → 充电/放电/静置
│
├─ [3] check_hour_commit()         每小时提交 Flash 异常记录
│
├─ [4] 逐电芯检测 (CW1573 本地)
│   for each cell:
│   ├─ 4.1 V < 1.50V 持续 5s → 欠压禁用
│   ├─ 4.2 V > 4.60V 持续 1s → 过压禁用
│   └─ 4.3 V > 4.50V → 更新过压保护记录(RAM最差值)
│
├─ [5] 温度警告 (主机 ntc_status)
│   解析 BIT[1:0]=BAT_NTC1, BIT[3:2]=BAT_NTC2
│   00=正常  01=低温保护  02=高温保护
│   → g_bat.warning
│
└─ [6] 温度异常记录 (本地温度 > 阈值 → Flash)
    充电时 >50.0℃ / 放电时 >60.0℃
```

## 4. NTC 温度换算

### 4.1 查找表

MF52-104F3950FA 热敏电阻, R25=100KΩ, B25/50=3950K, 数据取自 `电阻.md`:

```
-20℃: 939364Ω  ──┐
-15℃: 710392Ω    │
-10℃: 541619Ω    │
 -5℃: 416259Ω    │  R 随 T 升高单调递减
  0℃: 322418Ω    │
  5℃: 251623Ω    │
 10℃: 197801Ω    │
 ...   ...       │  步进 5℃, 共 21 个点
 70℃:  17063Ω    │
 75℃:  14326Ω    │
 80℃:  12076Ω  ──┘
```

表体 `static const` 存放于 Flash (.rodata), **不占用 4KB SRAM**。

### 4.2 插值算法

```
对阻值 R, 在表中找到区间 R[i+1] < R ≤ R[i]:
  T_01c = (-200) + i×50 + 50×(R[i] - R) / (R[i] - R[i+1])

边界:
  R ≤ 12076Ω  → 钳位 80.0℃
  R ≥ 939364Ω → 钳位 -20.0℃
  R = 0       → 保持上次值 (主机未下发)
```

纯定点运算, 无浮点, 适合 Cortex-M0 (无 FPU)。

## 5. 过压/欠压检测 (TFT 本地)

| 条件 | 阈值 | 持续时间 | 动作 |
|------|------|---------|------|
| 过压保护记录 | V > 4.50V | 即时 | 更新 RAM 最差值 |
| 过压禁用 | V > 4.60V | 1s (2轮) | disabled=1, reason=OV |
| 欠压禁用 | V < 1.50V | 5s | disabled=1, reason=UV |

禁用后 `battery_mgr_proc()` 直接 return, 需重新上电恢复。

## 6. 数据同步 (battery_mgr → ui_data)

在主循环的 sync block 中:

```c
ui_data.cell_voltage_mv[i]  = battery_mgr_cell_voltage_mv(i);
ui_data.bat_temperature = battery_mgr_temperature_01c();
ui_data.disable_flag        = battery_mgr_is_disabled();
ui_data.abnormal_count      = abnormal_log_voltage_count()
                            + abnormal_log_temperature_count();
```

注意: `ui_data.warning` 由 `i2c_slave_proc()` → `apply_host_data()` 直接设置 (更实时), 不与 `battery_mgr_get_warning()` 同步, 但两者来源相同 (`ntc_status`), 1 轮内收敛。

## 7. 已知问题

### 7.1 欠压计时精度 (低优先级)

`BAT_UV_DISABLE_S = 5` 但 `uv_seconds` 每 500ms 自增 1, 实际持续 2.5s (5×500ms) 就触发, 而非 5s.

**建议修复**:
```c
#define BAT_UV_DISABLE_S  10U   /* 10 × 500ms = 5s */
```
或在判断处改为:
```c
if (g_bat.uv_seconds[i] * (BAT_MGR_POLL_MS / 1000) >= BAT_UV_DISABLE_S)
```

### 7.2 OV 计时公式可简化 (低优先级)

当前:
```c
if (g_bat.ov_seconds[i] * (BAT_MGR_POLL_MS / 100) >= BAT_OV_DISABLE_S * 10)
```
等价于 `ov_seconds >= 2`, 建议直接写:
```c
#define BAT_OV_DISABLE_CNT  ((BAT_OV_DISABLE_S * 1000U) / BAT_MGR_POLL_MS)  /* 2 */
if (g_bat.ov_seconds[i] >= BAT_OV_DISABLE_CNT)
```

### 7.3 OV/UV 禁用后 warning 冻结

OV/UV 禁用后不再更新 `g_bat.warning`（代码中 `if (!g_bat.disabled)` 跳过），导致 `battery_mgr_get_warning()` 返回的是禁用前的温度警告，而非反映当前禁用状态。

**建议**: 在 `battery_mgr_get_warning()` 中检查 `disabled` 状态，或 OV/UV 禁用时显式设置一个专用警告值。

### 7.4 多电芯同时异常时 disable_reason 可能被覆盖

`for` 循环中不会 break, 若电芯0触发了UV 禁用电芯1又触发了OV, `disable_reason` 最终会是 OV（后者覆盖）。虽然后续因为 `disabled=1` 直接 return 不影响功能, 但记录的根因可能不准确。

### 7.5 负温度存储为 uint16_t

`abnormal_log_temperature_update()` 的 value 参数是 `uint16_t`, 当温度为负时 (如 -20℃ = -200 0.1℃) 转换为大整数 (65336), 读取日志时需注意符号解释。

### 7.6 cw1573_calc_data() 重复调用

每个主循环中 `cw1573_calc_data()` 被调用 3 次:
1. `cw1573_proc()` (推测)
2. `battery_mgr_proc()` 
3. `i2c_slave_proc()` → `pull_sensor_data()`

功能上无害 (纯计算, 无副作用), 但浪费 CPU。可考虑在 `battery_mgr_proc()` 中去除此调用。

## 8. 内存占用

| 项目 | 位置 | 大小 |
|------|------|------|
| `ntc_rnom_table[21]` | Flash (.rodata) | 84 bytes |
| `g_bat` (battery_mgr_ctx_t) | RAM (.bss) | ~24 bytes |
| NTC 插值临时变量 | 栈 | ~20 bytes |

总计 RAM 占用 < 50 bytes, 符合 4KB SRAM 约束。

## 9. 阈值参数速查

| 宏 | 值 | 含义 |
|----|----|------|
| `BAT_OV_PROT_MV` | 4500 | 过压保护记录 mV |
| `BAT_OV_DISABLE_MV` | 4600 | 过压禁用 mV |
| `BAT_UV_DISABLE_MV` | 1500 | 欠压禁用 mV |
| `BAT_OV_DISABLE_S` | 1 | 过压禁用持续时间 s |
| `BAT_UV_DISABLE_S` | 5 | 欠压禁用持续时间 s |
| `BAT_OT_CHG_THRESH` | 500 | 充电过温记录 50.0℃ |
| `BAT_OT_DSG_THRESH` | 600 | 放电过温记录 60.0℃ |
| `BAT_MGR_POLL_MS` | 500 | 轮询周期 ms |
| `NTC_TEMP_MIN_C` | -20 | NTC 温度下限 ℃ |
| `NTC_TEMP_MAX_C` | 80 | NTC 温度上限 ℃ |
