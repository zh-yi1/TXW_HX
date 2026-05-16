#ifndef __FLASH_H_
#define __FLASH_H_

#include "global_define.h"

#define READ_BUFFER_MAX		(1024)

md_status_t flash_read(uint32_t addr, unsigned char *buf, uint16_t size);
md_status_t flash_write(uint32_t addr, unsigned char *buf, uint16_t size);
md_status_t flash_sector_erase(uint32_t addr);
uint32_t flash_read_id(void);
md_status_t flash_wait_unbusy(void);

void flash_read_buf(uint32_t addr, uint8_t* read_buf, uint16_t size);
md_status_t flash_read_dma(uint32_t addr, unsigned char *buf, uint16_t size);

#endif
