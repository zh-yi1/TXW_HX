# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

基于 **Eastsoft ES32F0100TF**（Cortex-M0，32KB Flash，4KB SRAM，48MHz）的**移动电源显示面板**裸机固件。设备作为 **I2C 从机**，接收主机 MCU 发送的电池数据（SOC、电压、温度、循环次数、健康度等），在 135x240 TFT LCD（ST7789 兼容）上渲染显示，位图资源存储在外部 SPI NOR Flash 中。

## 构建系统

- **Keil MDK-ARM (uVision 5)** — 主要 IDE。工程文件：`../prj/base.uvprojx`。编译器：ARMCC V5.06。构建输出：`../prj/Objects/`（`.axf`、`.hex`）。
- **SCons** — 命令行构建备选。在 `../prj/` 目录下运行。`SConstruct` 自动向上查找 ES32 SDK 根目录，支持 ARMCC、GCC（mingw）和 IAR 工具链。
- **清理**：`../CleanTarget.bat` 删除所有构建产物。

## 代码架构

### 入口与主循环

[main.c](main/main.c) — `main()` 先调用 `sys_init()` 一次性初始化（时钟 48MHz HRC、GPIO、SPI、LCD、I2C、DMA、Flash），然后死循环调用 `ui_proc()`。无 RTOS；时序由 [irq.c](main/irq.c) 中的 SysTick ISR 驱动，通过级联计数器产生 1ms→10ms→100ms 的软件定时标志位（`FUNC_VAR_WORK_TICK`）。

### 头文件引用链

所有 `.c` 文件统一 `#include "global_define.h"` —— 这是唯一的引用入口，依次包含 `md_conf.h`（MD 外设模块选择）、所有 `drv/*.h` 和所有 `ui/*.h`。

### 驱动层 (`drv/`)

- **[lcd.c](drv/lcd.c)** — TFT LCD 底层驱动：ST7789 指令序列、SPI 像素写入（支持轮询和 DMA 辅助）、8 位色彩模式。
- **[flash.c](drv/flash.c)** — 外部 SPI NOR Flash 读写擦除驱动。位图资源通过 `flash_read_words()` 读取，地址定义在 [flash_addr.h](ui/flash_addr.h)。
- **[iic.c](drv/iic.c)** — I2C 从机驱动。寄存器映射表（`iic_reg_map_t`）定义约 48 个寄存器槽位：电池 SOC、端口功率、温度、循环次数、健康度、语言、计时器等。主机数据缓存于 `ui_ctrl.iic_data`。
- **[dma.c](drv/dma.c)** — SPI TX（Ch0）和 RX（Ch1）的 DMA 配置，用于加速 Flash→LCD 像素传输。
- **[timer.c](drv/timer.c)** — AD16C4T 定时器 Ch2 PWM 输出（PA4），用于 LCD 背光亮度控制（0-100% 占空比，平滑过渡）。
- **[ui.c](drv/ui.c)** — 显示控制器：LCD/Flash 控制引脚 GPIO 初始化、SPI 初始化、`ui_proc()` 分发到当前页面处理函数。

### UI 层 (`ui/`)

每个页面是一个三步状态机：`DISP_STEP_REFLASH`（刷新数据）→ `DISP_STEP_DISP`（渲染）→ `DISP_STEP_WAITCMD`（空闲等待）。页面包括：电池 SOC 环形图（`bat_soc.c`）、电池信息（`bat_info.c`）、屏幕休眠设置（`off_time.c`）、亮度设置（`brightness.c`）、USB-C1 端口设置（`c1_port.c`）、保护/错误显示（`protect.c`）。位图布局描述符在 `ui_array.c`。

### 库 (`lib/`)

- **CMSIS-CORE** — Cortex-M0 核心头文件及 `core_cm0.c`（SysTick、NVIC 操作函数）。
- **MD (Micro Driver)** — 厂商外设库（`md_gpio.*`、`md_spi.*`、`md_dma.*`、`md_i2c.*`、`md_timer.*`、`md_cmu.*` 等），位于 `inc/` 和 `src/`。寄存器定义在 `reg/`。
- **启动文件** — `startup_es32f010x.s`（Keil/ARMCC）和 `startup_es32f0283.s`（IAR），设置向量表，依次调用 `SystemInit()` 和 `main()`。

### GPIO 引脚分配（全部在 GPIOA）

| 引脚 | 功能 |
|------|------|
| PA1  | LCD_BLK（背光使能） |
| PA3  | LCD_CS（SPI 片选） |
| PA4  | 背光 PWM（AD16C4T Ch2） |
| PA5/6 | I2C1 SCL/SDA |
| PA7  | LCD_RST |
| PA8  | LCD_RS（数据/命令） |
| PA9  | FLASH_CS |
| PA10/11/12 | SPI0 CLK/MOSI/MISO |

## 关键约束

- **4KB SRAM** — 无大缓冲区，无动态内存分配。位图数据从 Flash 直接流式传输到 LCD。
- **无测试框架** — 验证仅在实际硬件上进行。
- **I2C 从机协议** — 主机 MCU 控制显示页面并下发所有数据，本设备为纯显示外设。
- **多语言** — 位图资源在 Flash 中分别存储中文和英文两套版本，通过主机下发的 `language_set` 选择。
