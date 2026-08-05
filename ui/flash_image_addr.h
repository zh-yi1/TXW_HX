/*
 * flash_image_addr.h — Auto-generated, do not edit.
 *
 * P25Q64SH Flash Image Address Map (64 Mb = 8 MB)
 * Sector size: 4096 bytes (4 KB)
 *
 * Images:       293
 * Categories:   196
 * Flash used:   1956930 bytes (1911.1 KB)
 * Sectors used: 478 / 2048
 * Capacity:     8192 KB (8 MB)
 *
 * Category layout:
 *   1800_S_BLUE                          base=0x000000  stride=6338   count=1     sectors=[0 – 1]
 *   1800_S_WHITE                         base=0x002000  stride=6338   count=1     sectors=[2 – 3]
 *   300_S_BLUE                           base=0x004000  stride=6338   count=1     sectors=[4 – 5]
 *   300_S_WHITE                          base=0x006000  stride=6338   count=1     sectors=[6 – 7]
 *   30_S_BLUE                            base=0x008000  stride=6338   count=1     sectors=[8 – 9]
 *   30_S_WHITE                           base=0x00A000  stride=6338   count=1     sectors=[10 – 11]
 *   60_S_BLUE                            base=0x00C000  stride=6338   count=1     sectors=[12 – 13]
 *   60_S_WHITE                           base=0x00E000  stride=6338   count=1     sectors=[14 – 15]
 *   A_CELL_VOLTAGE                       base=0x010000  stride=15426  count=1     sectors=[16 – 19]
 *   ABNORMAL_TIME                        base=0x014000  stride=1474   count=1     sectors=[20]
 *   ABNORMAL                             base=0x015000  stride=1474   count=1     sectors=[21]
 *   BAT_0_BLUE                           base=0x016000  stride=5250   count=1     sectors=[22 – 23]
 *   BAT_0_ORANGE                         base=0x018000  stride=5250   count=1     sectors=[24 – 25]
 *   BAT_1_BLUE                           base=0x01A000  stride=5250   count=1     sectors=[26 – 27]
 *   BAT_1_ORANGE                         base=0x01C000  stride=5250   count=1     sectors=[28 – 29]
 *   BAT_2_BLUE                           base=0x01E000  stride=5250   count=1     sectors=[30 – 31]
 *   BAT_2_ORANGE                         base=0x020000  stride=5250   count=1     sectors=[32 – 33]
 *   BAT_3_BLUE                           base=0x022000  stride=5250   count=1     sectors=[34 – 35]
 *   BAT_3_ORANGE                         base=0x024000  stride=5250   count=1     sectors=[36 – 37]
 *   BAT_4_BLUE                           base=0x026000  stride=5250   count=1     sectors=[38 – 39]
 *   BAT_4_ORANGE                         base=0x028000  stride=5250   count=1     sectors=[40 – 41]
 *   BAT_5_BLUE                           base=0x02A000  stride=5250   count=1     sectors=[42 – 43]
 *   BAT_5_ORANGE                         base=0x02C000  stride=5250   count=1     sectors=[44 – 45]
 *   BAT_6_BLUE                           base=0x02E000  stride=5250   count=1     sectors=[46 – 47]
 *   BAT_6_ORANGE                         base=0x030000  stride=5250   count=1     sectors=[48 – 49]
 *   BAT_7_BLUE                           base=0x032000  stride=5250   count=1     sectors=[50 – 51]
 *   BAT_7_ORANGE                         base=0x034000  stride=5250   count=1     sectors=[52 – 53]
 *   BAT_8_BLUE                           base=0x036000  stride=5250   count=1     sectors=[54 – 55]
 *   BAT_8_ORANGE                         base=0x038000  stride=5250   count=1     sectors=[56 – 57]
 *   BAT_9_BLUE                           base=0x03A000  stride=5250   count=1     sectors=[58 – 59]
 *   BAT_9_ORANGE                         base=0x03C000  stride=5250   count=1     sectors=[60 – 61]
 *   BAT_NUM                              base=0x03E000  stride=2562   count=1     sectors=[62]
 *   BAT_PER_BLUE                         base=0x03F000  stride=6402   count=1     sectors=[63 – 64]
 *   BAT_PER_ORANGE                       base=0x041000  stride=6402   count=1     sectors=[65 – 66]
 *   BAT_TMP                              base=0x043000  stride=15426  count=1     sectors=[67 – 70]
 *   BLUE_CHARGING_001                    base=0x047000  stride=8490   count=1     sectors=[71 – 73]
 *   BLUE_CHARGING_002                    base=0x04A000  stride=8490   count=1     sectors=[74 – 76]
 *   BLUE_CHARGING_003                    base=0x04D000  stride=8490   count=1     sectors=[77 – 79]
 *   BLUE_CHARGING_004                    base=0x050000  stride=8490   count=1     sectors=[80 – 82]
 *   BLUE_CHARGING_005                    base=0x053000  stride=8490   count=1     sectors=[83 – 85]
 *   BLUE_CHARGING_006                    base=0x056000  stride=8490   count=1     sectors=[86 – 88]
 *   BLUE_CHARGING_007                    base=0x059000  stride=8490   count=1     sectors=[89 – 91]
 *   BLUE_CHARGING_008                    base=0x05C000  stride=8490   count=1     sectors=[92 – 94]
 *   BLUE_CHARGING_009                    base=0x05F000  stride=8490   count=1     sectors=[95 – 97]
 *   BLUE_CHARGING_010                    base=0x062000  stride=8490   count=1     sectors=[98 – 100]
 *   BLUE_CHARGING_011                    base=0x065000  stride=8490   count=1     sectors=[101 – 103]
 *   BLUE_CHARGING_012                    base=0x068000  stride=8490   count=1     sectors=[104 – 106]
 *   BLUE_CHARGING_013                    base=0x06B000  stride=8490   count=1     sectors=[107 – 109]
 *   BLUE_CHARGING_014                    base=0x06E000  stride=8490   count=1     sectors=[110 – 112]
 *   BLUE_CHARGING_015                    base=0x071000  stride=8490   count=1     sectors=[113 – 115]
 *   BLUE_CHARGING_016                    base=0x074000  stride=8490   count=1     sectors=[116 – 118]
 *   BLUE_CHARGING_017                    base=0x077000  stride=8490   count=1     sectors=[119 – 121]
 *   BLUE_CHARGING_018                    base=0x07A000  stride=8490   count=1     sectors=[122 – 124]
 *   BLUE_CHARGING_019                    base=0x07D000  stride=8490   count=1     sectors=[125 – 127]
 *   BLUE_CHARGING_020                    base=0x080000  stride=8490   count=1     sectors=[128 – 130]
 *   BLUE_CHARGING_021                    base=0x083000  stride=8490   count=1     sectors=[131 – 133]
 *   BLUE_CHARGING_022                    base=0x086000  stride=8490   count=1     sectors=[134 – 136]
 *   BLUE_CHARGING_023                    base=0x089000  stride=8490   count=1     sectors=[137 – 139]
 *   BLUE_CHARGING_024                    base=0x08C000  stride=8490   count=1     sectors=[140 – 142]
 *   BLUE_CHARGING_025                    base=0x08F000  stride=8490   count=1     sectors=[143 – 145]
 *   BLUE_CHARGING_026                    base=0x092000  stride=8490   count=1     sectors=[146 – 148]
 *   BLUE_CHARGING_027                    base=0x095000  stride=8490   count=1     sectors=[149 – 151]
 *   BLUE_CHARGING_028                    base=0x098000  stride=8490   count=1     sectors=[152 – 154]
 *   BLUE_CHARGING_029                    base=0x09B000  stride=8490   count=1     sectors=[155 – 157]
 *   BLUE_CHARGING_030                    base=0x09E000  stride=8490   count=1     sectors=[158 – 160]
 *   BLUE_CHARGING_031                    base=0x0A1000  stride=8490   count=1     sectors=[161 – 163]
 *   BLUE_CHARGING_032                    base=0x0A4000  stride=8490   count=1     sectors=[164 – 166]
 *   BLUE_CHARGING_033                    base=0x0A7000  stride=8490   count=1     sectors=[167 – 169]
 *   BLUE_CHARGING_034                    base=0x0AA000  stride=8490   count=1     sectors=[170 – 172]
 *   BLUE_CHARGING_035                    base=0x0AD000  stride=8490   count=1     sectors=[173 – 175]
 *   BLUE_CHARGING_036                    base=0x0B0000  stride=8490   count=1     sectors=[176 – 178]
 *   BLUE_CHARGING_037                    base=0x0B3000  stride=8490   count=1     sectors=[179 – 181]
 *   BLUE_CHARGING_038                    base=0x0B6000  stride=8490   count=1     sectors=[182 – 184]
 *   BLUE_CHARGING_039                    base=0x0B9000  stride=8490   count=1     sectors=[185 – 187]
 *   BLUE_CHARGING_040                    base=0x0BC000  stride=8490   count=1     sectors=[188 – 190]
 *   CHARGE_HIGH_TEMP_PRO                 base=0x0BF000  stride=17346  count=1     sectors=[191 – 195]
 *   CHARGE_TEMP                          base=0x0C4000  stride=2718   count=1     sectors=[196]
 *   CI                                   base=0x0C5000  stride=1346   count=1     sectors=[197]
 *   CIRCUIT_PROTECTION                   base=0x0C6000  stride=12866  count=1     sectors=[198 – 201]
 *   CIRCUIT_PROTECTION_TEXT              base=0x0CA000  stride=17346  count=1     sectors=[202 – 206]
 *   CIRCUIT_RECOVERY                     base=0x0CF000  stride=9186   count=1     sectors=[207 – 209]
 *   CYCLE_INDEX                          base=0x0D2000  stride=7746   count=1     sectors=[210 – 211]
 *   DI                                   base=0x0D4000  stride=678    count=1     sectors=[212]
 *   DISCHARGE_HIGH_TEMP_PRO              base=0x0D5000  stride=17346  count=1     sectors=[213 – 217]
 *   DISCHARGE_TEMP                       base=0x0DA000  stride=2718   count=1     sectors=[218]
 *   DOUBLE_CLICK_SWITCH                  base=0x0DB000  stride=9186   count=1     sectors=[219 – 221]
 *   DOUHAO                               base=0x0DE000  stride=450    count=1     sectors=[222]
 *   GONG                                 base=0x0DF000  stride=678    count=1     sectors=[223]
 *   HEALTH                               base=0x0E0000  stride=7746   count=1     sectors=[224 – 225]
 *   LEFT_1_ORANGE                        base=0x0E2000  stride=11586  count=1     sectors=[226 – 228]
 *   LEFT_2_BLUE                          base=0x0E5000  stride=8994   count=1     sectors=[229 – 231]
 *   LEFT_2_ORANGE                        base=0x0E8000  stride=8994   count=1     sectors=[232 – 234]
 *   LEFT_3_BLUE                          base=0x0EB000  stride=6402   count=1     sectors=[235 – 236]
 *   MINI                                 base=0x0ED000  stride=2946   count=1     sectors=[237]
 *   NO_ABNORMAL                          base=0x0EE000  stride=5026   count=1     sectors=[238 – 239]
 *   NOAMAL_HIGH_TEMP_PRO                 base=0x0F0000  stride=17346  count=1     sectors=[240 – 244]
 *   NOAMAL_TEMP                          base=0x0F5000  stride=2718   count=1     sectors=[245]
 *   NUM_12                               base=0x0F6000  stride=346    count=40    sectors=[246 – 249]
 *   NUM_16                               base=0x0FA000  stride=770    count=40    sectors=[250 – 257]
 *   NUM_20                               base=0x102000  stride=738    count=10    sectors=[258 – 259]
 *   NUM_20_COLON                         base=0x104000  stride=450    count=1     sectors=[260]
 *   NUM_40                               base=0x105000  stride=1986   count=11    sectors=[261 – 266]
 *   NUM_40_DEGREE                        base=0x10B000  stride=1346   count=1     sectors=[267]
 *   NUM_40_PERCENT                       base=0x10C000  stride=1346   count=1     sectors=[268]
 *   ORANGE_CHARGING_001                  base=0x10D000  stride=8490   count=1     sectors=[269 – 271]
 *   ORANGE_CHARGING_002                  base=0x110000  stride=8490   count=1     sectors=[272 – 274]
 *   ORANGE_CHARGING_003                  base=0x113000  stride=8490   count=1     sectors=[275 – 277]
 *   ORANGE_CHARGING_004                  base=0x116000  stride=8490   count=1     sectors=[278 – 280]
 *   ORANGE_CHARGING_005                  base=0x119000  stride=8490   count=1     sectors=[281 – 283]
 *   ORANGE_CHARGING_006                  base=0x11C000  stride=8490   count=1     sectors=[284 – 286]
 *   ORANGE_CHARGING_007                  base=0x11F000  stride=8490   count=1     sectors=[287 – 289]
 *   ORANGE_CHARGING_008                  base=0x122000  stride=8490   count=1     sectors=[290 – 292]
 *   ORANGE_CHARGING_009                  base=0x125000  stride=8490   count=1     sectors=[293 – 295]
 *   ORANGE_CHARGING_010                  base=0x128000  stride=8490   count=1     sectors=[296 – 298]
 *   ORANGE_CHARGING_011                  base=0x12B000  stride=8490   count=1     sectors=[299 – 301]
 *   ORANGE_CHARGING_012                  base=0x12E000  stride=8490   count=1     sectors=[302 – 304]
 *   ORANGE_CHARGING_013                  base=0x131000  stride=8490   count=1     sectors=[305 – 307]
 *   ORANGE_CHARGING_014                  base=0x134000  stride=8490   count=1     sectors=[308 – 310]
 *   ORANGE_CHARGING_015                  base=0x137000  stride=8490   count=1     sectors=[311 – 313]
 *   ORANGE_CHARGING_016                  base=0x13A000  stride=8490   count=1     sectors=[314 – 316]
 *   ORANGE_CHARGING_017                  base=0x13D000  stride=8490   count=1     sectors=[317 – 319]
 *   ORANGE_CHARGING_018                  base=0x140000  stride=8490   count=1     sectors=[320 – 322]
 *   ORANGE_CHARGING_019                  base=0x143000  stride=8490   count=1     sectors=[323 – 325]
 *   ORANGE_CHARGING_020                  base=0x146000  stride=8490   count=1     sectors=[326 – 328]
 *   ORANGE_CHARGING_021                  base=0x149000  stride=8490   count=1     sectors=[329 – 331]
 *   ORANGE_CHARGING_022                  base=0x14C000  stride=8490   count=1     sectors=[332 – 334]
 *   ORANGE_CHARGING_023                  base=0x14F000  stride=8490   count=1     sectors=[335 – 337]
 *   ORANGE_CHARGING_024                  base=0x152000  stride=8490   count=1     sectors=[338 – 340]
 *   ORANGE_CHARGING_025                  base=0x155000  stride=8490   count=1     sectors=[341 – 343]
 *   ORANGE_CHARGING_026                  base=0x158000  stride=8490   count=1     sectors=[344 – 346]
 *   ORANGE_CHARGING_027                  base=0x15B000  stride=8490   count=1     sectors=[347 – 349]
 *   ORANGE_CHARGING_028                  base=0x15E000  stride=8490   count=1     sectors=[350 – 352]
 *   ORANGE_CHARGING_029                  base=0x161000  stride=8490   count=1     sectors=[353 – 355]
 *   ORANGE_CHARGING_030                  base=0x164000  stride=8490   count=1     sectors=[356 – 358]
 *   ORANGE_CHARGING_031                  base=0x167000  stride=8490   count=1     sectors=[359 – 361]
 *   ORANGE_CHARGING_032                  base=0x16A000  stride=8490   count=1     sectors=[362 – 364]
 *   ORANGE_CHARGING_033                  base=0x16D000  stride=8490   count=1     sectors=[365 – 367]
 *   ORANGE_CHARGING_034                  base=0x170000  stride=8490   count=1     sectors=[368 – 370]
 *   ORANGE_CHARGING_035                  base=0x173000  stride=8490   count=1     sectors=[371 – 373]
 *   ORANGE_CHARGING_036                  base=0x176000  stride=8490   count=1     sectors=[374 – 376]
 *   ORANGE_CHARGING_037                  base=0x179000  stride=8490   count=1     sectors=[377 – 379]
 *   ORANGE_CHARGING_038                  base=0x17C000  stride=8490   count=1     sectors=[380 – 382]
 *   ORANGE_CHARGING_039                  base=0x17F000  stride=8490   count=1     sectors=[383 – 385]
 *   ORANGE_CHARGING_040                  base=0x182000  stride=8490   count=1     sectors=[386 – 388]
 *   OUT                                  base=0x185000  stride=2178   count=1     sectors=[389]
 *   POWER_PART_1_USB_A_BLUE              base=0x186000  stride=5286   count=1     sectors=[390 – 391]
 *   POWER_PART_1_USB_A_WHITE             base=0x188000  stride=5286   count=1     sectors=[392 – 393]
 *   POWER_PART_1_USB_C_BLUE              base=0x18A000  stride=5286   count=1     sectors=[394 – 395]
 *   POWER_PART_1_USB_C_WHITE             base=0x18C000  stride=5286   count=1     sectors=[396 – 397]
 *   POWER_PART_2_PORT_1_BLUE             base=0x18E000  stride=1506   count=1     sectors=[398]
 *   POWER_PART_2_PORT_1_WHITE            base=0x18F000  stride=1506   count=1     sectors=[399]
 *   POWER_PART_2_PORT_2_BLUE             base=0x190000  stride=1506   count=1     sectors=[400]
 *   POWER_PART_2_PORT_2_WHITE            base=0x191000  stride=1506   count=1     sectors=[401]
 *   POWER_PART_2_PORT_3_BLUE             base=0x192000  stride=1506   count=1     sectors=[402]
 *   POWER_PART_2_PORT_3_WHITE            base=0x193000  stride=1506   count=1     sectors=[403]
 *   POWER_PART_3_IN_BLUE                 base=0x194000  stride=6366   count=1     sectors=[404 – 405]
 *   POWER_PART_3_OUT_BLUE                base=0x196000  stride=6366   count=1     sectors=[406 – 407]
 *   POWER_PART_3_WHITE                   base=0x198000  stride=6366   count=1     sectors=[408 – 409]
 *   POWER_PART_4_0_BLUE                  base=0x19A000  stride=1866   count=1     sectors=[410]
 *   POWER_PART_4_0_WHITE                 base=0x19B000  stride=1866   count=1     sectors=[411]
 *   POWER_PART_4_1_BLUE                  base=0x19C000  stride=1866   count=1     sectors=[412]
 *   POWER_PART_4_1_WHITE                 base=0x19D000  stride=1866   count=1     sectors=[413]
 *   POWER_PART_4_2_BLUE                  base=0x19E000  stride=1866   count=1     sectors=[414]
 *   POWER_PART_4_2_WHITE                 base=0x19F000  stride=1866   count=1     sectors=[415]
 *   POWER_PART_4_3_BLUE                  base=0x1A0000  stride=1866   count=1     sectors=[416]
 *   POWER_PART_4_3_WHITE                 base=0x1A1000  stride=1866   count=1     sectors=[417]
 *   POWER_PART_4_4_BLUE                  base=0x1A2000  stride=1866   count=1     sectors=[418]
 *   POWER_PART_4_4_WHITE                 base=0x1A3000  stride=1866   count=1     sectors=[419]
 *   POWER_PART_4_5_BLUE                  base=0x1A4000  stride=1866   count=1     sectors=[420]
 *   POWER_PART_4_5_WHITE                 base=0x1A5000  stride=1866   count=1     sectors=[421]
 *   POWER_PART_4_6_BLUE                  base=0x1A6000  stride=1866   count=1     sectors=[422]
 *   POWER_PART_4_6_WHITE                 base=0x1A7000  stride=1866   count=1     sectors=[423]
 *   POWER_PART_4_7_BLUE                  base=0x1A8000  stride=1866   count=1     sectors=[424]
 *   POWER_PART_4_7_WHITE                 base=0x1A9000  stride=1866   count=1     sectors=[425]
 *   POWER_PART_4_8_BLUE                  base=0x1AA000  stride=1866   count=1     sectors=[426]
 *   POWER_PART_4_8_WHITE                 base=0x1AB000  stride=1866   count=1     sectors=[427]
 *   POWER_PART_4_9_BLUE                  base=0x1AC000  stride=1866   count=1     sectors=[428]
 *   POWER_PART_4_9_WHITE                 base=0x1AD000  stride=1866   count=1     sectors=[429]
 *   POWER_PART_4_BLUE                    base=0x1AE000  stride=1866   count=1     sectors=[430]
 *   POWER_PART_4_WHITE                   base=0x1AF000  stride=1866   count=1     sectors=[431]
 *   POWER_PART_5_BLUE                    base=0x1B0000  stride=3486   count=1     sectors=[432]
 *   POWER_PART_5_WHITE                   base=0x1B1000  stride=3486   count=1     sectors=[433]
 *   RIGHT_1_ORANGE                       base=0x1B2000  stride=11586  count=1     sectors=[434 – 436]
 *   RIGHT_2_BLUE                         base=0x1B5000  stride=8994   count=1     sectors=[437 – 439]
 *   RIGHT_2_ORANGE                       base=0x1B8000  stride=8994   count=1     sectors=[440 – 442]
 *   RIGHT_3_BLUE                         base=0x1BB000  stride=6402   count=1     sectors=[443 – 444]
 *   SAFE                                 base=0x1BD000  stride=12866  count=1     sectors=[445 – 448]
 *   SAFEGUARD                            base=0x1C1000  stride=26466  count=1     sectors=[449 – 455]
 *   SCREEN_OFF_DURATION                  base=0x1C8000  stride=15426  count=1     sectors=[456 – 459]
 *   TEMP_ABNORMAL                        base=0x1CC000  stride=15426  count=1     sectors=[460 – 463]
 *   TEMP_ORANGE                          base=0x1D0000  stride=12866  count=1     sectors=[464 – 467]
 *   TEMPERATURE_RECOVERY                 base=0x1D4000  stride=9186   count=1     sectors=[468 – 470]
 *   TIAO                                 base=0x1D7000  stride=678    count=1     sectors=[471]
 *   TIMER                                base=0x1D8000  stride=1026   count=1     sectors=[472]
 *   TOTAL_VOLTAGE                        base=0x1D9000  stride=1986   count=1     sectors=[473]
 *   VOLTAGE_ABNORMAL                     base=0x1DA000  stride=15426  count=1     sectors=[474 – 477]
 */

