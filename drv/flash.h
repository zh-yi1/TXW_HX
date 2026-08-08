#ifndef __FLASH_H_
#define __FLASH_H_

#include "global_define.h"

#define READ_BUFFER_MAX		(1024)
/* DMA 完成等待上限 (循环次数, 非时间). 原值 5000 约 0.5~1ms, 而一次 864 字节
   传输本身就要 0.6ms 左右 —— 阈值和传输时间同量级, 正常传输也会被判超时并
   触发重试, 重试的数据一旦错位就是屏上的残条。放宽到 10 万次 (约 10~20ms),
   仍远小于任何真实故障的等待 */
#define FLASH_DMA_TIMEOUT	(100000U)
#define FLASH_UNBUSY_TIMEOUT	(50000U)
#define FLASH_WEL_DELAY		(100U)

md_status_t flash_read(uint32_t addr, unsigned char *buf, uint16_t size);
md_status_t flash_write(uint32_t addr, unsigned char *buf, uint16_t size);
md_status_t flash_page_erase(uint32_t addr);
uint32_t flash_read_id(void);
md_status_t flash_wait_unbusy(void);

void flash_read_buf(uint32_t addr, uint8_t* read_buf, uint16_t size);
md_status_t flash_read_dma(uint32_t addr, unsigned char *buf, uint16_t size);

#endif
