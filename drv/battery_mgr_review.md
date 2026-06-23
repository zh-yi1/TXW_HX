# battery_mgr 模块审阅与流程说明

> 本文档于 2026-06-23 依据当前代码复核订正。主要修正: 轮询周期 (50ms 而非 500ms)、
> 主循环调用顺序、温度物理来源 (CW1573 单颗 NTC)、过压阈值 (4470mV), 并删除若干
> 已不成立的"已知问题"。

## 1. 模块定位

`battery_mgr` 是 3C 新国标电池安全管理模块，负责：

| 职责 | 数据来源 | 判断方 |
|------|---------|--------|
| 过压/欠压检测与禁用 | CW1573 AFE 电芯电压 | **TFT 本地** |
| 温度计算 (NTC→℃) | CW1573 采集 → TFT 经 0x5C 上报主机 → 主机回传 bat_ntc2 | TFT 本地换算 |
| 温度保护警告 | 主机判定后通过 I2C 下发 ntc_status (0x20) | **主机判定** |
| 异常记录 (Flash) | 电压=本地阈值触发; 温度=随主机过温触发 | TFT 本地 |

> **温度物理拓扑**: 整机只有 **单颗 NTC**, 接在 TFT 侧的 CW1573 上。CW1573 读出阻值 →
> TFT 通过 0x5C 上报主机 → 主机再以 bat_ntc2 (0x25) 回传给 TFT 用于显示换算;
> 主机另据自身阈值判定后用 ntc_status (0x20) 通知 TFT 是否进入保护。TFT 不做本地温度阈值判断。

## 2. 主循环调用链

```
main() while(1):
  cw1573_proc()          → 读 CW1573 电芯电压/NTC/电流 (500ms, CW1573_POLL_MS)
  i2c_slave_proc()       → apply_host_data(): 主机数据 → ui_data  (先于 battery_mgr)
  battery_mgr_proc()     → ★ 本模块: OV/UV 检测 + 温度换算 + 异常记录 (50ms, BAT_MGR_POLL_MS)
  battery_mgr_sync_to_ui → battery_mgr getter → ui_data 同步
  ui_proc()              → 显示
```

**关键时序**: 主循环顺序为 `cw1573_proc → i2c_slave_proc → battery_mgr_proc`(见 main.c),
因此 `battery_mgr_proc()` 读到的是**当轮**已更新的 `ui_data.bat_ntc2 / ntc_status`, 无跨轮延迟。
(注: CW1573 寄存器本身每 500ms 才被 cw1573_proc 刷新一次, 故 NTC 数值有效更新粒度为 500ms,
温度变化慢可接受。)

## 3. battery_mgr_proc() 详细流程

```
battery_mgr_proc()                   50ms 周期 (BAT_MGR_POLL_MS)
│
├─ CW1573 未就绪? ───→ return            (见 7.7: 会连带跳过温度段)
├─ 距上次不足 50ms? ───→ return
├─ 已被禁用? ───→ return                  (OV/UV 锁死, 需重新上电; 见 7.3)
│
├─ cw1573_calc_data()              原始数据 → 工程值 (mV, mA, Ω)
│
├─ [1] 温度计算 (TEMP_NTC2_ONLY=1: 仅用 bat_ntc2)
│   ├─ bat_ntc2 ≠ 0 → ntc_resistance_to_temp() → temperature_01c
│   └─ bat_ntc2 = 0 → 保持上次温度
│   注: 物理单颗 NTC 接在 CW1573, TFT 经 0x5C 上报主机, 主机回传 bat_ntc2
│
├─ [2] detect_chg_state()          USB端口状态 → 充电/放电/静置
│
├─ [3] check_hour_commit()         每小时提交 Flash 异常记录
│
├─ [4] 逐电芯检测 (CW1573 本地)
│   for each cell:
│   ├─ 4.1 V < 1.50V 持续 5s → 欠压禁用
│   ├─ 4.2 V > 4.60V 持续 1s → 过压禁用
│   ├─ 4.3 V > 4.47V (BAT_OV_PROT_MV) → 更新过压保护记录(RAM最差值)
│   └─ 4.4 欠压保护 V < 2.72V 进入 / V > 3.00V 恢复 (仅非充电)
│
├─ [5] 温度警告/保护 (主机 ntc_status, 协议 §4.3 0x20)
│   解析 BIT[1:0]=BAT_NTC1, BIT[3:2]=BAT_NTC2   (PCB_NTC1/2 未检查, 见 7.8)
│   00=正常  01=低温保护  02=高温保护
│   → g_bat.warning + 切 PAGE_OVER_TEMP/PAGE_LOW_TEMP
│
└─ [6] 温度异常记录 (随 [5] 过温触发, 写本地换算的温度值)
    首次进入过温: 立即 force 写 Flash + abnormal_log_temperature_commit + 开启 1h 计时
    之后每小时由 check_hour_commit() 提交一次本小时 RAM 最差值
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
  R = 0       → 保持上次值 (尚未收到数据)
```