#ifndef __FLASH_IMAGE_ADDR_H__
#define __FLASH_IMAGE_ADDR_H__

/*
 * Category base addresses — access images via:
 *   addr = FLASH_ADDR_<CAT>_BASE + index * FLASH_STRIDE_<CAT>
 */
#define FLASH_ADDR_1800_S_BLUE_BASE    (0x00000000 + 0x0000)
#define FLASH_STRIDE_1800_S_BLUE       6338
#define FLASH_COUNT_1800_S_BLUE        1

#define FLASH_ADDR_1800_S_WHITE_BASE    (0x00000000 + 0x2000)
#define FLASH_STRIDE_1800_S_WHITE       6338
#define FLASH_COUNT_1800_S_WHITE        1

#define FLASH_ADDR_300_S_BLUE_BASE    (0x00000000 + 0x4000)
#define FLASH_STRIDE_300_S_BLUE       6338
#define FLASH_COUNT_300_S_BLUE        1

#define FLASH_ADDR_300_S_WHITE_BASE    (0x00000000 + 0x6000)
#define FLASH_STRIDE_300_S_WHITE       6338
#define FLASH_COUNT_300_S_WHITE        1

#define FLASH_ADDR_30_S_BLUE_BASE    (0x00000000 + 0x8000)
#define FLASH_STRIDE_30_S_BLUE       6338
#define FLASH_COUNT_30_S_BLUE        1

#define FLASH_ADDR_30_S_WHITE_BASE    (0x00000000 + 0xA000)
#define FLASH_STRIDE_30_S_WHITE       6338
#define FLASH_COUNT_30_S_WHITE        1

#define FLASH_ADDR_60_S_BLUE_BASE    (0x00000000 + 0xC000)
#define FLASH_STRIDE_60_S_BLUE       6338
#define FLASH_COUNT_60_S_BLUE        1

#define FLASH_ADDR_60_S_WHITE_BASE    (0x00000000 + 0xE000)
#define FLASH_STRIDE_60_S_WHITE       6338
#define FLASH_COUNT_60_S_WHITE        1

#define FLASH_ADDR_A_CELL_VOLTAGE_BASE    (0x00000000 + 0x10000)
#define FLASH_STRIDE_A_CELL_VOLTAGE       15426
#define FLASH_COUNT_A_CELL_VOLTAGE        1

#define FLASH_ADDR_ABNORMAL_TIME_BASE    (0x00000000 + 0x14000)
#define FLASH_STRIDE_ABNORMAL_TIME       1474
#define FLASH_COUNT_ABNORMAL_TIME        1

#define FLASH_ADDR_ABNORMAL_BASE    (0x00000000 + 0x15000)
#define FLASH_STRIDE_ABNORMAL       1474
#define FLASH_COUNT_ABNORMAL        1

#define FLASH_ADDR_BAT_0_BLUE_BASE    (0x00000000 + 0x16000)
#define FLASH_STRIDE_BAT_0_BLUE       5250
#define FLASH_COUNT_BAT_0_BLUE        1

#define FLASH_ADDR_BAT_0_ORANGE_BASE    (0x00000000 + 0x18000)
#define FLASH_STRIDE_BAT_0_ORANGE       5250
#define FLASH_COUNT_BAT_0_ORANGE        1

#define FLASH_ADDR_BAT_1_BLUE_BASE    (0x00000000 + 0x1A000)
#define FLASH_STRIDE_BAT_1_BLUE       5250
#define FLASH_COUNT_BAT_1_BLUE        1

#define FLASH_ADDR_BAT_1_ORANGE_BASE    (0x00000000 + 0x1C000)
#define FLASH_STRIDE_BAT_1_ORANGE       5250
#define FLASH_COUNT_BAT_1_ORANGE        1

#define FLASH_ADDR_BAT_2_BLUE_BASE    (0x00000000 + 0x1E000)
#define FLASH_STRIDE_BAT_2_BLUE       5250
#define FLASH_COUNT_BAT_2_BLUE        1

#define FLASH_ADDR_BAT_2_ORANGE_BASE    (0x00000000 + 0x20000)
#define FLASH_STRIDE_BAT_2_ORANGE       5250
#define FLASH_COUNT_BAT_2_ORANGE        1

#define FLASH_ADDR_BAT_3_BLUE_BASE    (0x00000000 + 0x22000)
#define FLASH_STRIDE_BAT_3_BLUE       5250
#define FLASH_COUNT_BAT_3_BLUE        1

#define FLASH_ADDR_BAT_3_ORANGE_BASE    (0x00000000 + 0x24000)
#define FLASH_STRIDE_BAT_3_ORANGE       5250
#define FLASH_COUNT_BAT_3_ORANGE        1

#define FLASH_ADDR_BAT_4_BLUE_BASE    (0x00000000 + 0x26000)
#define FLASH_STRIDE_BAT_4_BLUE       5250
#define FLASH_COUNT_BAT_4_BLUE        1

#define FLASH_ADDR_BAT_4_ORANGE_BASE    (0x00000000 + 0x28000)
#define FLASH_STRIDE_BAT_4_ORANGE       5250
#define FLASH_COUNT_BAT_4_ORANGE        1

#define FLASH_ADDR_BAT_5_BLUE_BASE    (0x00000000 + 0x2A000)
#define FLASH_STRIDE_BAT_5_BLUE       5250
#define FLASH_COUNT_BAT_5_BLUE        1

#define FLASH_ADDR_BAT_5_ORANGE_BASE    (0x00000000 + 0x2C000)
#define FLASH_STRIDE_BAT_5_ORANGE       5250
#define FLASH_COUNT_BAT_5_ORANGE        1

#define FLASH_ADDR_BAT_6_BLUE_BASE    (0x00000000 + 0x2E000)
#define FLASH_STRIDE_BAT_6_BLUE       5250
#define FLASH_COUNT_BAT_6_BLUE        1

#define FLASH_ADDR_BAT_6_ORANGE_BASE    (0x00000000 + 0x30000)
#define FLASH_STRIDE_BAT_6_ORANGE       5250
#define FLASH_COUNT_BAT_6_ORANGE        1

#define FLASH_ADDR_BAT_7_BLUE_BASE    (0x00000000 + 0x32000)
#define FLASH_STRIDE_BAT_7_BLUE       5250
#define FLASH_COUNT_BAT_7_BLUE        1

#define FLASH_ADDR_BAT_7_ORANGE_BASE    (0x00000000 + 0x34000)
#define FLASH_STRIDE_BAT_7_ORANGE       5250
#define FLASH_COUNT_BAT_7_ORANGE        1

#define FLASH_ADDR_BAT_8_BLUE_BASE    (0x00000000 + 0x36000)
#define FLASH_STRIDE_BAT_8_BLUE       5250
#define FLASH_COUNT_BAT_8_BLUE        1

#define FLASH_ADDR_BAT_8_ORANGE_BASE    (0x00000000 + 0x38000)
#define FLASH_STRIDE_BAT_8_ORANGE       5250
#define FLASH_COUNT_BAT_8_ORANGE        1

#define FLASH_ADDR_BAT_9_BLUE_BASE    (0x00000000 + 0x3A000)
#define FLASH_STRIDE_BAT_9_BLUE       5250
#define FLASH_COUNT_BAT_9_BLUE        1

#define FLASH_ADDR_BAT_9_ORANGE_BASE    (0x00000000 + 0x3C000)
#define FLASH_STRIDE_BAT_9_ORANGE       5250
#define FLASH_COUNT_BAT_9_ORANGE        1

