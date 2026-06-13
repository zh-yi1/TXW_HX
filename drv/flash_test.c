#include "flash_test.h"

#define TEST_ADDR 0x7FF000
#define WRITE_LEN 300 /* 写 300B */
#define ERASE_LEN 256 /* 只擦 256B */

static void dump_range(uint32_t addr, uint16_t len)
{
    uint8_t val;
    uint16_t i;
    for (i = 0; i < len; i++)
    {
        if ((i & 0x0F) == 0)
        {
            LOGI("\r\n%c%c%c: ",
                pt_nibble_to_hex((i >> 8) & 0xF),
                pt_nibble_to_hex((i >> 4) & 0xF),
                pt_nibble_to_hex(i & 0xF));
        }
        flash_read(addr + i, &val, 1);
        LOGI("%c%c ",
            pt_nibble_to_hex(val >> 4),
            pt_nibble_to_hex(val & 0xF));
    }
    LOGI("\r\n");
}

void flash_test_run(void)
{
    uint8_t val;
    uint16_t i;

    /* 1. 先擦净 16 个 256B 页 (覆盖 4KB 扇区), 再写满 300B 全是 0xAA */
    LOGI("PRE-ERASE 16x256B...\r\n");
    for (i = 0; i < 16; i++)
        flash_sector_erase(TEST_ADDR + i * 256);

    LOGI("WRITE 300B AA...\r\n");
    for (i = 0; i < WRITE_LEN; i++)
    {
        val = 0xAA;
        flash_write(TEST_ADDR + i, &val, 1);
    }

    /* 2. 擦前 dump */
    LOGI("BEFORE ERASE:\r\n");
    dump_range(TEST_ADDR, WRITE_LEN);

    /* 3. 只擦 256B */
    LOGI("ERASE 256B...\r\n");
    flash_sector_erase(TEST_ADDR);

    /* 4. 擦后 dump */
    LOGI("AFTER ERASE:\r\n");
    dump_range(TEST_ADDR, WRITE_LEN);

    /* 5. 定点检查 */
    LOGI("---\r\n[0]=");
    flash_read(TEST_ADDR, &val, 1);
    LOGI("%c%c", pt_nibble_to_hex(val >> 4), pt_nibble_to_hex(val & 0xF));

    LOGI(" [255]=");
    flash_read(TEST_ADDR + 255, &val, 1);
    LOGI("%c%c", pt_nibble_to_hex(val >> 4), pt_nibble_to_hex(val & 0xF));

    LOGI(" [256]=");
    flash_read(TEST_ADDR + 256, &val, 1);
    LOGI("%c%c", pt_nibble_to_hex(val >> 4), pt_nibble_to_hex(val & 0xF));

    LOGI(" [299]=");
    flash_read(TEST_ADDR + 299, &val, 1);
    LOGI("%c%c", pt_nibble_to_hex(val >> 4), pt_nibble_to_hex(val & 0xF));

    LOGI("\r\nDONE\r\n");
}
