#include "flash_test.h"

#define TEST_ADDR   0x7FF000
#define WRITE_LEN   300         /* 写 300B */
#define ERASE_LEN   256         /* 只擦 256B */
#define DUMP_CHUNK  16          /* 每次调用 dump 16 字节 */
#define WRITE_CHUNK 2           /* 每次调用写 2 字节 */
#define CYCLE_DELAY 20          /* 两次测试周期之间的主循环迭代次数 */

/* 非阻塞状态机: 每次主循环调用只做一小块工作, 立即返回 */
void flash_test_run(void)
{
    static uint8_t  state      = 0;    /* 状态机步骤 */
    static uint16_t idx        = 0;    /* 当前索引进度 */
    static uint16_t delay_cnt  = 0;    /* 周期间延迟计数 */
    uint8_t val;
    uint16_t i;

    switch (state) {

    /* ---- 0: 周期间隔, 让出 CPU 给 UI/按键 ---- */
    case 0:
        if (++delay_cnt < CYCLE_DELAY)
            return;
        delay_cnt = 0;
        LOGI("\r\n=== FLASH TEST CYCLE ===\r\n");
        state = 1;
        idx   = 0;
        /* fall through */

    /* ---- 1: 预擦除 16 个 256B 页 (每次擦 1 页) ---- */
    case 1:
        flash_sector_erase(TEST_ADDR + idx * 256);
        if (++idx >= 16) {
            idx   = 0;
            state = 2;
            LOGI("WRITE 300B AA...\r\n");
        }
        break;

    /* ---- 2: 写入 300 字节 0xAA (每次写 WRITE_CHUNK 字节) ---- */
    case 2:
        for (i = 0; i < WRITE_CHUNK && idx < WRITE_LEN; i++, idx++) {
            val = 0xAA;
            flash_write(TEST_ADDR + idx, &val, 1);
        }
        if (idx >= WRITE_LEN) {
            idx   = 0;
            state = 3;
            LOGI("BEFORE ERASE:\r\n");
        }
        break;

    /* ---- 3: 擦前 dump (每次 dump DUMP_CHUNK 字节) ---- */
    case 3:
        for (i = 0; i < DUMP_CHUNK && idx < WRITE_LEN; i++, idx++) {
            if ((idx & 0x0F) == 0) {
                LOGI("\r\n%c%c%c: ",
                    pt_nibble_to_hex((idx >> 8) & 0xF),
                    pt_nibble_to_hex((idx >> 4) & 0xF),
                    pt_nibble_to_hex(idx & 0xF));
            }
            flash_read(TEST_ADDR + idx, &val, 1);
            LOGI("%c%c ",
                pt_nibble_to_hex(val >> 4),
                pt_nibble_to_hex(val & 0xF));
        }
        if (idx >= WRITE_LEN) {
            LOGI("\r\n");
            idx   = 0;
            state = 4;
        }
        break;

    /* ---- 4: 测试擦除 256B ---- */
    case 4:
        LOGI("ERASE 256B...\r\n");
        flash_sector_erase(TEST_ADDR);
        state = 5;
        break;

    /* ---- 5: 擦后 dump (每次 dump DUMP_CHUNK 字节) ---- */
    case 5:
        for (i = 0; i < DUMP_CHUNK && idx < WRITE_LEN; i++, idx++) {
            if ((idx & 0x0F) == 0) {
                LOGI("\r\n%c%c%c: ",
                    pt_nibble_to_hex((idx >> 8) & 0xF),
                    pt_nibble_to_hex((idx >> 4) & 0xF),
                    pt_nibble_to_hex(idx & 0xF));
            }
            flash_read(TEST_ADDR + idx, &val, 1);
            LOGI("%c%c ",
                pt_nibble_to_hex(val >> 4),
                pt_nibble_to_hex(val & 0xF));
        }
        if (idx >= WRITE_LEN) {
            LOGI("\r\n");
            idx   = 0;
            state = 6;
        }
        break;

    /* ---- 6: 定点检查 4 个字节 ---- */
    case 6:
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
        state = 0;  /* 回到延迟状态, 开始下一轮测试 */
        break;
    }
}