#define FLASH_ADDR_BAT_NUM_BASE    (0x00000000 + 0x3E000)
#define FLASH_STRIDE_BAT_NUM       2562
#define FLASH_COUNT_BAT_NUM        1

#define FLASH_ADDR_BAT_PER_BLUE_BASE    (0x00000000 + 0x3F000)
#define FLASH_STRIDE_BAT_PER_BLUE       6402
#define FLASH_COUNT_BAT_PER_BLUE        1

#define FLASH_ADDR_BAT_PER_ORANGE_BASE    (0x00000000 + 0x41000)
#define FLASH_STRIDE_BAT_PER_ORANGE       6402
#define FLASH_COUNT_BAT_PER_ORANGE        1

#define FLASH_ADDR_BAT_TMP_BASE    (0x00000000 + 0x43000)
#define FLASH_STRIDE_BAT_TMP       15426
#define FLASH_COUNT_BAT_TMP        1

#define FLASH_ADDR_BLUE_CHARGING_001_BASE    (0x00000000 + 0x47000)
#define FLASH_STRIDE_BLUE_CHARGING_001       8490
#define FLASH_COUNT_BLUE_CHARGING_001        1

#define FLASH_ADDR_BLUE_CHARGING_002_BASE    (0x00000000 + 0x4A000)
#define FLASH_STRIDE_BLUE_CHARGING_002       8490
#define FLASH_COUNT_BLUE_CHARGING_002        1

#define FLASH_ADDR_BLUE_CHARGING_003_BASE    (0x00000000 + 0x4D000)
#define FLASH_STRIDE_BLUE_CHARGING_003       8490
#define FLASH_COUNT_BLUE_CHARGING_003        1

#define FLASH_ADDR_BLUE_CHARGING_004_BASE    (0x00000000 + 0x50000)
#define FLASH_STRIDE_BLUE_CHARGING_004       8490
#define FLASH_COUNT_BLUE_CHARGING_004        1

#define FLASH_ADDR_BLUE_CHARGING_005_BASE    (0x00000000 + 0x53000)
#define FLASH_STRIDE_BLUE_CHARGING_005       8490
#define FLASH_COUNT_BLUE_CHARGING_005        1

#define FLASH_ADDR_BLUE_CHARGING_006_BASE    (0x00000000 + 0x56000)
#define FLASH_STRIDE_BLUE_CHARGING_006       8490
#define FLASH_COUNT_BLUE_CHARGING_006        1

#define FLASH_ADDR_BLUE_CHARGING_007_BASE    (0x00000000 + 0x59000)
#define FLASH_STRIDE_BLUE_CHARGING_007       8490
#define FLASH_COUNT_BLUE_CHARGING_007        1

#define FLASH_ADDR_BLUE_CHARGING_008_BASE    (0x00000000 + 0x5C000)
#define FLASH_STRIDE_BLUE_CHARGING_008       8490
#define FLASH_COUNT_BLUE_CHARGING_008        1

#define FLASH_ADDR_BLUE_CHARGING_009_BASE    (0x00000000 + 0x5F000)
#define FLASH_STRIDE_BLUE_CHARGING_009       8490
#define FLASH_COUNT_BLUE_CHARGING_009        1

#define FLASH_ADDR_BLUE_CHARGING_010_BASE    (0x00000000 + 0x62000)
#define FLASH_STRIDE_BLUE_CHARGING_010       8490
#define FLASH_COUNT_BLUE_CHARGING_010        1

#define FLASH_ADDR_BLUE_CHARGING_011_BASE    (0x00000000 + 0x65000)
#define FLASH_STRIDE_BLUE_CHARGING_011       8490
#define FLASH_COUNT_BLUE_CHARGING_011        1

#define FLASH_ADDR_BLUE_CHARGING_012_BASE    (0x00000000 + 0x68000)
#define FLASH_STRIDE_BLUE_CHARGING_012       8490
#define FLASH_COUNT_BLUE_CHARGING_012        1

#define FLASH_ADDR_BLUE_CHARGING_013_BASE    (0x00000000 + 0x6B000)
#define FLASH_STRIDE_BLUE_CHARGING_013       8490
#define FLASH_COUNT_BLUE_CHARGING_013        1

#define FLASH_ADDR_BLUE_CHARGING_014_BASE    (0x00000000 + 0x6E000)
#define FLASH_STRIDE_BLUE_CHARGING_014       8490
#define FLASH_COUNT_BLUE_CHARGING_014        1

#define FLASH_ADDR_BLUE_CHARGING_015_BASE    (0x00000000 + 0x71000)
#define FLASH_STRIDE_BLUE_CHARGING_015       8490
#define FLASH_COUNT_BLUE_CHARGING_015        1

#define FLASH_ADDR_BLUE_CHARGING_016_BASE    (0x00000000 + 0x74000)
#define FLASH_STRIDE_BLUE_CHARGING_016       8490
#define FLASH_COUNT_BLUE_CHARGING_016        1

#define FLASH_ADDR_BLUE_CHARGING_017_BASE    (0x00000000 + 0x77000)
#define FLASH_STRIDE_BLUE_CHARGING_017       8490
#define FLASH_COUNT_BLUE_CHARGING_017        1

#define FLASH_ADDR_BLUE_CHARGING_018_BASE    (0x00000000 + 0x7A000)
#define FLASH_STRIDE_BLUE_CHARGING_018       8490
#define FLASH_COUNT_BLUE_CHARGING_018        1

#define FLASH_ADDR_BLUE_CHARGING_019_BASE    (0x00000000 + 0x7D000)
#define FLASH_STRIDE_BLUE_CHARGING_019       8490
#define FLASH_COUNT_BLUE_CHARGING_019        1

#define FLASH_ADDR_BLUE_CHARGING_020_BASE    (0x00000000 + 0x80000)
#define FLASH_STRIDE_BLUE_CHARGING_020       8490
#define FLASH_COUNT_BLUE_CHARGING_020        1

#define FLASH_ADDR_BLUE_CHARGING_021_BASE    (0x00000000 + 0x83000)
#define FLASH_STRIDE_BLUE_CHARGING_021       8490
#define FLASH_COUNT_BLUE_CHARGING_021        1

#define FLASH_ADDR_BLUE_CHARGING_022_BASE    (0x00000000 + 0x86000)
#define FLASH_STRIDE_BLUE_CHARGING_022       8490
#define FLASH_COUNT_BLUE_CHARGING_022        1

#define FLASH_ADDR_BLUE_CHARGING_023_BASE    (0x00000000 + 0x89000)
#define FLASH_STRIDE_BLUE_CHARGING_023       8490
#define FLASH_COUNT_BLUE_CHARGING_023        1

#define FLASH_ADDR_BLUE_CHARGING_024_BASE    (0x00000000 + 0x8C000)
#define FLASH_STRIDE_BLUE_CHARGING_024       8490
#define FLASH_COUNT_BLUE_CHARGING_024        1

#define FLASH_ADDR_BLUE_CHARGING_025_BASE    (0x00000000 + 0x8F000)
#define FLASH_STRIDE_BLUE_CHARGING_025       8490
#define FLASH_COUNT_BLUE_CHARGING_025        1

#define FLASH_ADDR_BLUE_CHARGING_026_BASE    (0x00000000 + 0x92000)
#define FLASH_STRIDE_BLUE_CHARGING_026       8490
#define FLASH_COUNT_BLUE_CHARGING_026        1

#define FLASH_ADDR_BLUE_CHARGING_027_BASE    (0x00000000 + 0x95000)
#define FLASH_STRIDE_BLUE_CHARGING_027       8490
#define FLASH_COUNT_BLUE_CHARGING_027        1

#define FLASH_ADDR_BLUE_CHARGING_028_BASE    (0x00000000 + 0x98000)
#define FLASH_STRIDE_BLUE_CHARGING_028       8490
#define FLASH_COUNT_BLUE_CHARGING_028        1

#define FLASH_ADDR_BLUE_CHARGING_029_BASE    (0x00000000 + 0x9B000)
#define FLASH_STRIDE_BLUE_CHARGING_029       8490
#define FLASH_COUNT_BLUE_CHARGING_029        1

#define FLASH_ADDR_BLUE_CHARGING_030_BASE    (0x00000000 + 0x9E000)
#define FLASH_STRIDE_BLUE_CHARGING_030       8490
#define FLASH_COUNT_BLUE_CHARGING_030        1

#define FLASH_ADDR_BLUE_CHARGING_031_BASE    (0x00000000 + 0xA1000)
#define FLASH_STRIDE_BLUE_CHARGING_031       8490
#define FLASH_COUNT_BLUE_CHARGING_031        1

#define FLASH_ADDR_BLUE_CHARGING_032_BASE    (0x00000000 + 0xA4000)
#define FLASH_STRIDE_BLUE_CHARGING_032       8490
#define FLASH_COUNT_BLUE_CHARGING_032        1

#define FLASH_ADDR_BLUE_CHARGING_033_BASE    (0x00000000 + 0xA7000)
#define FLASH_STRIDE_BLUE_CHARGING_033       8490
#define FLASH_COUNT_BLUE_CHARGING_033        1

#define FLASH_ADDR_BLUE_CHARGING_034_BASE    (0x00000000 + 0xAA000)
#define FLASH_STRIDE_BLUE_CHARGING_034       8490
#define FLASH_COUNT_BLUE_CHARGING_034        1

#define FLASH_ADDR_BLUE_CHARGING_035_BASE    (0x00000000 + 0xAD000)
#define FLASH_STRIDE_BLUE_CHARGING_035       8490
#define FLASH_COUNT_BLUE_CHARGING_035        1

#define FLASH_ADDR_BLUE_CHARGING_036_BASE    (0x00000000 + 0xB0000)
#define FLASH_STRIDE_BLUE_CHARGING_036       8490
#define FLASH_COUNT_BLUE_CHARGING_036        1

#define FLASH_ADDR_BLUE_CHARGING_037_BASE    (0x00000000 + 0xB3000)
#define FLASH_STRIDE_BLUE_CHARGING_037       8490
#define FLASH_COUNT_BLUE_CHARGING_037        1

#define FLASH_ADDR_BLUE_CHARGING_038_BASE    (0x00000000 + 0xB6000)
#define FLASH_STRIDE_BLUE_CHARGING_038       8490
#define FLASH_COUNT_BLUE_CHARGING_038        1

#define FLASH_ADDR_BLUE_CHARGING_039_BASE    (0x00000000 + 0xB9000)
#define FLASH_STRIDE_BLUE_CHARGING_039       8490
#define FLASH_COUNT_BLUE_CHARGING_039        1

#define FLASH_ADDR_BLUE_CHARGING_040_BASE    (0x00000000 + 0xBC000)
#define FLASH_STRIDE_BLUE_CHARGING_040       8490
#define FLASH_COUNT_BLUE_CHARGING_040        1

#define FLASH_ADDR_CHARGE_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xBF000)
#define FLASH_STRIDE_CHARGE_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_CHARGE_HIGH_TEMP_PRO        1

#define FLASH_ADDR_CHARGE_TEMP_BASE    (0x00000000 + 0xC4000)
#define FLASH_STRIDE_CHARGE_TEMP       2718
#define FLASH_COUNT_CHARGE_TEMP        1

#define FLASH_ADDR_CI_BASE    (0x00000000 + 0xC5000)
#define FLASH_STRIDE_CI       1346
#define FLASH_COUNT_CI        1

#define FLASH_ADDR_CIRCUIT_PROTECTION_BASE    (0x00000000 + 0xC6000)
#define FLASH_STRIDE_CIRCUIT_PROTECTION       12866
#define FLASH_COUNT_CIRCUIT_PROTECTION        1

#define FLASH_ADDR_CIRCUIT_PROTECTION_TEXT_BASE    (0x00000000 + 0xCA000)
#define FLASH_STRIDE_CIRCUIT_PROTECTION_TEXT       17346
#define FLASH_COUNT_CIRCUIT_PROTECTION_TEXT        1

#define FLASH_ADDR_CIRCUIT_RECOVERY_BASE    (0x00000000 + 0xCF000)
#define FLASH_STRIDE_CIRCUIT_RECOVERY       9186
#define FLASH_COUNT_CIRCUIT_RECOVERY        1

#define FLASH_ADDR_CYCLE_INDEX_BASE    (0x00000000 + 0xD2000)
#define FLASH_STRIDE_CYCLE_INDEX       7746
#define FLASH_COUNT_CYCLE_INDEX        1

#define FLASH_ADDR_DI_BASE    (0x00000000 + 0xD4000)
#define FLASH_STRIDE_DI       678
#define FLASH_COUNT_DI        1

#define FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xD5000)
#define FLASH_STRIDE_DISCHARGE_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_DISCHARGE_HIGH_TEMP_PRO        1

#define FLASH_ADDR_DISCHARGE_TEMP_BASE    (0x00000000 + 0xDA000)
#define FLASH_STRIDE_DISCHARGE_TEMP       2718
#define FLASH_COUNT_DISCHARGE_TEMP        1

#define FLASH_ADDR_DOUBLE_CLICK_SWITCH_BASE    (0x00000000 + 0xDB000)
#define FLASH_STRIDE_DOUBLE_CLICK_SWITCH       9186
#define FLASH_COUNT_DOUBLE_CLICK_SWITCH        1

#define FLASH_ADDR_DOUHAO_BASE    (0x00000000 + 0xDE000)
#define FLASH_STRIDE_DOUHAO       450
#define FLASH_COUNT_DOUHAO        1

#define FLASH_ADDR_GONG_BASE    (0x00000000 + 0xDF000)
#define FLASH_STRIDE_GONG       678
#define FLASH_COUNT_GONG        1

#define FLASH_ADDR_HEALTH_BASE    (0x00000000 + 0xE0000)
#define FLASH_STRIDE_HEALTH       7746
#define FLASH_COUNT_HEALTH        1

#define FLASH_ADDR_LEFT_1_ORANGE_BASE    (0x00000000 + 0xE2000)
#define FLASH_STRIDE_LEFT_1_ORANGE       11586
#define FLASH_COUNT_LEFT_1_ORANGE        1

#define FLASH_ADDR_LEFT_2_BLUE_BASE    (0x00000000 + 0xE5000)
#define FLASH_STRIDE_LEFT_2_BLUE       8994
#define FLASH_COUNT_LEFT_2_BLUE        1

#define FLASH_ADDR_LEFT_2_ORANGE_BASE    (0x00000000 + 0xE8000)
#define FLASH_STRIDE_LEFT_2_ORANGE       8994
#define FLASH_COUNT_LEFT_2_ORANGE        1

#define FLASH_ADDR_LEFT_3_BLUE_BASE    (0x00000000 + 0xEB000)
#define FLASH_STRIDE_LEFT_3_BLUE       6402
#define FLASH_COUNT_LEFT_3_BLUE        1

#define FLASH_ADDR_MINI_BASE    (0x00000000 + 0xED000)
#define FLASH_STRIDE_MINI       2946
#define FLASH_COUNT_MINI        1

#define FLASH_ADDR_NO_ABNORMAL_BASE    (0x00000000 + 0xEE000)
#define FLASH_STRIDE_NO_ABNORMAL       5026
#define FLASH_COUNT_NO_ABNORMAL        1