纯定点运算, 无浮点, 适合 Cortex-M0 (无 FPU)。

## 5. 过压/欠压检测 (TFT 本地)

| 条件 | 阈值 | 持续时间 | 动作 |
|------|------|---------|------|
| 过压保护记录 | V > 4.47V (BAT_OV_PROT_MV) | 即时 | 更新 RAM 最差值 |
| 过压保护恢复 | V < 4.40V | 持续 5s | 清除保护 |
| 过压禁用 | V > 4.60V | 1s (20轮×50ms) | disabled=1, reason=OV |
| 欠压禁用 | V < 1.50V | 5s (100轮×50ms) | disabled=1, reason=UV |
| 欠压保护进入 | V < 2.72V (非充电) | 1s | 进 PAGE_SHORT_CIRCUIT |
| 欠压保护恢复 | V > 3.00V 或充电中 | 5s | 清除 |

禁用后 `battery_mgr_proc()` 直接 return, 需重新上电恢复。

> 计时换算宏: `BAT_MGR_POLL_CNT(s) = s × 1000 / BAT_MGR_POLL_MS = s × 20`,
> 即 1s=20 次、5s=100 次轮询。早期文档误按 500ms 估算, 结论不成立。

## 6. 数据同步 (battery_mgr → ui_data)

在主循环的 sync block 中:

```c
ui_data.cell_voltage_mv[i]  = battery_mgr_cell_voltage_mv(i);
ui_data.bat_temperature     = battery_mgr_temperature_01c();
ui_data.disable_flag        = battery_mgr_is_disabled();
ui_data.abnormal_volt_count = abnormal_log_voltage_count();
ui_data.abnormal_temp_count = abnormal_log_temperature_count();
```

> **死数据提醒**: `ui_data.warning` 由 `i2c_slave_proc()` → `apply_host_data()` 每轮写入,
> 但全工程**没有任何地方读取它**(过温页显示走 `cur_page=PAGE_OVER_TEMP` + `battery_mgr_get_warning_chg_state()`)。
> 同理 `battery_mgr_get_warning()` 也是**定义了但从未被调用**。两者皆为冗余, 可清理。

## 7. 已知问题 / 待确认

### 7.1 欠压/过压计时 (已核实, 非问题)

轮询周期为 50ms (BAT_MGR_POLL_MS), `BAT_MGR_POLL_CNT(s) = s×20`:
- 欠压禁用 `BAT_UV_DISABLE_S=5 → 100 次 × 50ms = 5s` ✓
- 过压禁用 `BAT_OV_DISABLE_S=1 → 20 次 × 50ms = 1s` ✓

(早期文档误按 500ms 估算得出 "2.5s" 的结论, 实际代码正确。)

### 7.2 OV/UV 计时公式 (已统一, 非问题)

代码已统一使用 `BAT_MGR_POLL_CNT(s)` 宏换算秒数→轮询次数, 无需手写系数。

### 7.3 OV/UV 禁用后 warning 冻结 (低优先级, 当前无影响)

`battery_mgr_proc()` 在 `if (g_bat.disabled) return;` 处提前返回, 第 [5] 段不执行,
`g_bat.warning` 停在禁用前的值。但因 `battery_mgr_get_warning()` 目前无调用点, 该冻结**无实际影响**。
若将来启用该 getter, 需在禁用态显式处理。此外过温提示页本身靠 ui.c 的 5s 定时切走, 不会卡死。

### 7.4 多电芯同时异常时 disable_reason 可能被覆盖

`for` 循环不 break, 若电芯0触发 UV、电芯1又触发 OV, `disable_reason` 会被后者覆盖。
后续因 `disabled=1` 直接 return 不影响功能, 但记录的根因可能不准确。

### 7.5 负温度存储为 uint16_t

`abnormal_log_temperature_update()` 的 value 参数是 `uint16_t`, 温度为负时 (如 -20℃ = -200)
会转为大整数 (65336), 读取日志需注意符号。过温路径 (热=正温度) 不触发此问题。

