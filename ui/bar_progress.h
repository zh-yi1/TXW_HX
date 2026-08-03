#ifndef __BAR_PROGRESS_H__
#define __BAR_PROGRESS_H__

#include "flash_image_addr.h"

#define BAR_PROGRESS_W   240
#define BAR_PROGRESS_H   4
/* 粒子图标宽度蓝橙不同 (由 stride 反算: (2082-66)/14=144B/行 → 72px;
   (738-66)/14=48B/行 → 24px), 擦除必须按当前颜色的实际宽度算 */
#define CHARGING_ICON_W_BLUE    72
#define CHARGING_ICON_W_ORANGE  24
#define CHARGING_ICON_W  CHARGING_ICON_W_BLUE   /* 兼容旧用法, 指蓝色 */
#define CHARGING_ICON_H  14
#define BLUR_W           240
#define BLUR_H           14

/* progress bar: 100 frames, stored linearly in external flash.
   Address = FLASH_ADDR_BAR_PROGRESS_BASE + (bat - 1) * FLASH_STRIDE_BAR_PROGRESS */

/* ===== 充电动画粒子效果 (可通过 md_conf.h 的 ENABLE_CHARGE_ANIM 裁剪) =====
   All frames stored linearly in external flash:
     charging_blue_up:      FLASH_ADDR_CHARGING_BLUE_UP_BASE      + f  * 2082
     charging_blue_down:    FLASH_ADDR_CHARGING_BLUE_DOWN_BASE    + f  * 2082
     charging_orange_up:    FLASH_ADDR_CHARGING_ORANGE_UP_BASE    + f  * 738
     charging_orange_down:  FLASH_ADDR_CHARGING_ORANGE_DOWN_BASE  + f  * 738
     blur_up:               FLASH_ADDR_BLUR_UP_BASE              + idx * 6786
     blur_down:             FLASH_ADDR_BLUR_DOWN_BASE            + idx * 6786
================================================================= */

#endif /* __BAR_PROGRESS_H__ */