#define FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xF0000)
#define FLASH_STRIDE_NOAMAL_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_NOAMAL_HIGH_TEMP_PRO        1

#define FLASH_ADDR_NOAMAL_TEMP_BASE    (0x00000000 + 0xF5000)
#define FLASH_STRIDE_NOAMAL_TEMP       2718
#define FLASH_COUNT_NOAMAL_TEMP        1

#define FLASH_ADDR_NUM_12_BASE    (0x00000000 + 0xF6000)
#define FLASH_STRIDE_NUM_12       346
#define FLASH_COUNT_NUM_12        40

#define FLASH_ADDR_NUM_16_BASE    (0x00000000 + 0xFA000)
#define FLASH_STRIDE_NUM_16       770
#define FLASH_COUNT_NUM_16        40

#define FLASH_ADDR_NUM_20_BASE    (0x00000000 + 0x102000)
#define FLASH_STRIDE_NUM_20       738
#define FLASH_COUNT_NUM_20        10

#define FLASH_ADDR_NUM_20_COLON_BASE    (0x00000000 + 0x104000)
#define FLASH_STRIDE_NUM_20_COLON       450
#define FLASH_COUNT_NUM_20_COLON        1

#define FLASH_ADDR_NUM_40_BASE    (0x00000000 + 0x105000)
#define FLASH_STRIDE_NUM_40       1986
#define FLASH_COUNT_NUM_40        11

#define FLASH_ADDR_NUM_40_DEGREE_BASE    (0x00000000 + 0x10B000)
#define FLASH_STRIDE_NUM_40_DEGREE       1346
#define FLASH_COUNT_NUM_40_DEGREE        1

#define FLASH_ADDR_NUM_40_PERCENT_BASE    (0x00000000 + 0x10C000)
#define FLASH_STRIDE_NUM_40_PERCENT       1346
#define FLASH_COUNT_NUM_40_PERCENT        1

#define FLASH_ADDR_ORANGE_CHARGING_001_BASE    (0x00000000 + 0x10D000)
#define FLASH_STRIDE_ORANGE_CHARGING_001       8490
#define FLASH_COUNT_ORANGE_CHARGING_001        1

#define FLASH_ADDR_ORANGE_CHARGING_002_BASE    (0x00000000 + 0x110000)
#define FLASH_STRIDE_ORANGE_CHARGING_002       8490
#define FLASH_COUNT_ORANGE_CHARGING_002        1

#define FLASH_ADDR_ORANGE_CHARGING_003_BASE    (0x00000000 + 0x113000)
#define FLASH_STRIDE_ORANGE_CHARGING_003       8490
#define FLASH_COUNT_ORANGE_CHARGING_003        1

#define FLASH_ADDR_ORANGE_CHARGING_004_BASE    (0x00000000 + 0x116000)
#define FLASH_STRIDE_ORANGE_CHARGING_004       8490
#define FLASH_COUNT_ORANGE_CHARGING_004        1

#define FLASH_ADDR_ORANGE_CHARGING_005_BASE    (0x00000000 + 0x119000)
#define FLASH_STRIDE_ORANGE_CHARGING_005       8490
#define FLASH_COUNT_ORANGE_CHARGING_005        1

#define FLASH_ADDR_ORANGE_CHARGING_006_BASE    (0x00000000 + 0x11C000)
#define FLASH_STRIDE_ORANGE_CHARGING_006       8490
#define FLASH_COUNT_ORANGE_CHARGING_006        1

#define FLASH_ADDR_ORANGE_CHARGING_007_BASE    (0x00000000 + 0x11F000)
#define FLASH_STRIDE_ORANGE_CHARGING_007       8490
#define FLASH_COUNT_ORANGE_CHARGING_007        1

#define FLASH_ADDR_ORANGE_CHARGING_008_BASE    (0x00000000 + 0x122000)
#define FLASH_STRIDE_ORANGE_CHARGING_008       8490
#define FLASH_COUNT_ORANGE_CHARGING_008        1

#define FLASH_ADDR_ORANGE_CHARGING_009_BASE    (0x00000000 + 0x125000)
#define FLASH_STRIDE_ORANGE_CHARGING_009       8490
#define FLASH_COUNT_ORANGE_CHARGING_009        1

#define FLASH_ADDR_ORANGE_CHARGING_010_BASE    (0x00000000 + 0x128000)
#define FLASH_STRIDE_ORANGE_CHARGING_010       8490
#define FLASH_COUNT_ORANGE_CHARGING_010        1

#define FLASH_ADDR_ORANGE_CHARGING_011_BASE    (0x00000000 + 0x12B000)
#define FLASH_STRIDE_ORANGE_CHARGING_011       8490
#define FLASH_COUNT_ORANGE_CHARGING_011        1

#define FLASH_ADDR_ORANGE_CHARGING_012_BASE    (0x00000000 + 0x12E000)
#define FLASH_STRIDE_ORANGE_CHARGING_012       8490
#define FLASH_COUNT_ORANGE_CHARGING_012        1

#define FLASH_ADDR_ORANGE_CHARGING_013_BASE    (0x00000000 + 0x131000)
#define FLASH_STRIDE_ORANGE_CHARGING_013       8490
#define FLASH_COUNT_ORANGE_CHARGING_013        1

#define FLASH_ADDR_ORANGE_CHARGING_014_BASE    (0x00000000 + 0x134000)
#define FLASH_STRIDE_ORANGE_CHARGING_014       8490
#define FLASH_COUNT_ORANGE_CHARGING_014        1

#define FLASH_ADDR_ORANGE_CHARGING_015_BASE    (0x00000000 + 0x137000)
#define FLASH_STRIDE_ORANGE_CHARGING_015       8490
#define FLASH_COUNT_ORANGE_CHARGING_015        1

#define FLASH_ADDR_ORANGE_CHARGING_016_BASE    (0x00000000 + 0x13A000)
#define FLASH_STRIDE_ORANGE_CHARGING_016       8490
#define FLASH_COUNT_ORANGE_CHARGING_016        1

#define FLASH_ADDR_ORANGE_CHARGING_017_BASE    (0x00000000 + 0x13D000)
#define FLASH_STRIDE_ORANGE_CHARGING_017       8490
#define FLASH_COUNT_ORANGE_CHARGING_017        1

#define FLASH_ADDR_ORANGE_CHARGING_018_BASE    (0x00000000 + 0x140000)
#define FLASH_STRIDE_ORANGE_CHARGING_018       8490
#define FLASH_COUNT_ORANGE_CHARGING_018        1

#define FLASH_ADDR_ORANGE_CHARGING_019_BASE    (0x00000000 + 0x143000)
#define FLASH_STRIDE_ORANGE_CHARGING_019       8490
#define FLASH_COUNT_ORANGE_CHARGING_019        1

#define FLASH_ADDR_ORANGE_CHARGING_020_BASE    (0x00000000 + 0x146000)
#define FLASH_STRIDE_ORANGE_CHARGING_020       8490
#define FLASH_COUNT_ORANGE_CHARGING_020        1

#define FLASH_ADDR_ORANGE_CHARGING_021_BASE    (0x00000000 + 0x149000)
#define FLASH_STRIDE_ORANGE_CHARGING_021       8490
#define FLASH_COUNT_ORANGE_CHARGING_021        1

#define FLASH_ADDR_ORANGE_CHARGING_022_BASE    (0x00000000 + 0x14C000)
#define FLASH_STRIDE_ORANGE_CHARGING_022       8490
#define FLASH_COUNT_ORANGE_CHARGING_022        1

#define FLASH_ADDR_ORANGE_CHARGING_023_BASE    (0x00000000 + 0x14F000)
#define FLASH_STRIDE_ORANGE_CHARGING_023       8490
#define FLASH_COUNT_ORANGE_CHARGING_023        1

#define FLASH_ADDR_ORANGE_CHARGING_024_BASE    (0x00000000 + 0x152000)
#define FLASH_STRIDE_ORANGE_CHARGING_024       8490
#define FLASH_COUNT_ORANGE_CHARGING_024        1

#define FLASH_ADDR_ORANGE_CHARGING_025_BASE    (0x00000000 + 0x155000)
#define FLASH_STRIDE_ORANGE_CHARGING_025       8490
#define FLASH_COUNT_ORANGE_CHARGING_025        1

#define FLASH_ADDR_ORANGE_CHARGING_026_BASE    (0x00000000 + 0x158000)
#define FLASH_STRIDE_ORANGE_CHARGING_026       8490
#define FLASH_COUNT_ORANGE_CHARGING_026        1

#define FLASH_ADDR_ORANGE_CHARGING_027_BASE    (0x00000000 + 0x15B000)
#define FLASH_STRIDE_ORANGE_CHARGING_027       8490
#define FLASH_COUNT_ORANGE_CHARGING_027        1

#define FLASH_ADDR_ORANGE_CHARGING_028_BASE    (0x00000000 + 0x15E000)
#define FLASH_STRIDE_ORANGE_CHARGING_028       8490
#define FLASH_COUNT_ORANGE_CHARGING_028        1

#define FLASH_ADDR_ORANGE_CHARGING_029_BASE    (0x00000000 + 0x161000)
#define FLASH_STRIDE_ORANGE_CHARGING_029       8490
#define FLASH_COUNT_ORANGE_CHARGING_029        1

#define FLASH_ADDR_ORANGE_CHARGING_030_BASE    (0x00000000 + 0x164000)
#define FLASH_STRIDE_ORANGE_CHARGING_030       8490
#define FLASH_COUNT_ORANGE_CHARGING_030        1

#define FLASH_ADDR_ORANGE_CHARGING_031_BASE    (0x00000000 + 0x167000)
#define FLASH_STRIDE_ORANGE_CHARGING_031       8490
#define FLASH_COUNT_ORANGE_CHARGING_031        1

#define FLASH_ADDR_ORANGE_CHARGING_032_BASE    (0x00000000 + 0x16A000)
#define FLASH_STRIDE_ORANGE_CHARGING_032       8490
#define FLASH_COUNT_ORANGE_CHARGING_032        1

#define FLASH_ADDR_ORANGE_CHARGING_033_BASE    (0x00000000 + 0x16D000)
#define FLASH_STRIDE_ORANGE_CHARGING_033       8490
#define FLASH_COUNT_ORANGE_CHARGING_033        1

#define FLASH_ADDR_ORANGE_CHARGING_034_BASE    (0x00000000 + 0x170000)
#define FLASH_STRIDE_ORANGE_CHARGING_034       8490
#define FLASH_COUNT_ORANGE_CHARGING_034        1

#define FLASH_ADDR_ORANGE_CHARGING_035_BASE    (0x00000000 + 0x173000)
#define FLASH_STRIDE_ORANGE_CHARGING_035       8490
#define FLASH_COUNT_ORANGE_CHARGING_035        1

#define FLASH_ADDR_ORANGE_CHARGING_036_BASE    (0x00000000 + 0x176000)
#define FLASH_STRIDE_ORANGE_CHARGING_036       8490
#define FLASH_COUNT_ORANGE_CHARGING_036        1

#define FLASH_ADDR_ORANGE_CHARGING_037_BASE    (0x00000000 + 0x179000)
#define FLASH_STRIDE_ORANGE_CHARGING_037       8490
#define FLASH_COUNT_ORANGE_CHARGING_037        1

#define FLASH_ADDR_ORANGE_CHARGING_038_BASE    (0x00000000 + 0x17C000)
#define FLASH_STRIDE_ORANGE_CHARGING_038       8490
#define FLASH_COUNT_ORANGE_CHARGING_038        1

#define FLASH_ADDR_ORANGE_CHARGING_039_BASE    (0x00000000 + 0x17F000)
#define FLASH_STRIDE_ORANGE_CHARGING_039       8490
#define FLASH_COUNT_ORANGE_CHARGING_039        1

#define FLASH_ADDR_ORANGE_CHARGING_040_BASE    (0x00000000 + 0x182000)
#define FLASH_STRIDE_ORANGE_CHARGING_040       8490
#define FLASH_COUNT_ORANGE_CHARGING_040        1

#define FLASH_ADDR_OUT_BASE    (0x00000000 + 0x185000)
#define FLASH_STRIDE_OUT       2178
#define FLASH_COUNT_OUT        1

#define FLASH_ADDR_POWER_PART_1_USB_A_BLUE_BASE    (0x00000000 + 0x186000)
#define FLASH_STRIDE_POWER_PART_1_USB_A_BLUE       5286
#define FLASH_COUNT_POWER_PART_1_USB_A_BLUE        1

#define FLASH_ADDR_POWER_PART_1_USB_A_WHITE_BASE    (0x00000000 + 0x188000)
#define FLASH_STRIDE_POWER_PART_1_USB_A_WHITE       5286
#define FLASH_COUNT_POWER_PART_1_USB_A_WHITE        1

#define FLASH_ADDR_POWER_PART_1_USB_C_BLUE_BASE    (0x00000000 + 0x18A000)
#define FLASH_STRIDE_POWER_PART_1_USB_C_BLUE       5286
#define FLASH_COUNT_POWER_PART_1_USB_C_BLUE        1

#define FLASH_ADDR_POWER_PART_1_USB_C_WHITE_BASE    (0x00000000 + 0x18C000)
#define FLASH_STRIDE_POWER_PART_1_USB_C_WHITE       5286
#define FLASH_COUNT_POWER_PART_1_USB_C_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_1_BLUE_BASE    (0x00000000 + 0x18E000)
#define FLASH_STRIDE_POWER_PART_2_PORT_1_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_1_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_1_WHITE_BASE    (0x00000000 + 0x18F000)
#define FLASH_STRIDE_POWER_PART_2_PORT_1_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_1_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_2_BLUE_BASE    (0x00000000 + 0x190000)
#define FLASH_STRIDE_POWER_PART_2_PORT_2_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_2_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_2_WHITE_BASE    (0x00000000 + 0x191000)
#define FLASH_STRIDE_POWER_PART_2_PORT_2_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_2_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_3_BLUE_BASE    (0x00000000 + 0x192000)
#define FLASH_STRIDE_POWER_PART_2_PORT_3_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_3_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_3_WHITE_BASE    (0x00000000 + 0x193000)
#define FLASH_STRIDE_POWER_PART_2_PORT_3_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_3_WHITE        1

#define FLASH_ADDR_POWER_PART_3_IN_BLUE_BASE    (0x00000000 + 0x194000)
#define FLASH_STRIDE_POWER_PART_3_IN_BLUE       6366
#define FLASH_COUNT_POWER_PART_3_IN_BLUE        1

#define FLASH_ADDR_POWER_PART_3_OUT_BLUE_BASE    (0x00000000 + 0x196000)
#define FLASH_STRIDE_POWER_PART_3_OUT_BLUE       6366
#define FLASH_COUNT_POWER_PART_3_OUT_BLUE        1

#define FLASH_ADDR_POWER_PART_3_WHITE_BASE    (0x00000000 + 0x198000)
#define FLASH_STRIDE_POWER_PART_3_WHITE       6366
#define FLASH_COUNT_POWER_PART_3_WHITE        1