### 7.6 cw1573_calc_data() 重复调用 (低优先级)

`battery_mgr_calc_data()` 在 `battery_mgr_proc()` 与 `i2c_slave_proc()→pull_sensor_data()` 各调一次,
顺带把全局 `g_bat_high_temp` 算两遍。纯计算无副作用, 但浪费 CPU; 且 `disabled`/未就绪时
`battery_mgr_proc` 提前 return, `g_bat_high_temp` 只靠 i2c_slave 那次刷新。

### 7.7 ⚠ CW1573 未就绪会连带禁用整个温度段 (需确认是否有意)

`battery_mgr_proc()` 开头 `if (!cw1573_is_ready()) return;` 在第 [5] 温度段**之前**。
后果: 主机下发 `ntc_status=过温` 时, 只要本地 CW1573 没就绪, TFT **既不切 PAGE_OVER_TEMP, 也不写异常日志**,
保护被静默吞掉。因温度物理源就是 CW1573, 主机此时也是旧数据——但若某形态 CW1573 一直配置不上,
温度保护将永久失效。请确认是否接受此耦合。

### 7.8 PCB NTC 保护位未检查 (需确认)

第 [5] 段与 `apply_host_data()` 均为 `for (i = 0; i < 2; i++)`, 只解析 BAT_NTC1 (BIT[1:0])、
BAT_NTC2 (BIT[3:2]); **PCB_NTC1/2 (BIT[5:4]、[7:6]) 忽略**。若板端过温也需提示, 这里覆盖不全。
两处一致故不会状态冲突。请确认是否故意。

### 7.9 ntc_status 保留值 0x03 被当 "正常"

2-bit 域解析只判 `==0x02`/`==0x01`, 值为 3 (保留) 时 over/low 均不置位 → 当正常。
主机若误发 0x03 会掩盖保护。fail-safe 方向是否应 "保持上一次" 而非 "正常", 可考虑。

### 7.10 g_bat_high_temp 注释方向 (已修复)

CW1573 侧 `g_bat_high_temp = (rntc_ohm <= 26000Ω)`, 代码正确 (NTC 阻值越低越热, 26kΩ≈57℃)。
原 cw1573.h / cw1573.c 注释误写为 `>= 26000Ω`, 已订正。

## 8. 内存占用

| 项目 | 位置 | 大小 |
|------|------|------|
| `ntc_rnom_table[21]` | Flash (.rodata) | 84 bytes |
| `g_bat` (battery_mgr_ctx_t) | RAM (.bss) | ~92 bytes (含 5 个 uint32 计时数组) |
| NTC 插值临时变量 | 栈 | ~20 bytes |

总计 RAM 占用 ~110 bytes, 符合 4KB SRAM 约束。

## 9. 阈值参数速查

| 宏 | 值 | 含义 |
|----|----|------|
| `BAT_OV_PROT_MV` | 4470 | 过压保护记录阈值 mV |
| `BAT_OV_RECOVER_MV` | 4400 | 过压保护恢复阈值 mV (滞回) |
| `BAT_OV_DISABLE_MV` | 4600 | 过压禁用阈值 mV |
| `BAT_UV_DISABLE_MV` | 1500 | 欠压禁用阈值 mV |
| `BAT_OV_DISABLE_S` | 1 | 过压禁用持续 s (20 次×50ms) |
| `BAT_UV_DISABLE_S` | 5 | 欠压禁用持续 s (100 次×50ms) |
| `BAT_UV_PROT_MV` | 2720 | 欠压保护记录阈值 mV |
| `BAT_UV_RECOVER_MV` | 3000 | 欠压保护恢复阈值 mV (滞回) |
| `BAT_MGR_POLL_MS` | 50 | battery_mgr 轮询周期 ms |
| `CW1573_POLL_MS` | 500 | CW1573 采样周期 ms (cw1573 模块) |
| `NTC_TEMP_MIN_C` | -20 | NTC 温度下限 ℃ |
| `NTC_TEMP_MAX_C` | 80 | NTC 温度上限 ℃ |

> 注: 温度保护**无本地阈值宏**, 完全由主机 `ntc_status` (0x20) 触发;
> 本地换算的温度仅用于显示与异常日志数值。
> CW1573 侧另有 `g_bat_high_temp` (rntc_ohm ≤ 26000Ω ≈ 57℃), 用于 key.c 抑制唤醒, 与本模块独立。
