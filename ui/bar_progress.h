#ifndef __BAR_PROGRESS_H__
#define __BAR_PROGRESS_H__

#include "flash_image_addr.h"

#define BAR_PROGRESS_W   240
#define BAR_PROGRESS_H   4
#define CHARGING_ICON_W  72
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