#define FLASH_ADDR_POWER_PART_4_0_BLUE_BASE    (0x00000000 + 0x19A000)
#define FLASH_STRIDE_POWER_PART_4_0_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_0_BLUE        1

#define FLASH_ADDR_POWER_PART_4_0_WHITE_BASE    (0x00000000 + 0x19B000)
#define FLASH_STRIDE_POWER_PART_4_0_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_0_WHITE        1

#define FLASH_ADDR_POWER_PART_4_1_BLUE_BASE    (0x00000000 + 0x19C000)
#define FLASH_STRIDE_POWER_PART_4_1_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_1_BLUE        1

#define FLASH_ADDR_POWER_PART_4_1_WHITE_BASE    (0x00000000 + 0x19D000)
#define FLASH_STRIDE_POWER_PART_4_1_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_1_WHITE        1

#define FLASH_ADDR_POWER_PART_4_2_BLUE_BASE    (0x00000000 + 0x19E000)
#define FLASH_STRIDE_POWER_PART_4_2_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_2_BLUE        1

#define FLASH_ADDR_POWER_PART_4_2_WHITE_BASE    (0x00000000 + 0x19F000)
#define FLASH_STRIDE_POWER_PART_4_2_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_2_WHITE        1

#define FLASH_ADDR_POWER_PART_4_3_BLUE_BASE    (0x00000000 + 0x1A0000)
#define FLASH_STRIDE_POWER_PART_4_3_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_3_BLUE        1

#define FLASH_ADDR_POWER_PART_4_3_WHITE_BASE    (0x00000000 + 0x1A1000)
#define FLASH_STRIDE_POWER_PART_4_3_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_3_WHITE        1

#define FLASH_ADDR_POWER_PART_4_4_BLUE_BASE    (0x00000000 + 0x1A2000)
#define FLASH_STRIDE_POWER_PART_4_4_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_4_BLUE        1

#define FLASH_ADDR_POWER_PART_4_4_WHITE_BASE    (0x00000000 + 0x1A3000)
#define FLASH_STRIDE_POWER_PART_4_4_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_4_WHITE        1

#define FLASH_ADDR_POWER_PART_4_5_BLUE_BASE    (0x00000000 + 0x1A4000)
#define FLASH_STRIDE_POWER_PART_4_5_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_5_BLUE        1

#define FLASH_ADDR_POWER_PART_4_5_WHITE_BASE    (0x00000000 + 0x1A5000)
#define FLASH_STRIDE_POWER_PART_4_5_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_5_WHITE        1

#define FLASH_ADDR_POWER_PART_4_6_BLUE_BASE    (0x00000000 + 0x1A6000)
#define FLASH_STRIDE_POWER_PART_4_6_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_6_BLUE        1

#define FLASH_ADDR_POWER_PART_4_6_WHITE_BASE    (0x00000000 + 0x1A7000)
#define FLASH_STRIDE_POWER_PART_4_6_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_6_WHITE        1

#define FLASH_ADDR_POWER_PART_4_7_BLUE_BASE    (0x00000000 + 0x1A8000)
#define FLASH_STRIDE_POWER_PART_4_7_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_7_BLUE        1

#define FLASH_ADDR_POWER_PART_4_7_WHITE_BASE    (0x00000000 + 0x1A9000)
#define FLASH_STRIDE_POWER_PART_4_7_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_7_WHITE        1

#define FLASH_ADDR_POWER_PART_4_8_BLUE_BASE    (0x00000000 + 0x1AA000)
#define FLASH_STRIDE_POWER_PART_4_8_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_8_BLUE        1

#define FLASH_ADDR_POWER_PART_4_8_WHITE_BASE    (0x00000000 + 0x1AB000)
#define FLASH_STRIDE_POWER_PART_4_8_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_8_WHITE        1

#define FLASH_ADDR_POWER_PART_4_9_BLUE_BASE    (0x00000000 + 0x1AC000)
#define FLASH_STRIDE_POWER_PART_4_9_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_9_BLUE        1

#define FLASH_ADDR_POWER_PART_4_9_WHITE_BASE    (0x00000000 + 0x1AD000)
#define FLASH_STRIDE_POWER_PART_4_9_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_9_WHITE        1

#define FLASH_ADDR_POWER_PART_4_BLUE_BASE    (0x00000000 + 0x1AE000)
#define FLASH_STRIDE_POWER_PART_4_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_BLUE        1

#define FLASH_ADDR_POWER_PART_4_WHITE_BASE    (0x00000000 + 0x1AF000)
#define FLASH_STRIDE_POWER_PART_4_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_WHITE        1

#define FLASH_ADDR_POWER_PART_5_BLUE_BASE    (0x00000000 + 0x1B0000)
#define FLASH_STRIDE_POWER_PART_5_BLUE       3486
#define FLASH_COUNT_POWER_PART_5_BLUE        1

#define FLASH_ADDR_POWER_PART_5_WHITE_BASE    (0x00000000 + 0x1B1000)
#define FLASH_STRIDE_POWER_PART_5_WHITE       3486
#define FLASH_COUNT_POWER_PART_5_WHITE        1

#define FLASH_ADDR_RIGHT_1_ORANGE_BASE    (0x00000000 + 0x1B2000)
#define FLASH_STRIDE_RIGHT_1_ORANGE       11586
#define FLASH_COUNT_RIGHT_1_ORANGE        1

#define FLASH_ADDR_RIGHT_2_BLUE_BASE    (0x00000000 + 0x1B5000)
#define FLASH_STRIDE_RIGHT_2_BLUE       8994
#define FLASH_COUNT_RIGHT_2_BLUE        1

#define FLASH_ADDR_RIGHT_2_ORANGE_BASE    (0x00000000 + 0x1B8000)
#define FLASH_STRIDE_RIGHT_2_ORANGE       8994
#define FLASH_COUNT_RIGHT_2_ORANGE        1

#define FLASH_ADDR_RIGHT_3_BLUE_BASE    (0x00000000 + 0x1BB000)
#define FLASH_STRIDE_RIGHT_3_BLUE       6402
#define FLASH_COUNT_RIGHT_3_BLUE        1

#define FLASH_ADDR_SAFE_BASE    (0x00000000 + 0x1BD000)
#define FLASH_STRIDE_SAFE       12866
#define FLASH_COUNT_SAFE        1

#define FLASH_ADDR_SAFEGUARD_BASE    (0x00000000 + 0x1C1000)
#define FLASH_STRIDE_SAFEGUARD       26466
#define FLASH_COUNT_SAFEGUARD        1

#define FLASH_ADDR_SCREEN_OFF_DURATION_BASE    (0x00000000 + 0x1C8000)
#define FLASH_STRIDE_SCREEN_OFF_DURATION       15426
#define FLASH_COUNT_SCREEN_OFF_DURATION        1

#define FLASH_ADDR_TEMP_ABNORMAL_BASE    (0x00000000 + 0x1CC000)
#define FLASH_STRIDE_TEMP_ABNORMAL       15426
#define FLASH_COUNT_TEMP_ABNORMAL        1

#define FLASH_ADDR_TEMP_ORANGE_BASE    (0x00000000 + 0x1D0000)
#define FLASH_STRIDE_TEMP_ORANGE       12866
#define FLASH_COUNT_TEMP_ORANGE        1

#define FLASH_ADDR_TEMPERATURE_RECOVERY_BASE    (0x00000000 + 0x1D4000)
#define FLASH_STRIDE_TEMPERATURE_RECOVERY       9186
#define FLASH_COUNT_TEMPERATURE_RECOVERY        1

#define FLASH_ADDR_TIAO_BASE    (0x00000000 + 0x1D7000)
#define FLASH_STRIDE_TIAO       678
#define FLASH_COUNT_TIAO        1

#define FLASH_ADDR_TIMER_BASE    (0x00000000 + 0x1D8000)
#define FLASH_STRIDE_TIMER       1026
#define FLASH_COUNT_TIMER        1

#define FLASH_ADDR_TOTAL_VOLTAGE_BASE    (0x00000000 + 0x1D9000)
#define FLASH_STRIDE_TOTAL_VOLTAGE       1986
#define FLASH_COUNT_TOTAL_VOLTAGE        1

#define FLASH_ADDR_VOLTAGE_ABNORMAL_BASE    (0x00000000 + 0x1DA000)
#define FLASH_STRIDE_VOLTAGE_ABNORMAL       15426
#define FLASH_COUNT_VOLTAGE_ABNORMAL        1


/*
 * Per-image index macros — for named access within a category.
 *   addr = FLASH_ADDR_<CAT>_BASE + FLASH_IDX_<CAT>_<ITEM> * FLASH_STRIDE_<CAT>
 */
#define FLASH_IDX_NUM_12_0  0
#define FLASH_IDX_NUM_12_1  1
#define FLASH_IDX_NUM_12_2  2
#define FLASH_IDX_NUM_12_3  3
#define FLASH_IDX_NUM_12_4  4
#define FLASH_IDX_NUM_12_5  5
#define FLASH_IDX_NUM_12_6  6
#define FLASH_IDX_NUM_12_7  7
#define FLASH_IDX_NUM_12_8  8
#define FLASH_IDX_NUM_12_9  9
#define FLASH_IDX_NUM_12__  10
#define FLASH_IDX_NUM_12_A  11
#define FLASH_IDX_NUM_12_B  12
#define FLASH_IDX_NUM_12_C  13
#define FLASH_IDX_NUM_12_D  14
#define FLASH_IDX_NUM_12_E  15
#define FLASH_IDX_NUM_12_F  16
#define FLASH_IDX_NUM_12_G  17
#define FLASH_IDX_NUM_12_H  18
#define FLASH_IDX_NUM_12_I  19
#define FLASH_IDX_NUM_12_J  20
#define FLASH_IDX_NUM_12_K  21
#define FLASH_IDX_NUM_12_L  22
#define FLASH_IDX_NUM_12_M  23
#define FLASH_IDX_NUM_12_N  24
#define FLASH_IDX_NUM_12_O  25
#define FLASH_IDX_NUM_12_P  26
#define FLASH_IDX_NUM_12_Q  27
#define FLASH_IDX_NUM_12_R  28
#define FLASH_IDX_NUM_12_S  29
#define FLASH_IDX_NUM_12_T  30
#define FLASH_IDX_NUM_12_U  31
#define FLASH_IDX_NUM_12_V  32
#define FLASH_IDX_NUM_12_W  33
#define FLASH_IDX_NUM_12_X  34
#define FLASH_IDX_NUM_12_Y  35
#define FLASH_IDX_NUM_12_Z  36
#define FLASH_IDX_NUM_12_Z_COLON  37
#define FLASH_IDX_NUM_12_Z_DEGREE  38
#define FLASH_IDX_NUM_12_Z_DOT  39

#define FLASH_IDX_NUM_16_0  0
#define FLASH_IDX_NUM_16_1  1
#define FLASH_IDX_NUM_16_2  2
#define FLASH_IDX_NUM_16_3  3
#define FLASH_IDX_NUM_16_4  4
#define FLASH_IDX_NUM_16_5  5
#define FLASH_IDX_NUM_16_6  6
#define FLASH_IDX_NUM_16_7  7
#define FLASH_IDX_NUM_16_8  8
#define FLASH_IDX_NUM_16_9  9
#define FLASH_IDX_NUM_16__  10
#define FLASH_IDX_NUM_16_A  11
#define FLASH_IDX_NUM_16_B  12
#define FLASH_IDX_NUM_16_C  13
#define FLASH_IDX_NUM_16_D  14
#define FLASH_IDX_NUM_16_E  15
#define FLASH_IDX_NUM_16_F  16
#define FLASH_IDX_NUM_16_G  17
#define FLASH_IDX_NUM_16_H  18
#define FLASH_IDX_NUM_16_I  19
#define FLASH_IDX_NUM_16_J  20
#define FLASH_IDX_NUM_16_K  21
#define FLASH_IDX_NUM_16_L  22
#define FLASH_IDX_NUM_16_M  23
#define FLASH_IDX_NUM_16_N  24
#define FLASH_IDX_NUM_16_O  25
#define FLASH_IDX_NUM_16_P  26
#define FLASH_IDX_NUM_16_Q  27
#define FLASH_IDX_NUM_16_R  28
#define FLASH_IDX_NUM_16_S  29
#define FLASH_IDX_NUM_16_T  30
#define FLASH_IDX_NUM_16_U  31
#define FLASH_IDX_NUM_16_V  32
#define FLASH_IDX_NUM_16_W  33
#define FLASH_IDX_NUM_16_X  34
#define FLASH_IDX_NUM_16_Y  35
#define FLASH_IDX_NUM_16_Z  36
#define FLASH_IDX_NUM_16_Z_COLON  37
#define FLASH_IDX_NUM_16_Z_DEGREE  38
#define FLASH_IDX_NUM_16_Z_DOT  39

#define FLASH_IDX_NUM_20_0  0
#define FLASH_IDX_NUM_20_1  1
#define FLASH_IDX_NUM_20_2  2
#define FLASH_IDX_NUM_20_3  3
#define FLASH_IDX_NUM_20_4  4
#define FLASH_IDX_NUM_20_5  5
#define FLASH_IDX_NUM_20_6  6
#define FLASH_IDX_NUM_20_7  7
#define FLASH_IDX_NUM_20_8  8
#define FLASH_IDX_NUM_20_9  9

#define FLASH_IDX_NUM_40_0  0
#define FLASH_IDX_NUM_40_1  1
#define FLASH_IDX_NUM_40_2  2
#define FLASH_IDX_NUM_40_3  3
#define FLASH_IDX_NUM_40_4  4
#define FLASH_IDX_NUM_40_5  5
#define FLASH_IDX_NUM_40_6  6
#define FLASH_IDX_NUM_40_7  7
#define FLASH_IDX_NUM_40_8  8
#define FLASH_IDX_NUM_40_9  9
#define FLASH_IDX_NUM_40__  10


/*
 * Absolute flash addresses and sizes for every image.
 */
#define FLASH_ADDR_1800_S_BLUE                (0x00000000 + 0x0000)
#define FLASH_SIZE_1800_S_BLUE                6338
#define FLASH_ADDR_1800_S_WHITE               (0x00000000 + 0x2000)
#define FLASH_SIZE_1800_S_WHITE               6338
#define FLASH_ADDR_300_S_BLUE                 (0x00000000 + 0x4000)
#define FLASH_SIZE_300_S_BLUE                 6338
#define FLASH_ADDR_300_S_WHITE                (0x00000000 + 0x6000)
#define FLASH_SIZE_300_S_WHITE                6338
#define FLASH_ADDR_30_S_BLUE                  (0x00000000 + 0x8000)
#define FLASH_SIZE_30_S_BLUE                  6338
#define FLASH_ADDR_30_S_WHITE                 (0x00000000 + 0xA000)
#define FLASH_SIZE_30_S_WHITE                 6338
#define FLASH_ADDR_60_S_BLUE                  (0x00000000 + 0xC000)
#define FLASH_SIZE_60_S_BLUE                  6338
#define FLASH_ADDR_60_S_WHITE                 (0x00000000 + 0xE000)
#define FLASH_SIZE_60_S_WHITE                 6338
#define FLASH_ADDR_A_CELL_VOLTAGE             (0x00000000 + 0x10000)
#define FLASH_SIZE_A_CELL_VOLTAGE             15426
#define FLASH_ADDR_ABNORMAL_TIME              (0x00000000 + 0x14000)
#define FLASH_SIZE_ABNORMAL_TIME              1474
#define FLASH_ADDR_ABNORMAL_V                 (0x00000000 + 0x15000)
#define FLASH_SIZE_ABNORMAL_V                 1474
#define FLASH_ADDR_BAT_0_BLUE                 (0x00000000 + 0x16000)
#define FLASH_SIZE_BAT_0_BLUE                 5250
#define FLASH_ADDR_BAT_0_ORANGE               (0x00000000 + 0x18000)
#define FLASH_SIZE_BAT_0_ORANGE               5250
#define FLASH_ADDR_BAT_1_BLUE                 (0x00000000 + 0x1A000)
#define FLASH_SIZE_BAT_1_BLUE                 5250
#define FLASH_ADDR_BAT_1_ORANGE               (0x00000000 + 0x1C000)
#define FLASH_SIZE_BAT_1_ORANGE               5250
#define FLASH_ADDR_BAT_2_BLUE                 (0x00000000 + 0x1E000)
#define FLASH_SIZE_BAT_2_BLUE                 5250
#define FLASH_ADDR_BAT_2_ORANGE               (0x00000000 + 0x20000)
#define FLASH_SIZE_BAT_2_ORANGE               5250
#define FLASH_ADDR_BAT_3_BLUE                 (0x00000000 + 0x22000)
#define FLASH_SIZE_BAT_3_BLUE                 5250
#define FLASH_ADDR_BAT_3_ORANGE               (0x00000000 + 0x24000)
#define FLASH_SIZE_BAT_3_ORANGE               5250
#define FLASH_ADDR_BAT_4_BLUE                 (0x00000000 + 0x26000)
#define FLASH_SIZE_BAT_4_BLUE                 5250
#define FLASH_ADDR_BAT_4_ORANGE               (0x00000000 + 0x28000)
#define FLASH_SIZE_BAT_4_ORANGE               5250
#define FLASH_ADDR_BAT_5_BLUE                 (0x00000000 + 0x2A000)
#define FLASH_SIZE_BAT_5_BLUE                 5250
#define FLASH_ADDR_BAT_5_ORANGE               (0x00000000 + 0x2C000)
#define FLASH_SIZE_BAT_5_ORANGE               5250
#define FLASH_ADDR_BAT_6_BLUE                 (0x00000000 + 0x2E000)
#define FLASH_SIZE_BAT_6_BLUE                 5250
#define FLASH_ADDR_BAT_6_ORANGE               (0x00000000 + 0x30000)
#define FLASH_SIZE_BAT_6_ORANGE               5250
#define FLASH_ADDR_BAT_7_BLUE                 (0x00000000 + 0x32000)
#define FLASH_SIZE_BAT_7_BLUE                 5250
#define FLASH_ADDR_BAT_7_ORANGE               (0x00000000 + 0x34000)
#define FLASH_SIZE_BAT_7_ORANGE               5250
#define FLASH_ADDR_BAT_8_BLUE                 (0x00000000 + 0x36000)
#define FLASH_SIZE_BAT_8_BLUE                 5250
#define FLASH_ADDR_BAT_8_ORANGE               (0x00000000 + 0x38000)
#define FLASH_SIZE_BAT_8_ORANGE               5250
#define FLASH_ADDR_BAT_9_BLUE                 (0x00000000 + 0x3A000)
#define FLASH_SIZE_BAT_9_BLUE                 5250
#define FLASH_ADDR_BAT_9_ORANGE               (0x00000000 + 0x3C000)
#define FLASH_SIZE_BAT_9_ORANGE               5250
#define FLASH_ADDR_BAT_NUM                    (0x00000000 + 0x3E000)
#define FLASH_SIZE_BAT_NUM                    2562
#define FLASH_ADDR_BAT_PER_BLUE               (0x00000000 + 0x3F000)
#define FLASH_SIZE_BAT_PER_BLUE               6402
#define FLASH_ADDR_BAT_PER_ORANGE             (0x00000000 + 0x41000)
#define FLASH_SIZE_BAT_PER_ORANGE             6402
#define FLASH_ADDR_BAT_TMP                    (0x00000000 + 0x43000)
#define FLASH_SIZE_BAT_TMP                    15426
#define FLASH_ADDR_BLUE_CHARGING_001          (0x00000000 + 0x47000)
#define FLASH_SIZE_BLUE_CHARGING_001          8490
#define FLASH_ADDR_BLUE_CHARGING_002          (0x00000000 + 0x4A000)
#define FLASH_SIZE_BLUE_CHARGING_002          8490
#define FLASH_ADDR_BLUE_CHARGING_003          (0x00000000 + 0x4D000)
#define FLASH_SIZE_BLUE_CHARGING_003          8490
#define FLASH_ADDR_BLUE_CHARGING_004          (0x00000000 + 0x50000)
#define FLASH_SIZE_BLUE_CHARGING_004          8490
#define FLASH_ADDR_BLUE_CHARGING_005          (0x00000000 + 0x53000)
#define FLASH_SIZE_BLUE_CHARGING_005          8490
#define FLASH_ADDR_BLUE_CHARGING_006          (0x00000000 + 0x56000)
#define FLASH_SIZE_BLUE_CHARGING_006          8490
#define FLASH_ADDR_BLUE_CHARGING_007          (0x00000000 + 0x59000)
#define FLASH_SIZE_BLUE_CHARGING_007          8490
#define FLASH_ADDR_BLUE_CHARGING_008          (0x00000000 + 0x5C000)
#define FLASH_SIZE_BLUE_CHARGING_008          8490
#define FLASH_ADDR_BLUE_CHARGING_009          (0x00000000 + 0x5F000)
#define FLASH_SIZE_BLUE_CHARGING_009          8490
#define FLASH_ADDR_BLUE_CHARGING_010          (0x00000000 + 0x62000)
#define FLASH_SIZE_BLUE_CHARGING_010          8490
#define FLASH_ADDR_BLUE_CHARGING_011          (0x00000000 + 0x65000)
#define FLASH_SIZE_BLUE_CHARGING_011          8490
#define FLASH_ADDR_BLUE_CHARGING_012          (0x00000000 + 0x68000)
#define FLASH_SIZE_BLUE_CHARGING_012          8490
#define FLASH_ADDR_BLUE_CHARGING_013          (0x00000000 + 0x6B000)
#define FLASH_SIZE_BLUE_CHARGING_013          8490
#define FLASH_ADDR_BLUE_CHARGING_014          (0x00000000 + 0x6E000)
#define FLASH_SIZE_BLUE_CHARGING_014          8490
#define FLASH_ADDR_BLUE_CHARGING_015          (0x00000000 + 0x71000)
#define FLASH_SIZE_BLUE_CHARGING_015          8490
#define FLASH_ADDR_BLUE_CHARGING_016          (0x00000000 + 0x74000)
#define FLASH_SIZE_BLUE_CHARGING_016          8490
#define FLASH_ADDR_BLUE_CHARGING_017          (0x00000000 + 0x77000)
#define FLASH_SIZE_BLUE_CHARGING_017          8490
#define FLASH_ADDR_BLUE_CHARGING_018          (0x00000000 + 0x7A000)
#define FLASH_SIZE_BLUE_CHARGING_018          8490
#define FLASH_ADDR_BLUE_CHARGING_019          (0x00000000 + 0x7D000)
#define FLASH_SIZE_BLUE_CHARGING_019          8490
#define FLASH_ADDR_BLUE_CHARGING_020          (0x00000000 + 0x80000)
#define FLASH_SIZE_BLUE_CHARGING_020          8490
#define FLASH_ADDR_BLUE_CHARGING_021          (0x00000000 + 0x83000)
#define FLASH_SIZE_BLUE_CHARGING_021          8490
#define FLASH_ADDR_BLUE_CHARGING_022          (0x00000000 + 0x86000)
#define FLASH_SIZE_BLUE_CHARGING_022          8490
#define FLASH_ADDR_BLUE_CHARGING_023          (0x00000000 + 0x89000)
#define FLASH_SIZE_BLUE_CHARGING_023          8490
#define FLASH_ADDR_BLUE_CHARGING_024          (0x00000000 + 0x8C000)
#define FLASH_SIZE_BLUE_CHARGING_024          8490
#define FLASH_ADDR_BLUE_CHARGING_025          (0x00000000 + 0x8F000)
#define FLASH_SIZE_BLUE_CHARGING_025          8490
#define FLASH_ADDR_BLUE_CHARGING_026          (0x00000000 + 0x92000)
#define FLASH_SIZE_BLUE_CHARGING_026          8490
#define FLASH_ADDR_BLUE_CHARGING_027          (0x00000000 + 0x95000)
#define FLASH_SIZE_BLUE_CHARGING_027          8490
#define FLASH_ADDR_BLUE_CHARGING_028          (0x00000000 + 0x98000)
#define FLASH_SIZE_BLUE_CHARGING_028          8490
#define FLASH_ADDR_BLUE_CHARGING_029          (0x00000000 + 0x9B000)
#define FLASH_SIZE_BLUE_CHARGING_029          8490
#define FLASH_ADDR_BLUE_CHARGING_030          (0x00000000 + 0x9E000)
#define FLASH_SIZE_BLUE_CHARGING_030          8490
#define FLASH_ADDR_BLUE_CHARGING_031          (0x00000000 + 0xA1000)
#define FLASH_SIZE_BLUE_CHARGING_031          8490
#define FLASH_ADDR_BLUE_CHARGING_032          (0x00000000 + 0xA4000)
#define FLASH_SIZE_BLUE_CHARGING_032          8490
#define FLASH_ADDR_BLUE_CHARGING_033          (0x00000000 + 0xA7000)
#define FLASH_SIZE_BLUE_CHARGING_033          8490
#define FLASH_ADDR_BLUE_CHARGING_034          (0x00000000 + 0xAA000)
#define FLASH_SIZE_BLUE_CHARGING_034          8490
#define FLASH_ADDR_BLUE_CHARGING_035          (0x00000000 + 0xAD000)
#define FLASH_SIZE_BLUE_CHARGING_035          8490
#define FLASH_ADDR_BLUE_CHARGING_036          (0x00000000 + 0xB0000)
#define FLASH_SIZE_BLUE_CHARGING_036          8490
#define FLASH_ADDR_BLUE_CHARGING_037          (0x00000000 + 0xB3000)
#define FLASH_SIZE_BLUE_CHARGING_037          8490
#define FLASH_ADDR_BLUE_CHARGING_038          (0x00000000 + 0xB6000)
#define FLASH_SIZE_BLUE_CHARGING_038          8490
#define FLASH_ADDR_BLUE_CHARGING_039          (0x00000000 + 0xB9000)
#define FLASH_SIZE_BLUE_CHARGING_039          8490
#define FLASH_ADDR_BLUE_CHARGING_040          (0x00000000 + 0xBC000)
#define FLASH_SIZE_BLUE_CHARGING_040          8490
#define FLASH_ADDR_CHARGE_HIGH_TEMP_PRO       (0x00000000 + 0xBF000)
#define FLASH_SIZE_CHARGE_HIGH_TEMP_PRO       17346
#define FLASH_ADDR_CHARGE_TEMP                (0x00000000 + 0xC4000)
#define FLASH_SIZE_CHARGE_TEMP                2718
#define FLASH_ADDR_CI                         (0x00000000 + 0xC5000)
#define FLASH_SIZE_CI                         1346
#define FLASH_ADDR_CIRCUIT_PROTECTION         (0x00000000 + 0xC6000)
#define FLASH_SIZE_CIRCUIT_PROTECTION         12866
#define FLASH_ADDR_CIRCUIT_PROTECTION_TEXT    (0x00000000 + 0xCA000)
#define FLASH_SIZE_CIRCUIT_PROTECTION_TEXT    17346
#define FLASH_ADDR_CIRCUIT_RECOVERY           (0x00000000 + 0xCF000)
#define FLASH_SIZE_CIRCUIT_RECOVERY           9186
#define FLASH_ADDR_CYCLE_INDEX                (0x00000000 + 0xD2000)
#define FLASH_SIZE_CYCLE_INDEX                7746
#define FLASH_ADDR_DI                         (0x00000000 + 0xD4000)
#define FLASH_SIZE_DI                         678
#define FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO    (0x00000000 + 0xD5000)
#define FLASH_SIZE_DISCHARGE_HIGH_TEMP_PRO    17346
#define FLASH_ADDR_DISCHARGE_TEMP             (0x00000000 + 0xDA000)
#define FLASH_SIZE_DISCHARGE_TEMP             2718
#define FLASH_ADDR_DOUBLE_CLICK_SWITCH        (0x00000000 + 0xDB000)
#define FLASH_SIZE_DOUBLE_CLICK_SWITCH        9186
#define FLASH_ADDR_DOUHAO                     (0x00000000 + 0xDE000)
#define FLASH_SIZE_DOUHAO                     450
#define FLASH_ADDR_GONG                       (0x00000000 + 0xDF000)
#define FLASH_SIZE_GONG                       678
#define FLASH_ADDR_HEALTH                     (0x00000000 + 0xE0000)
#define FLASH_SIZE_HEALTH                     7746
#define FLASH_ADDR_LEFT_1_ORANGE              (0x00000000 + 0xE2000)
#define FLASH_SIZE_LEFT_1_ORANGE              11586
#define FLASH_ADDR_LEFT_2_BLUE                (0x00000000 + 0xE5000)
#define FLASH_SIZE_LEFT_2_BLUE                8994
#define FLASH_ADDR_LEFT_2_ORANGE              (0x00000000 + 0xE8000)
#define FLASH_SIZE_LEFT_2_ORANGE              8994
#define FLASH_ADDR_LEFT_3_BLUE                (0x00000000 + 0xEB000)
#define FLASH_SIZE_LEFT_3_BLUE                6402
#define FLASH_ADDR_MINI                       (0x00000000 + 0xED000)
#define FLASH_SIZE_MINI                       2946
#define FLASH_ADDR_NO_ABNORMAL                (0x00000000 + 0xEE000)
#define FLASH_SIZE_NO_ABNORMAL                5026
#define FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO       (0x00000000 + 0xF0000)
#define FLASH_SIZE_NOAMAL_HIGH_TEMP_PRO       17346
#define FLASH_ADDR_NOAMAL_TEMP                (0x00000000 + 0xF5000)
#define FLASH_SIZE_NOAMAL_TEMP                2718
#define FLASH_ADDR_NUM_12_0                   (0x00000000 + 0xF6000)
#define FLASH_SIZE_NUM_12_0                   226
#define FLASH_ADDR_NUM_12_1                   (0x00000000 + 0xF615A)
#define FLASH_SIZE_NUM_12_1                   186
#define FLASH_ADDR_NUM_12_2                   (0x00000000 + 0xF62B4)
#define FLASH_SIZE_NUM_12_2                   226
#define FLASH_ADDR_NUM_12_3                   (0x00000000 + 0xF640E)
#define FLASH_SIZE_NUM_12_3                   226
#define FLASH_ADDR_NUM_12_4                   (0x00000000 + 0xF6568)
#define FLASH_SIZE_NUM_12_4                   266
#define FLASH_ADDR_NUM_12_5                   (0x00000000 + 0xF66C2)
#define FLASH_SIZE_NUM_12_5                   226
#define FLASH_ADDR_NUM_12_6                   (0x00000000 + 0xF681C)
#define FLASH_SIZE_NUM_12_6                   226
#define FLASH_ADDR_NUM_12_7                   (0x00000000 + 0xF6976)
#define FLASH_SIZE_NUM_12_7                   226
#define FLASH_ADDR_NUM_12_8                   (0x00000000 + 0xF6AD0)
#define FLASH_SIZE_NUM_12_8                   226
#define FLASH_ADDR_NUM_12_9                   (0x00000000 + 0xF6C2A)
#define FLASH_SIZE_NUM_12_9                   226
#define FLASH_ADDR_NUM_12                     (0x00000000 + 0xF6D84)
#define FLASH_SIZE_NUM_12                     226
#define FLASH_ADDR_NUM_12_A                   (0x00000000 + 0xF6EDE)
#define FLASH_SIZE_NUM_12_A                   266
#define FLASH_ADDR_NUM_12_B                   (0x00000000 + 0xF7038)
#define FLASH_SIZE_NUM_12_B                   226
#define FLASH_ADDR_NUM_12_C                   (0x00000000 + 0xF7192)
#define FLASH_SIZE_NUM_12_C                   266
#define FLASH_ADDR_NUM_12_D                   (0x00000000 + 0xF72EC)
#define FLASH_SIZE_NUM_12_D                   266
#define FLASH_ADDR_NUM_12_E                   (0x00000000 + 0xF7446)
#define FLASH_SIZE_NUM_12_E                   226
#define FLASH_ADDR_NUM_12_F                   (0x00000000 + 0xF75A0)
#define FLASH_SIZE_NUM_12_F                   226
#define FLASH_ADDR_NUM_12_G                   (0x00000000 + 0xF76FA)
#define FLASH_SIZE_NUM_12_G                   266
#define FLASH_ADDR_NUM_12_H                   (0x00000000 + 0xF7854)
#define FLASH_SIZE_NUM_12_H                   266
#define FLASH_ADDR_NUM_12_I                   (0x00000000 + 0xF79AE)
#define FLASH_SIZE_NUM_12_I                   186
#define FLASH_ADDR_NUM_12_J                   (0x00000000 + 0xF7B08)
#define FLASH_SIZE_NUM_12_J                   226
#define FLASH_ADDR_NUM_12_K                   (0x00000000 + 0xF7C62)
#define FLASH_SIZE_NUM_12_K                   226
#define FLASH_ADDR_NUM_12_L                   (0x00000000 + 0xF7DBC)
#define FLASH_SIZE_NUM_12_L                   226
#define FLASH_ADDR_NUM_12_M                   (0x00000000 + 0xF7F16)
#define FLASH_SIZE_NUM_12_M                   306
#define FLASH_ADDR_NUM_12_N                   (0x00000000 + 0xF8070)
#define FLASH_SIZE_NUM_12_N                   266
#define FLASH_ADDR_NUM_12_O                   (0x00000000 + 0xF81CA)
#define FLASH_SIZE_NUM_12_O                   266
#define FLASH_ADDR_NUM_12_P                   (0x00000000 + 0xF8324)
#define FLASH_SIZE_NUM_12_P                   226
#define FLASH_ADDR_NUM_12_Q                   (0x00000000 + 0xF847E)
#define FLASH_SIZE_NUM_12_Q                   266
#define FLASH_ADDR_NUM_12_R                   (0x00000000 + 0xF85D8)
#define FLASH_SIZE_NUM_12_R                   226
#define FLASH_ADDR_NUM_12_S                   (0x00000000 + 0xF8732)
#define FLASH_SIZE_NUM_12_S                   226
#define FLASH_ADDR_NUM_12_T                   (0x00000000 + 0xF888C)
#define FLASH_SIZE_NUM_12_T                   226
#define FLASH_ADDR_NUM_12_U                   (0x00000000 + 0xF89E6)
#define FLASH_SIZE_NUM_12_U                   266
#define FLASH_ADDR_NUM_12_V                   (0x00000000 + 0xF8B40)
#define FLASH_SIZE_NUM_12_V                   266
#define FLASH_ADDR_NUM_12_W                   (0x00000000 + 0xF8C9A)
#define FLASH_SIZE_NUM_12_W                   346
#define FLASH_ADDR_NUM_12_X                   (0x00000000 + 0xF8DF4)
#define FLASH_SIZE_NUM_12_X                   266
#define FLASH_ADDR_NUM_12_Y                   (0x00000000 + 0xF8F4E)
#define FLASH_SIZE_NUM_12_Y                   266
#define FLASH_ADDR_NUM_12_Z                   (0x00000000 + 0xF90A8)
#define FLASH_SIZE_NUM_12_Z                   266
#define FLASH_ADDR_NUM_12_Z_COLON             (0x00000000 + 0xF9202)
#define FLASH_SIZE_NUM_12_Z_COLON             186
#define FLASH_ADDR_NUM_12_Z_DEGREE            (0x00000000 + 0xF935C)
#define FLASH_SIZE_NUM_12_Z_DEGREE            346
#define FLASH_ADDR_NUM_12_Z_DOT               (0x00000000 + 0xF94B6)
#define FLASH_SIZE_NUM_12_Z_DOT               146
#define FLASH_ADDR_NUM_16_0                   (0x00000000 + 0xFA000)
#define FLASH_SIZE_NUM_16_0                   450
#define FLASH_ADDR_NUM_16_1                   (0x00000000 + 0xFA302)
#define FLASH_SIZE_NUM_16_1                   322
#define FLASH_ADDR_NUM_16_2                   (0x00000000 + 0xFA604)
#define FLASH_SIZE_NUM_16_2                   450
#define FLASH_ADDR_NUM_16_3                   (0x00000000 + 0xFA906)
#define FLASH_SIZE_NUM_16_3                   450
#define FLASH_ADDR_NUM_16_4                   (0x00000000 + 0xFAC08)
#define FLASH_SIZE_NUM_16_4                   450
#define FLASH_ADDR_NUM_16_5                   (0x00000000 + 0xFAF0A)
#define FLASH_SIZE_NUM_16_5                   450
#define FLASH_ADDR_NUM_16_6                   (0x00000000 + 0xFB20C)
#define FLASH_SIZE_NUM_16_6                   450
#define FLASH_ADDR_NUM_16_7                   (0x00000000 + 0xFB50E)
#define FLASH_SIZE_NUM_16_7                   450
#define FLASH_ADDR_NUM_16_8                   (0x00000000 + 0xFB810)
#define FLASH_SIZE_NUM_16_8                   450
#define FLASH_ADDR_NUM_16_9                   (0x00000000 + 0xFBB12)
#define FLASH_SIZE_NUM_16_9                   450
#define FLASH_ADDR_NUM_16                     (0x00000000 + 0xFBE14)
#define FLASH_SIZE_NUM_16                     322
#define FLASH_ADDR_NUM_16_A                   (0x00000000 + 0xFC116)
#define FLASH_SIZE_NUM_16_A                   514
#define FLASH_ADDR_NUM_16_B                   (0x00000000 + 0xFC418)
#define FLASH_SIZE_NUM_16_B                   450
#define FLASH_ADDR_NUM_16_C                   (0x00000000 + 0xFC71A)
#define FLASH_SIZE_NUM_16_C                   514
#define FLASH_ADDR_NUM_16_D                   (0x00000000 + 0xFCA1C)
#define FLASH_SIZE_NUM_16_D                   514
#define FLASH_ADDR_NUM_16_E                   (0x00000000 + 0xFCD1E)
#define FLASH_SIZE_NUM_16_E                   386
#define FLASH_ADDR_NUM_16_F                   (0x00000000 + 0xFD020)
#define FLASH_SIZE_NUM_16_F                   386
#define FLASH_ADDR_NUM_16_G                   (0x00000000 + 0xFD322)
#define FLASH_SIZE_NUM_16_G                   514
#define FLASH_ADDR_NUM_16_H                   (0x00000000 + 0xFD624)
#define FLASH_SIZE_NUM_16_H                   450
#define FLASH_ADDR_NUM_16_I                   (0x00000000 + 0xFD926)
#define FLASH_SIZE_NUM_16_I                   258
#define FLASH_ADDR_NUM_16_J                   (0x00000000 + 0xFDC28)
#define FLASH_SIZE_NUM_16_J                   386
#define FLASH_ADDR_NUM_16_K                   (0x00000000 + 0xFDF2A)
#define FLASH_SIZE_NUM_16_K                   450
#define FLASH_ADDR_NUM_16_L                   (0x00000000 + 0xFE22C)
#define FLASH_SIZE_NUM_16_L                   386
#define FLASH_ADDR_NUM_16_M                   (0x00000000 + 0xFE52E)
#define FLASH_SIZE_NUM_16_M                   578
#define FLASH_ADDR_NUM_16_N                   (0x00000000 + 0xFE830)
#define FLASH_SIZE_NUM_16_N                   450
#define FLASH_ADDR_NUM_16_O                   (0x00000000 + 0xFEB32)
#define FLASH_SIZE_NUM_16_O                   514
#define FLASH_ADDR_NUM_16_P                   (0x00000000 + 0xFEE34)
#define FLASH_SIZE_NUM_16_P                   386
#define FLASH_ADDR_NUM_16_Q                   (0x00000000 + 0xFF136)
#define FLASH_SIZE_NUM_16_Q                   514
#define FLASH_ADDR_NUM_16_R                   (0x00000000 + 0xFF438)
#define FLASH_SIZE_NUM_16_R                   450
#define FLASH_ADDR_NUM_16_S                   (0x00000000 + 0xFF73A)
#define FLASH_SIZE_NUM_16_S                   386
#define FLASH_ADDR_NUM_16_T                   (0x00000000 + 0xFFA3C)
#define FLASH_SIZE_NUM_16_T                   450
#define FLASH_ADDR_NUM_16_U                   (0x00000000 + 0xFFD3E)
#define FLASH_SIZE_NUM_16_U                   450
#define FLASH_ADDR_NUM_16_V                   (0x00000000 + 0x100040)
#define FLASH_SIZE_NUM_16_V                   514
#define FLASH_ADDR_NUM_16_W                   (0x00000000 + 0x100342)
#define FLASH_SIZE_NUM_16_W                   706
#define FLASH_ADDR_NUM_16_X                   (0x00000000 + 0x100644)
#define FLASH_SIZE_NUM_16_X                   514
#define FLASH_ADDR_NUM_16_Y                   (0x00000000 + 0x100946)
#define FLASH_SIZE_NUM_16_Y                   450
#define FLASH_ADDR_NUM_16_Z                   (0x00000000 + 0x100C48)
#define FLASH_SIZE_NUM_16_Z                   450
#define FLASH_ADDR_NUM_16_Z_COLON             (0x00000000 + 0x100F4A)
#define FLASH_SIZE_NUM_16_Z_COLON             258
#define FLASH_ADDR_NUM_16_Z_DEGREE            (0x00000000 + 0x10124C)
#define FLASH_SIZE_NUM_16_Z_DEGREE            770
#define FLASH_ADDR_NUM_16_Z_DOT               (0x00000000 + 0x10154E)
#define FLASH_SIZE_NUM_16_Z_DOT               258
#define FLASH_ADDR_NUM_20_0                   (0x00000000 + 0x102000)
#define FLASH_SIZE_NUM_20_0                   738
#define FLASH_ADDR_NUM_20_1                   (0x00000000 + 0x1022E2)
#define FLASH_SIZE_NUM_20_1                   738
#define FLASH_ADDR_NUM_20_2                   (0x00000000 + 0x1025C4)
#define FLASH_SIZE_NUM_20_2                   642
#define FLASH_ADDR_NUM_20_3                   (0x00000000 + 0x1028A6)
#define FLASH_SIZE_NUM_20_3                   642
#define FLASH_ADDR_NUM_20_4                   (0x00000000 + 0x102B88)
#define FLASH_SIZE_NUM_20_4                   642
#define FLASH_ADDR_NUM_20_5                   (0x00000000 + 0x102E6A)
#define FLASH_SIZE_NUM_20_5                   642
#define FLASH_ADDR_NUM_20_6                   (0x00000000 + 0x10314C)
#define FLASH_SIZE_NUM_20_6                   642
#define FLASH_ADDR_NUM_20_7                   (0x00000000 + 0x10342E)
#define FLASH_SIZE_NUM_20_7                   642
#define FLASH_ADDR_NUM_20_8                   (0x00000000 + 0x103710)
#define FLASH_SIZE_NUM_20_8                   642
#define FLASH_ADDR_NUM_20_9                   (0x00000000 + 0x1039F2)
#define FLASH_SIZE_NUM_20_9                   642
#define FLASH_ADDR_NUM_20_COLON               (0x00000000 + 0x104000)
#define FLASH_SIZE_NUM_20_COLON               450
#define FLASH_ADDR_NUM_40_0                   (0x00000000 + 0x105000)
#define FLASH_SIZE_NUM_40_0                   1986
#define FLASH_ADDR_NUM_40_1                   (0x00000000 + 0x1057C2)
#define FLASH_SIZE_NUM_40_1                   1346
#define FLASH_ADDR_NUM_40_2                   (0x00000000 + 0x105F84)
#define FLASH_SIZE_NUM_40_2                   1986
#define FLASH_ADDR_NUM_40_3                   (0x00000000 + 0x106746)
#define FLASH_SIZE_NUM_40_3                   1986
#define FLASH_ADDR_NUM_40_4                   (0x00000000 + 0x106F08)
#define FLASH_SIZE_NUM_40_4                   1986
#define FLASH_ADDR_NUM_40_5                   (0x00000000 + 0x1076CA)
#define FLASH_SIZE_NUM_40_5                   1986
#define FLASH_ADDR_NUM_40_6                   (0x00000000 + 0x107E8C)
#define FLASH_SIZE_NUM_40_6                   1986
#define FLASH_ADDR_NUM_40_7                   (0x00000000 + 0x10864E)
#define FLASH_SIZE_NUM_40_7                   1986
#define FLASH_ADDR_NUM_40_8                   (0x00000000 + 0x108E10)
#define FLASH_SIZE_NUM_40_8                   1986
#define FLASH_ADDR_NUM_40_9                   (0x00000000 + 0x1095D2)
#define FLASH_SIZE_NUM_40_9                   1986
#define FLASH_ADDR_NUM_40                     (0x00000000 + 0x109D94)
#define FLASH_SIZE_NUM_40                     1346
#define FLASH_ADDR_NUM_40_DEGREE              (0x00000000 + 0x10B000)
#define FLASH_SIZE_NUM_40_DEGREE              1346
#define FLASH_ADDR_NUM_40_PERCENT             (0x00000000 + 0x10C000)
#define FLASH_SIZE_NUM_40_PERCENT             1346
#define FLASH_ADDR_ORANGE_CHARGING_001        (0x00000000 + 0x10D000)
#define FLASH_SIZE_ORANGE_CHARGING_001        8490
#define FLASH_ADDR_ORANGE_CHARGING_002        (0x00000000 + 0x110000)
#define FLASH_SIZE_ORANGE_CHARGING_002        8490
#define FLASH_ADDR_ORANGE_CHARGING_003        (0x00000000 + 0x113000)
#define FLASH_SIZE_ORANGE_CHARGING_003        8490
#define FLASH_ADDR_ORANGE_CHARGING_004        (0x00000000 + 0x116000)
#define FLASH_SIZE_ORANGE_CHARGING_004        8490
#define FLASH_ADDR_ORANGE_CHARGING_005        (0x00000000 + 0x119000)
#define FLASH_SIZE_ORANGE_CHARGING_005        8490
#define FLASH_ADDR_ORANGE_CHARGING_006        (0x00000000 + 0x11C000)
#define FLASH_SIZE_ORANGE_CHARGING_006        8490
#define FLASH_ADDR_ORANGE_CHARGING_007        (0x00000000 + 0x11F000)
#define FLASH_SIZE_ORANGE_CHARGING_007        8490
#define FLASH_ADDR_ORANGE_CHARGING_008        (0x00000000 + 0x122000)
#define FLASH_SIZE_ORANGE_CHARGING_008        8490
#define FLASH_ADDR_ORANGE_CHARGING_009        (0x00000000 + 0x125000)
#define FLASH_SIZE_ORANGE_CHARGING_009        8490
#define FLASH_ADDR_ORANGE_CHARGING_010        (0x00000000 + 0x128000)
#define FLASH_SIZE_ORANGE_CHARGING_010        8490
#define FLASH_ADDR_ORANGE_CHARGING_011        (0x00000000 + 0x12B000)
#define FLASH_SIZE_ORANGE_CHARGING_011        8490
#define FLASH_ADDR_ORANGE_CHARGING_012        (0x00000000 + 0x12E000)
#define FLASH_SIZE_ORANGE_CHARGING_012        8490
#define FLASH_ADDR_ORANGE_CHARGING_013        (0x00000000 + 0x131000)
#define FLASH_SIZE_ORANGE_CHARGING_013        8490
#define FLASH_ADDR_ORANGE_CHARGING_014        (0x00000000 + 0x134000)
#define FLASH_SIZE_ORANGE_CHARGING_014        8490
#define FLASH_ADDR_ORANGE_CHARGING_015        (0x00000000 + 0x137000)
#define FLASH_SIZE_ORANGE_CHARGING_015        8490
#define FLASH_ADDR_ORANGE_CHARGING_016        (0x00000000 + 0x13A000)
#define FLASH_SIZE_ORANGE_CHARGING_016        8490
#define FLASH_ADDR_ORANGE_CHARGING_017        (0x00000000 + 0x13D000)
#define FLASH_SIZE_ORANGE_CHARGING_017        8490
#define FLASH_ADDR_ORANGE_CHARGING_018        (0x00000000 + 0x140000)
#define FLASH_SIZE_ORANGE_CHARGING_018        8490
#define FLASH_ADDR_ORANGE_CHARGING_019        (0x00000000 + 0x143000)
#define FLASH_SIZE_ORANGE_CHARGING_019        8490
#define FLASH_ADDR_ORANGE_CHARGING_020        (0x00000000 + 0x146000)
#define FLASH_SIZE_ORANGE_CHARGING_020        8490
#define FLASH_ADDR_ORANGE_CHARGING_021        (0x00000000 + 0x149000)
#define FLASH_SIZE_ORANGE_CHARGING_021        8490
#define FLASH_ADDR_ORANGE_CHARGING_022        (0x00000000 + 0x14C000)
#define FLASH_SIZE_ORANGE_CHARGING_022        8490
#define FLASH_ADDR_ORANGE_CHARGING_023        (0x00000000 + 0x14F000)
#define FLASH_SIZE_ORANGE_CHARGING_023        8490
#define FLASH_ADDR_ORANGE_CHARGING_024        (0x00000000 + 0x152000)
#define FLASH_SIZE_ORANGE_CHARGING_024        8490
#define FLASH_ADDR_ORANGE_CHARGING_025        (0x00000000 + 0x155000)
#define FLASH_SIZE_ORANGE_CHARGING_025        8490
#define FLASH_ADDR_ORANGE_CHARGING_026        (0x00000000 + 0x158000)
#define FLASH_SIZE_ORANGE_CHARGING_026        8490
#define FLASH_ADDR_ORANGE_CHARGING_027        (0x00000000 + 0x15B000)
#define FLASH_SIZE_ORANGE_CHARGING_027        8490
#define FLASH_ADDR_ORANGE_CHARGING_028        (0x00000000 + 0x15E000)
#define FLASH_SIZE_ORANGE_CHARGING_028        8490
#define FLASH_ADDR_ORANGE_CHARGING_029        (0x00000000 + 0x161000)
#define FLASH_SIZE_ORANGE_CHARGING_029        8490
#define FLASH_ADDR_ORANGE_CHARGING_030        (0x00000000 + 0x164000)
#define FLASH_SIZE_ORANGE_CHARGING_030        8490
#define FLASH_ADDR_ORANGE_CHARGING_031        (0x00000000 + 0x167000)
#define FLASH_SIZE_ORANGE_CHARGING_031        8490
#define FLASH_ADDR_ORANGE_CHARGING_032        (0x00000000 + 0x16A000)
#define FLASH_SIZE_ORANGE_CHARGING_032        8490
#define FLASH_ADDR_ORANGE_CHARGING_033        (0x00000000 + 0x16D000)
#define FLASH_SIZE_ORANGE_CHARGING_033        8490
#define FLASH_ADDR_ORANGE_CHARGING_034        (0x00000000 + 0x170000)
#define FLASH_SIZE_ORANGE_CHARGING_034        8490
#define FLASH_ADDR_ORANGE_CHARGING_035        (0x00000000 + 0x173000)
#define FLASH_SIZE_ORANGE_CHARGING_035        8490
#define FLASH_ADDR_ORANGE_CHARGING_036        (0x00000000 + 0x176000)
#define FLASH_SIZE_ORANGE_CHARGING_036        8490
#define FLASH_ADDR_ORANGE_CHARGING_037        (0x00000000 + 0x179000)
#define FLASH_SIZE_ORANGE_CHARGING_037        8490
#define FLASH_ADDR_ORANGE_CHARGING_038        (0x00000000 + 0x17C000)
#define FLASH_SIZE_ORANGE_CHARGING_038        8490
#define FLASH_ADDR_ORANGE_CHARGING_039        (0x00000000 + 0x17F000)
#define FLASH_SIZE_ORANGE_CHARGING_039        8490
#define FLASH_ADDR_ORANGE_CHARGING_040        (0x00000000 + 0x182000)
#define FLASH_SIZE_ORANGE_CHARGING_040        8490
#define FLASH_ADDR_OUT                        (0x00000000 + 0x185000)
#define FLASH_SIZE_OUT                        2178
#define FLASH_ADDR_POWER_PART_1_USB_A_BLUE    (0x00000000 + 0x186000)
#define FLASH_SIZE_POWER_PART_1_USB_A_BLUE    5286
#define FLASH_ADDR_POWER_PART_1_USB_A_WHITE   (0x00000000 + 0x188000)
#define FLASH_SIZE_POWER_PART_1_USB_A_WHITE   5286
#define FLASH_ADDR_POWER_PART_1_USB_C_BLUE    (0x00000000 + 0x18A000)
#define FLASH_SIZE_POWER_PART_1_USB_C_BLUE    5286
#define FLASH_ADDR_POWER_PART_1_USB_C_WHITE   (0x00000000 + 0x18C000)
#define FLASH_SIZE_POWER_PART_1_USB_C_WHITE   5286
#define FLASH_ADDR_POWER_PART_2_PORT_1_BLUE   (0x00000000 + 0x18E000)
#define FLASH_SIZE_POWER_PART_2_PORT_1_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_1_WHITE  (0x00000000 + 0x18F000)
#define FLASH_SIZE_POWER_PART_2_PORT_1_WHITE  1506
#define FLASH_ADDR_POWER_PART_2_PORT_2_BLUE   (0x00000000 + 0x190000)
#define FLASH_SIZE_POWER_PART_2_PORT_2_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_2_WHITE  (0x00000000 + 0x191000)
#define FLASH_SIZE_POWER_PART_2_PORT_2_WHITE  1506
#define FLASH_ADDR_POWER_PART_2_PORT_3_BLUE   (0x00000000 + 0x192000)
#define FLASH_SIZE_POWER_PART_2_PORT_3_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_3_WHITE  (0x00000000 + 0x193000)
#define FLASH_SIZE_POWER_PART_2_PORT_3_WHITE  1506
#define FLASH_ADDR_POWER_PART_3_IN_BLUE       (0x00000000 + 0x194000)
#define FLASH_SIZE_POWER_PART_3_IN_BLUE       6366
#define FLASH_ADDR_POWER_PART_3_OUT_BLUE      (0x00000000 + 0x196000)
#define FLASH_SIZE_POWER_PART_3_OUT_BLUE      6366
#define FLASH_ADDR_POWER_PART_3_WHITE         (0x00000000 + 0x198000)
#define FLASH_SIZE_POWER_PART_3_WHITE         6366
#define FLASH_ADDR_POWER_PART_4_0_BLUE        (0x00000000 + 0x19A000)
#define FLASH_SIZE_POWER_PART_4_0_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_0_WHITE       (0x00000000 + 0x19B000)
#define FLASH_SIZE_POWER_PART_4_0_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_1_BLUE        (0x00000000 + 0x19C000)
#define FLASH_SIZE_POWER_PART_4_1_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_1_WHITE       (0x00000000 + 0x19D000)
#define FLASH_SIZE_POWER_PART_4_1_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_2_BLUE        (0x00000000 + 0x19E000)
#define FLASH_SIZE_POWER_PART_4_2_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_2_WHITE       (0x00000000 + 0x19F000)
#define FLASH_SIZE_POWER_PART_4_2_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_3_BLUE        (0x00000000 + 0x1A0000)
#define FLASH_SIZE_POWER_PART_4_3_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_3_WHITE       (0x00000000 + 0x1A1000)
#define FLASH_SIZE_POWER_PART_4_3_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_4_BLUE        (0x00000000 + 0x1A2000)
#define FLASH_SIZE_POWER_PART_4_4_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_4_WHITE       (0x00000000 + 0x1A3000)
#define FLASH_SIZE_POWER_PART_4_4_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_5_BLUE        (0x00000000 + 0x1A4000)
#define FLASH_SIZE_POWER_PART_4_5_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_5_WHITE       (0x00000000 + 0x1A5000)
#define FLASH_SIZE_POWER_PART_4_5_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_6_BLUE        (0x00000000 + 0x1A6000)
#define FLASH_SIZE_POWER_PART_4_6_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_6_WHITE       (0x00000000 + 0x1A7000)
#define FLASH_SIZE_POWER_PART_4_6_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_7_BLUE        (0x00000000 + 0x1A8000)
#define FLASH_SIZE_POWER_PART_4_7_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_7_WHITE       (0x00000000 + 0x1A9000)
#define FLASH_SIZE_POWER_PART_4_7_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_8_BLUE        (0x00000000 + 0x1AA000)
#define FLASH_SIZE_POWER_PART_4_8_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_8_WHITE       (0x00000000 + 0x1AB000)
#define FLASH_SIZE_POWER_PART_4_8_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_9_BLUE        (0x00000000 + 0x1AC000)
#define FLASH_SIZE_POWER_PART_4_9_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_9_WHITE       (0x00000000 + 0x1AD000)
#define FLASH_SIZE_POWER_PART_4_9_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_BLUE          (0x00000000 + 0x1AE000)
#define FLASH_SIZE_POWER_PART_4_BLUE          1866
#define FLASH_ADDR_POWER_PART_4_WHITE         (0x00000000 + 0x1AF000)
#define FLASH_SIZE_POWER_PART_4_WHITE         1866
#define FLASH_ADDR_POWER_PART_5_BLUE          (0x00000000 + 0x1B0000)
#define FLASH_SIZE_POWER_PART_5_BLUE          3486
#define FLASH_ADDR_POWER_PART_5_WHITE         (0x00000000 + 0x1B1000)
#define FLASH_SIZE_POWER_PART_5_WHITE         3486
#define FLASH_ADDR_RIGHT_1_ORANGE             (0x00000000 + 0x1B2000)
#define FLASH_SIZE_RIGHT_1_ORANGE             11586
#define FLASH_ADDR_RIGHT_2_BLUE               (0x00000000 + 0x1B5000)
#define FLASH_SIZE_RIGHT_2_BLUE               8994
#define FLASH_ADDR_RIGHT_2_ORANGE             (0x00000000 + 0x1B8000)
#define FLASH_SIZE_RIGHT_2_ORANGE             8994
#define FLASH_ADDR_RIGHT_3_BLUE               (0x00000000 + 0x1BB000)
#define FLASH_SIZE_RIGHT_3_BLUE               6402
#define FLASH_ADDR_SAFE                       (0x00000000 + 0x1BD000)
#define FLASH_SIZE_SAFE                       12866
#define FLASH_ADDR_SAFEGUARD                  (0x00000000 + 0x1C1000)
#define FLASH_SIZE_SAFEGUARD                  26466
#define FLASH_ADDR_SCREEN_OFF_DURATION        (0x00000000 + 0x1C8000)
#define FLASH_SIZE_SCREEN_OFF_DURATION        15426
#define FLASH_ADDR_TEMP_ABNORMAL              (0x00000000 + 0x1CC000)
#define FLASH_SIZE_TEMP_ABNORMAL              15426
#define FLASH_ADDR_TEMP_ORANGE                (0x00000000 + 0x1D0000)
#define FLASH_SIZE_TEMP_ORANGE                12866
#define FLASH_ADDR_TEMPERATURE_RECOVERY       (0x00000000 + 0x1D4000)
#define FLASH_SIZE_TEMPERATURE_RECOVERY       9186
#define FLASH_ADDR_TIAO                       (0x00000000 + 0x1D7000)
#define FLASH_SIZE_TIAO                       678
#define FLASH_ADDR_TIMER                      (0x00000000 + 0x1D8000)
#define FLASH_SIZE_TIMER                      1026
#define FLASH_ADDR_TOTAL_VOLTAGE              (0x00000000 + 0x1D9000)
#define FLASH_SIZE_TOTAL_VOLTAGE              1986
#define FLASH_ADDR_VOLTAGE_ABNORMAL           (0x00000000 + 0x1DA000)
#define FLASH_SIZE_VOLTAGE_ABNORMAL           15426

#endif /* __FLASH_IMAGE_ADDR_H__ */
