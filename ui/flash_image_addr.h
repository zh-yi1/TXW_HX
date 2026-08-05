/*
 * flash_image_addr.h — Auto-generated, do not edit.
 *
 * P25Q64SH Flash Image Address Map (64 Mb = 8 MB)
 * Sector size: 4096 bytes (4 KB)
 *
 * Images:       283
 * Categories:   186
 * Flash used:   1862722 bytes (1819.1 KB)
 * Sectors used: 455 / 2048
 * Capacity:     8192 KB (8 MB)
 *
 * Category layout:
 *   A_CELL_VOLTAGE                       base=0x000000  stride=15426  count=1     sectors=[0 – 3]
 *   ABNORMAL_TIME                        base=0x004000  stride=1474   count=1     sectors=[4]
 *   ABNORMAL                             base=0x005000  stride=1474   count=1     sectors=[5]
 *   BAT_0_BLUE                           base=0x006000  stride=5250   count=1     sectors=[6 – 7]
 *   BAT_0_ORANGE                         base=0x008000  stride=5250   count=1     sectors=[8 – 9]
 *   BAT_1_BLUE                           base=0x00A000  stride=5250   count=1     sectors=[10 – 11]
 *   BAT_1_ORANGE                         base=0x00C000  stride=5250   count=1     sectors=[12 – 13]
 *   BAT_2_BLUE                           base=0x00E000  stride=5250   count=1     sectors=[14 – 15]
 *   BAT_2_ORANGE                         base=0x010000  stride=5250   count=1     sectors=[16 – 17]
 *   BAT_3_BLUE                           base=0x012000  stride=5250   count=1     sectors=[18 – 19]
 *   BAT_3_ORANGE                         base=0x014000  stride=5250   count=1     sectors=[20 – 21]
 *   BAT_4_BLUE                           base=0x016000  stride=5250   count=1     sectors=[22 – 23]
 *   BAT_4_ORANGE                         base=0x018000  stride=5250   count=1     sectors=[24 – 25]
 *   BAT_5_BLUE                           base=0x01A000  stride=5250   count=1     sectors=[26 – 27]
 *   BAT_5_ORANGE                         base=0x01C000  stride=5250   count=1     sectors=[28 – 29]
 *   BAT_6_BLUE                           base=0x01E000  stride=5250   count=1     sectors=[30 – 31]
 *   BAT_6_ORANGE                         base=0x020000  stride=5250   count=1     sectors=[32 – 33]
 *   BAT_7_BLUE                           base=0x022000  stride=5250   count=1     sectors=[34 – 35]
 *   BAT_7_ORANGE                         base=0x024000  stride=5250   count=1     sectors=[36 – 37]
 *   BAT_8_BLUE                           base=0x026000  stride=5250   count=1     sectors=[38 – 39]
 *   BAT_8_ORANGE                         base=0x028000  stride=5250   count=1     sectors=[40 – 41]
 *   BAT_9_BLUE                           base=0x02A000  stride=5250   count=1     sectors=[42 – 43]
 *   BAT_9_ORANGE                         base=0x02C000  stride=5250   count=1     sectors=[44 – 45]
 *   BAT_NUM                              base=0x02E000  stride=2562   count=1     sectors=[46]
 *   BAT_PER_BLUE                         base=0x02F000  stride=6402   count=1     sectors=[47 – 48]
 *   BAT_PER_ORANGE                       base=0x031000  stride=6402   count=1     sectors=[49 – 50]
 *   BAT_TMP                              base=0x033000  stride=15426  count=1     sectors=[51 – 54]
 *   BLUE_CHARGING_001                    base=0x037000  stride=8490   count=1     sectors=[55 – 57]
 *   BLUE_CHARGING_002                    base=0x03A000  stride=8490   count=1     sectors=[58 – 60]
 *   BLUE_CHARGING_003                    base=0x03D000  stride=8490   count=1     sectors=[61 – 63]
 *   BLUE_CHARGING_004                    base=0x040000  stride=8490   count=1     sectors=[64 – 66]
 *   BLUE_CHARGING_005                    base=0x043000  stride=8490   count=1     sectors=[67 – 69]
 *   BLUE_CHARGING_006                    base=0x046000  stride=8490   count=1     sectors=[70 – 72]
 *   BLUE_CHARGING_007                    base=0x049000  stride=8490   count=1     sectors=[73 – 75]
 *   BLUE_CHARGING_008                    base=0x04C000  stride=8490   count=1     sectors=[76 – 78]
 *   BLUE_CHARGING_009                    base=0x04F000  stride=8490   count=1     sectors=[79 – 81]
 *   BLUE_CHARGING_010                    base=0x052000  stride=8490   count=1     sectors=[82 – 84]
 *   BLUE_CHARGING_011                    base=0x055000  stride=8490   count=1     sectors=[85 – 87]
 *   BLUE_CHARGING_012                    base=0x058000  stride=8490   count=1     sectors=[88 – 90]
 *   BLUE_CHARGING_013                    base=0x05B000  stride=8490   count=1     sectors=[91 – 93]
 *   BLUE_CHARGING_014                    base=0x05E000  stride=8490   count=1     sectors=[94 – 96]
 *   BLUE_CHARGING_015                    base=0x061000  stride=8490   count=1     sectors=[97 – 99]
 *   BLUE_CHARGING_016                    base=0x064000  stride=8490   count=1     sectors=[100 – 102]
 *   BLUE_CHARGING_017                    base=0x067000  stride=8490   count=1     sectors=[103 – 105]
 *   BLUE_CHARGING_018                    base=0x06A000  stride=8490   count=1     sectors=[106 – 108]
 *   BLUE_CHARGING_019                    base=0x06D000  stride=8490   count=1     sectors=[109 – 111]
 *   BLUE_CHARGING_020                    base=0x070000  stride=8490   count=1     sectors=[112 – 114]
 *   BLUE_CHARGING_021                    base=0x073000  stride=8490   count=1     sectors=[115 – 117]
 *   BLUE_CHARGING_022                    base=0x076000  stride=8490   count=1     sectors=[118 – 120]
 *   BLUE_CHARGING_023                    base=0x079000  stride=8490   count=1     sectors=[121 – 123]
 *   BLUE_CHARGING_024                    base=0x07C000  stride=8490   count=1     sectors=[124 – 126]
 *   BLUE_CHARGING_025                    base=0x07F000  stride=8490   count=1     sectors=[127 – 129]
 *   BLUE_CHARGING_026                    base=0x082000  stride=8490   count=1     sectors=[130 – 132]
 *   BLUE_CHARGING_027                    base=0x085000  stride=8490   count=1     sectors=[133 – 135]
 *   BLUE_CHARGING_028                    base=0x088000  stride=8490   count=1     sectors=[136 – 138]
 *   BLUE_CHARGING_029                    base=0x08B000  stride=8490   count=1     sectors=[139 – 141]
 *   BLUE_CHARGING_030                    base=0x08E000  stride=8490   count=1     sectors=[142 – 144]
 *   BLUE_CHARGING_031                    base=0x091000  stride=8490   count=1     sectors=[145 – 147]
 *   BLUE_CHARGING_032                    base=0x094000  stride=8490   count=1     sectors=[148 – 150]
 *   BLUE_CHARGING_033                    base=0x097000  stride=8490   count=1     sectors=[151 – 153]
 *   BLUE_CHARGING_034                    base=0x09A000  stride=8490   count=1     sectors=[154 – 156]
 *   BLUE_CHARGING_035                    base=0x09D000  stride=8490   count=1     sectors=[157 – 159]
 *   BLUE_CHARGING_036                    base=0x0A0000  stride=8490   count=1     sectors=[160 – 162]
 *   BLUE_CHARGING_037                    base=0x0A3000  stride=8490   count=1     sectors=[163 – 165]
 *   BLUE_CHARGING_038                    base=0x0A6000  stride=8490   count=1     sectors=[166 – 168]
 *   BLUE_CHARGING_039                    base=0x0A9000  stride=8490   count=1     sectors=[169 – 171]
 *   BLUE_CHARGING_040                    base=0x0AC000  stride=8490   count=1     sectors=[172 – 174]
 *   CHARGE_HIGH_TEMP_PRO                 base=0x0AF000  stride=17346  count=1     sectors=[175 – 179]
 *   CHARGE_TEMP                          base=0x0B4000  stride=2718   count=1     sectors=[180]
 *   CI                                   base=0x0B5000  stride=1346   count=1     sectors=[181]
 *   CIRCUIT_PROTECTION                   base=0x0B6000  stride=12866  count=1     sectors=[182 – 185]
 *   CIRCUIT_PROTECTION_TEXT              base=0x0BA000  stride=17346  count=1     sectors=[186 – 190]
 *   CIRCUIT_RECOVERY                     base=0x0BF000  stride=9186   count=1     sectors=[191 – 193]
 *   CYCLE_INDEX                          base=0x0C2000  stride=7746   count=1     sectors=[194 – 195]
 *   DI                                   base=0x0C4000  stride=678    count=1     sectors=[196]
 *   DISCHARGE_HIGH_TEMP_PRO              base=0x0C5000  stride=17346  count=1     sectors=[197 – 201]
 *   DISCHARGE_TEMP                       base=0x0CA000  stride=2718   count=1     sectors=[202]
 *   DOUHAO                               base=0x0CB000  stride=450    count=1     sectors=[203]
 *   GONG                                 base=0x0CC000  stride=678    count=1     sectors=[204]
 *   HEALTH                               base=0x0CD000  stride=7746   count=1     sectors=[205 – 206]
 *   LEFT_1_ORANGE                        base=0x0CF000  stride=11586  count=1     sectors=[207 – 209]
 *   LEFT_2_BLUE                          base=0x0D2000  stride=8994   count=1     sectors=[210 – 212]
 *   LEFT_2_ORANGE                        base=0x0D5000  stride=8994   count=1     sectors=[213 – 215]
 *   LEFT_3_BLUE                          base=0x0D8000  stride=6402   count=1     sectors=[216 – 217]
 *   MINI                                 base=0x0DA000  stride=2946   count=1     sectors=[218]
 *   NO_ABNORMAL                          base=0x0DB000  stride=5026   count=1     sectors=[219 – 220]
 *   NOAMAL_HIGH_TEMP_PRO                 base=0x0DD000  stride=17346  count=1     sectors=[221 – 225]
 *   NOAMAL_TEMP                          base=0x0E2000  stride=2718   count=1     sectors=[226]
 *   NUM_12                               base=0x0E3000  stride=346    count=40    sectors=[227 – 230]
 *   NUM_16                               base=0x0E7000  stride=770    count=40    sectors=[231 – 238]
 *   NUM_20                               base=0x0EF000  stride=738    count=10    sectors=[239 – 240]
 *   NUM_20_COLON                         base=0x0F1000  stride=450    count=1     sectors=[241]
 *   NUM_40                               base=0x0F2000  stride=1986   count=11    sectors=[242 – 247]
 *   NUM_40_DEGREE                        base=0x0F8000  stride=1346   count=1     sectors=[248]
 *   NUM_40_PERCENT                       base=0x0F9000  stride=1346   count=1     sectors=[249]
 *   ORANGE_CHARGING_001                  base=0x0FA000  stride=8490   count=1     sectors=[250 – 252]
 *   ORANGE_CHARGING_002                  base=0x0FD000  stride=8490   count=1     sectors=[253 – 255]
 *   ORANGE_CHARGING_003                  base=0x100000  stride=8490   count=1     sectors=[256 – 258]
 *   ORANGE_CHARGING_004                  base=0x103000  stride=8490   count=1     sectors=[259 – 261]
 *   ORANGE_CHARGING_005                  base=0x106000  stride=8490   count=1     sectors=[262 – 264]
 *   ORANGE_CHARGING_006                  base=0x109000  stride=8490   count=1     sectors=[265 – 267]
 *   ORANGE_CHARGING_007                  base=0x10C000  stride=8490   count=1     sectors=[268 – 270]
 *   ORANGE_CHARGING_008                  base=0x10F000  stride=8490   count=1     sectors=[271 – 273]
 *   ORANGE_CHARGING_009                  base=0x112000  stride=8490   count=1     sectors=[274 – 276]
 *   ORANGE_CHARGING_010                  base=0x115000  stride=8490   count=1     sectors=[277 – 279]
 *   ORANGE_CHARGING_011                  base=0x118000  stride=8490   count=1     sectors=[280 – 282]
 *   ORANGE_CHARGING_012                  base=0x11B000  stride=8490   count=1     sectors=[283 – 285]
 *   ORANGE_CHARGING_013                  base=0x11E000  stride=8490   count=1     sectors=[286 – 288]
 *   ORANGE_CHARGING_014                  base=0x121000  stride=8490   count=1     sectors=[289 – 291]
 *   ORANGE_CHARGING_015                  base=0x124000  stride=8490   count=1     sectors=[292 – 294]
 *   ORANGE_CHARGING_016                  base=0x127000  stride=8490   count=1     sectors=[295 – 297]
 *   ORANGE_CHARGING_017                  base=0x12A000  stride=8490   count=1     sectors=[298 – 300]
 *   ORANGE_CHARGING_018                  base=0x12D000  stride=8490   count=1     sectors=[301 – 303]
 *   ORANGE_CHARGING_019                  base=0x130000  stride=8490   count=1     sectors=[304 – 306]
 *   ORANGE_CHARGING_020                  base=0x133000  stride=8490   count=1     sectors=[307 – 309]
 *   ORANGE_CHARGING_021                  base=0x136000  stride=8490   count=1     sectors=[310 – 312]
 *   ORANGE_CHARGING_022                  base=0x139000  stride=8490   count=1     sectors=[313 – 315]
 *   ORANGE_CHARGING_023                  base=0x13C000  stride=8490   count=1     sectors=[316 – 318]
 *   ORANGE_CHARGING_024                  base=0x13F000  stride=8490   count=1     sectors=[319 – 321]
 *   ORANGE_CHARGING_025                  base=0x142000  stride=8490   count=1     sectors=[322 – 324]
 *   ORANGE_CHARGING_026                  base=0x145000  stride=8490   count=1     sectors=[325 – 327]
 *   ORANGE_CHARGING_027                  base=0x148000  stride=8490   count=1     sectors=[328 – 330]
 *   ORANGE_CHARGING_028                  base=0x14B000  stride=8490   count=1     sectors=[331 – 333]
 *   ORANGE_CHARGING_029                  base=0x14E000  stride=8490   count=1     sectors=[334 – 336]
 *   ORANGE_CHARGING_030                  base=0x151000  stride=8490   count=1     sectors=[337 – 339]
 *   ORANGE_CHARGING_031                  base=0x154000  stride=8490   count=1     sectors=[340 – 342]
 *   ORANGE_CHARGING_032                  base=0x157000  stride=8490   count=1     sectors=[343 – 345]
 *   ORANGE_CHARGING_033                  base=0x15A000  stride=8490   count=1     sectors=[346 – 348]
 *   ORANGE_CHARGING_034                  base=0x15D000  stride=8490   count=1     sectors=[349 – 351]
 *   ORANGE_CHARGING_035                  base=0x160000  stride=8490   count=1     sectors=[352 – 354]
 *   ORANGE_CHARGING_036                  base=0x163000  stride=8490   count=1     sectors=[355 – 357]
 *   ORANGE_CHARGING_037                  base=0x166000  stride=8490   count=1     sectors=[358 – 360]
 *   ORANGE_CHARGING_038                  base=0x169000  stride=8490   count=1     sectors=[361 – 363]
 *   ORANGE_CHARGING_039                  base=0x16C000  stride=8490   count=1     sectors=[364 – 366]
 *   ORANGE_CHARGING_040                  base=0x16F000  stride=8490   count=1     sectors=[367 – 369]
 *   OUT                                  base=0x172000  stride=2178   count=1     sectors=[370]
 *   POWER_PART_1_USB_A_BLUE              base=0x173000  stride=5286   count=1     sectors=[371 – 372]
 *   POWER_PART_1_USB_A_WHITE             base=0x175000  stride=5286   count=1     sectors=[373 – 374]
 *   POWER_PART_1_USB_C_BLUE              base=0x177000  stride=5286   count=1     sectors=[375 – 376]
 *   POWER_PART_1_USB_C_WHITE             base=0x179000  stride=5286   count=1     sectors=[377 – 378]
 *   POWER_PART_2_PORT_1_BLUE             base=0x17B000  stride=1506   count=1     sectors=[379]
 *   POWER_PART_2_PORT_1_WHITE            base=0x17C000  stride=1506   count=1     sectors=[380]
 *   POWER_PART_2_PORT_2_BLUE             base=0x17D000  stride=1506   count=1     sectors=[381]
 *   POWER_PART_2_PORT_2_WHITE            base=0x17E000  stride=1506   count=1     sectors=[382]
 *   POWER_PART_2_PORT_3_BLUE             base=0x17F000  stride=1506   count=1     sectors=[383]
 *   POWER_PART_2_PORT_3_WHITE            base=0x180000  stride=1506   count=1     sectors=[384]
 *   POWER_PART_3_IN_BLUE                 base=0x181000  stride=6366   count=1     sectors=[385 – 386]
 *   POWER_PART_3_OUT_BLUE                base=0x183000  stride=6366   count=1     sectors=[387 – 388]
 *   POWER_PART_3_WHITE                   base=0x185000  stride=6366   count=1     sectors=[389 – 390]
 *   POWER_PART_4_0_BLUE                  base=0x187000  stride=1866   count=1     sectors=[391]
 *   POWER_PART_4_0_WHITE                 base=0x188000  stride=1866   count=1     sectors=[392]
 *   POWER_PART_4_1_BLUE                  base=0x189000  stride=1866   count=1     sectors=[393]
 *   POWER_PART_4_1_WHITE                 base=0x18A000  stride=1866   count=1     sectors=[394]
 *   POWER_PART_4_2_BLUE                  base=0x18B000  stride=1866   count=1     sectors=[395]
 *   POWER_PART_4_2_WHITE                 base=0x18C000  stride=1866   count=1     sectors=[396]
 *   POWER_PART_4_3_BLUE                  base=0x18D000  stride=1866   count=1     sectors=[397]
 *   POWER_PART_4_3_WHITE                 base=0x18E000  stride=1866   count=1     sectors=[398]
 *   POWER_PART_4_4_BLUE                  base=0x18F000  stride=1866   count=1     sectors=[399]
 *   POWER_PART_4_4_WHITE                 base=0x190000  stride=1866   count=1     sectors=[400]
 *   POWER_PART_4_5_BLUE                  base=0x191000  stride=1866   count=1     sectors=[401]
 *   POWER_PART_4_5_WHITE                 base=0x192000  stride=1866   count=1     sectors=[402]
 *   POWER_PART_4_6_BLUE                  base=0x193000  stride=1866   count=1     sectors=[403]
 *   POWER_PART_4_6_WHITE                 base=0x194000  stride=1866   count=1     sectors=[404]
 *   POWER_PART_4_7_BLUE                  base=0x195000  stride=1866   count=1     sectors=[405]
 *   POWER_PART_4_7_WHITE                 base=0x196000  stride=1866   count=1     sectors=[406]
 *   POWER_PART_4_8_BLUE                  base=0x197000  stride=1866   count=1     sectors=[407]
 *   POWER_PART_4_8_WHITE                 base=0x198000  stride=1866   count=1     sectors=[408]
 *   POWER_PART_4_9_BLUE                  base=0x199000  stride=1866   count=1     sectors=[409]
 *   POWER_PART_4_9_WHITE                 base=0x19A000  stride=1866   count=1     sectors=[410]
 *   POWER_PART_4_BLUE                    base=0x19B000  stride=1866   count=1     sectors=[411]
 *   POWER_PART_4_WHITE                   base=0x19C000  stride=1866   count=1     sectors=[412]
 *   POWER_PART_5_BLUE                    base=0x19D000  stride=3486   count=1     sectors=[413]
 *   POWER_PART_5_WHITE                   base=0x19E000  stride=3486   count=1     sectors=[414]
 *   RIGHT_1_ORANGE                       base=0x19F000  stride=11586  count=1     sectors=[415 – 417]
 *   RIGHT_2_BLUE                         base=0x1A2000  stride=8994   count=1     sectors=[418 – 420]
 *   RIGHT_2_ORANGE                       base=0x1A5000  stride=8994   count=1     sectors=[421 – 423]
 *   RIGHT_3_BLUE                         base=0x1A8000  stride=6402   count=1     sectors=[424 – 425]
 *   SAFE                                 base=0x1AA000  stride=12866  count=1     sectors=[426 – 429]
 *   SAFEGUARD                            base=0x1AE000  stride=26466  count=1     sectors=[430 – 436]
 *   TEMP_ABNORMAL                        base=0x1B5000  stride=15426  count=1     sectors=[437 – 440]
 *   TEMP_ORANGE                          base=0x1B9000  stride=12866  count=1     sectors=[441 – 444]
 *   TEMPERATURE_RECOVERY                 base=0x1BD000  stride=9186   count=1     sectors=[445 – 447]
 *   TIAO                                 base=0x1C0000  stride=678    count=1     sectors=[448]
 *   TIMER                                base=0x1C1000  stride=1026   count=1     sectors=[449]
 *   TOTAL_VOLTAGE                        base=0x1C2000  stride=1986   count=1     sectors=[450]
 *   VOLTAGE_ABNORMAL                     base=0x1C3000  stride=15426  count=1     sectors=[451 – 454]
 */

#ifndef __FLASH_IMAGE_ADDR_H__
#define __FLASH_IMAGE_ADDR_H__

/*
 * Category base addresses — access images via:
 *   addr = FLASH_ADDR_<CAT>_BASE + index * FLASH_STRIDE_<CAT>
 */
#define FLASH_ADDR_A_CELL_VOLTAGE_BASE    (0x00000000 + 0x0000)
#define FLASH_STRIDE_A_CELL_VOLTAGE       15426
#define FLASH_COUNT_A_CELL_VOLTAGE        1

#define FLASH_ADDR_ABNORMAL_TIME_BASE    (0x00000000 + 0x4000)
#define FLASH_STRIDE_ABNORMAL_TIME       1474
#define FLASH_COUNT_ABNORMAL_TIME        1

#define FLASH_ADDR_ABNORMAL_BASE    (0x00000000 + 0x5000)
#define FLASH_STRIDE_ABNORMAL       1474
#define FLASH_COUNT_ABNORMAL        1

#define FLASH_ADDR_BAT_0_BLUE_BASE    (0x00000000 + 0x6000)
#define FLASH_STRIDE_BAT_0_BLUE       5250
#define FLASH_COUNT_BAT_0_BLUE        1

#define FLASH_ADDR_BAT_0_ORANGE_BASE    (0x00000000 + 0x8000)
#define FLASH_STRIDE_BAT_0_ORANGE       5250
#define FLASH_COUNT_BAT_0_ORANGE        1

#define FLASH_ADDR_BAT_1_BLUE_BASE    (0x00000000 + 0xA000)
#define FLASH_STRIDE_BAT_1_BLUE       5250
#define FLASH_COUNT_BAT_1_BLUE        1

#define FLASH_ADDR_BAT_1_ORANGE_BASE    (0x00000000 + 0xC000)
#define FLASH_STRIDE_BAT_1_ORANGE       5250
#define FLASH_COUNT_BAT_1_ORANGE        1

#define FLASH_ADDR_BAT_2_BLUE_BASE    (0x00000000 + 0xE000)
#define FLASH_STRIDE_BAT_2_BLUE       5250
#define FLASH_COUNT_BAT_2_BLUE        1

#define FLASH_ADDR_BAT_2_ORANGE_BASE    (0x00000000 + 0x10000)
#define FLASH_STRIDE_BAT_2_ORANGE       5250
#define FLASH_COUNT_BAT_2_ORANGE        1

#define FLASH_ADDR_BAT_3_BLUE_BASE    (0x00000000 + 0x12000)
#define FLASH_STRIDE_BAT_3_BLUE       5250
#define FLASH_COUNT_BAT_3_BLUE        1

#define FLASH_ADDR_BAT_3_ORANGE_BASE    (0x00000000 + 0x14000)
#define FLASH_STRIDE_BAT_3_ORANGE       5250
#define FLASH_COUNT_BAT_3_ORANGE        1

#define FLASH_ADDR_BAT_4_BLUE_BASE    (0x00000000 + 0x16000)
#define FLASH_STRIDE_BAT_4_BLUE       5250
#define FLASH_COUNT_BAT_4_BLUE        1

#define FLASH_ADDR_BAT_4_ORANGE_BASE    (0x00000000 + 0x18000)
#define FLASH_STRIDE_BAT_4_ORANGE       5250
#define FLASH_COUNT_BAT_4_ORANGE        1

#define FLASH_ADDR_BAT_5_BLUE_BASE    (0x00000000 + 0x1A000)
#define FLASH_STRIDE_BAT_5_BLUE       5250
#define FLASH_COUNT_BAT_5_BLUE        1

#define FLASH_ADDR_BAT_5_ORANGE_BASE    (0x00000000 + 0x1C000)
#define FLASH_STRIDE_BAT_5_ORANGE       5250
#define FLASH_COUNT_BAT_5_ORANGE        1

#define FLASH_ADDR_BAT_6_BLUE_BASE    (0x00000000 + 0x1E000)
#define FLASH_STRIDE_BAT_6_BLUE       5250
#define FLASH_COUNT_BAT_6_BLUE        1

#define FLASH_ADDR_BAT_6_ORANGE_BASE    (0x00000000 + 0x20000)
#define FLASH_STRIDE_BAT_6_ORANGE       5250
#define FLASH_COUNT_BAT_6_ORANGE        1

#define FLASH_ADDR_BAT_7_BLUE_BASE    (0x00000000 + 0x22000)
#define FLASH_STRIDE_BAT_7_BLUE       5250
#define FLASH_COUNT_BAT_7_BLUE        1

#define FLASH_ADDR_BAT_7_ORANGE_BASE    (0x00000000 + 0x24000)
#define FLASH_STRIDE_BAT_7_ORANGE       5250
#define FLASH_COUNT_BAT_7_ORANGE        1

#define FLASH_ADDR_BAT_8_BLUE_BASE    (0x00000000 + 0x26000)
#define FLASH_STRIDE_BAT_8_BLUE       5250
#define FLASH_COUNT_BAT_8_BLUE        1

#define FLASH_ADDR_BAT_8_ORANGE_BASE    (0x00000000 + 0x28000)
#define FLASH_STRIDE_BAT_8_ORANGE       5250
#define FLASH_COUNT_BAT_8_ORANGE        1

#define FLASH_ADDR_BAT_9_BLUE_BASE    (0x00000000 + 0x2A000)
#define FLASH_STRIDE_BAT_9_BLUE       5250
#define FLASH_COUNT_BAT_9_BLUE        1

#define FLASH_ADDR_BAT_9_ORANGE_BASE    (0x00000000 + 0x2C000)
#define FLASH_STRIDE_BAT_9_ORANGE       5250
#define FLASH_COUNT_BAT_9_ORANGE        1

#define FLASH_ADDR_BAT_NUM_BASE    (0x00000000 + 0x2E000)
#define FLASH_STRIDE_BAT_NUM       2562
#define FLASH_COUNT_BAT_NUM        1

#define FLASH_ADDR_BAT_PER_BLUE_BASE    (0x00000000 + 0x2F000)
#define FLASH_STRIDE_BAT_PER_BLUE       6402
#define FLASH_COUNT_BAT_PER_BLUE        1

#define FLASH_ADDR_BAT_PER_ORANGE_BASE    (0x00000000 + 0x31000)
#define FLASH_STRIDE_BAT_PER_ORANGE       6402
#define FLASH_COUNT_BAT_PER_ORANGE        1

#define FLASH_ADDR_BAT_TMP_BASE    (0x00000000 + 0x33000)
#define FLASH_STRIDE_BAT_TMP       15426
#define FLASH_COUNT_BAT_TMP        1

#define FLASH_ADDR_BLUE_CHARGING_001_BASE    (0x00000000 + 0x37000)
#define FLASH_STRIDE_BLUE_CHARGING_001       8490
#define FLASH_COUNT_BLUE_CHARGING_001        1

#define FLASH_ADDR_BLUE_CHARGING_002_BASE    (0x00000000 + 0x3A000)
#define FLASH_STRIDE_BLUE_CHARGING_002       8490
#define FLASH_COUNT_BLUE_CHARGING_002        1

#define FLASH_ADDR_BLUE_CHARGING_003_BASE    (0x00000000 + 0x3D000)
#define FLASH_STRIDE_BLUE_CHARGING_003       8490
#define FLASH_COUNT_BLUE_CHARGING_003        1

#define FLASH_ADDR_BLUE_CHARGING_004_BASE    (0x00000000 + 0x40000)
#define FLASH_STRIDE_BLUE_CHARGING_004       8490
#define FLASH_COUNT_BLUE_CHARGING_004        1

#define FLASH_ADDR_BLUE_CHARGING_005_BASE    (0x00000000 + 0x43000)
#define FLASH_STRIDE_BLUE_CHARGING_005       8490
#define FLASH_COUNT_BLUE_CHARGING_005        1

#define FLASH_ADDR_BLUE_CHARGING_006_BASE    (0x00000000 + 0x46000)
#define FLASH_STRIDE_BLUE_CHARGING_006       8490
#define FLASH_COUNT_BLUE_CHARGING_006        1

#define FLASH_ADDR_BLUE_CHARGING_007_BASE    (0x00000000 + 0x49000)
#define FLASH_STRIDE_BLUE_CHARGING_007       8490
#define FLASH_COUNT_BLUE_CHARGING_007        1

#define FLASH_ADDR_BLUE_CHARGING_008_BASE    (0x00000000 + 0x4C000)
#define FLASH_STRIDE_BLUE_CHARGING_008       8490
#define FLASH_COUNT_BLUE_CHARGING_008        1

#define FLASH_ADDR_BLUE_CHARGING_009_BASE    (0x00000000 + 0x4F000)
#define FLASH_STRIDE_BLUE_CHARGING_009       8490
#define FLASH_COUNT_BLUE_CHARGING_009        1

#define FLASH_ADDR_BLUE_CHARGING_010_BASE    (0x00000000 + 0x52000)
#define FLASH_STRIDE_BLUE_CHARGING_010       8490
#define FLASH_COUNT_BLUE_CHARGING_010        1

#define FLASH_ADDR_BLUE_CHARGING_011_BASE    (0x00000000 + 0x55000)
#define FLASH_STRIDE_BLUE_CHARGING_011       8490
#define FLASH_COUNT_BLUE_CHARGING_011        1

#define FLASH_ADDR_BLUE_CHARGING_012_BASE    (0x00000000 + 0x58000)
#define FLASH_STRIDE_BLUE_CHARGING_012       8490
#define FLASH_COUNT_BLUE_CHARGING_012        1

#define FLASH_ADDR_BLUE_CHARGING_013_BASE    (0x00000000 + 0x5B000)
#define FLASH_STRIDE_BLUE_CHARGING_013       8490
#define FLASH_COUNT_BLUE_CHARGING_013        1

#define FLASH_ADDR_BLUE_CHARGING_014_BASE    (0x00000000 + 0x5E000)
#define FLASH_STRIDE_BLUE_CHARGING_014       8490
#define FLASH_COUNT_BLUE_CHARGING_014        1

#define FLASH_ADDR_BLUE_CHARGING_015_BASE    (0x00000000 + 0x61000)
#define FLASH_STRIDE_BLUE_CHARGING_015       8490
#define FLASH_COUNT_BLUE_CHARGING_015        1

#define FLASH_ADDR_BLUE_CHARGING_016_BASE    (0x00000000 + 0x64000)
#define FLASH_STRIDE_BLUE_CHARGING_016       8490
#define FLASH_COUNT_BLUE_CHARGING_016        1

#define FLASH_ADDR_BLUE_CHARGING_017_BASE    (0x00000000 + 0x67000)
#define FLASH_STRIDE_BLUE_CHARGING_017       8490
#define FLASH_COUNT_BLUE_CHARGING_017        1

#define FLASH_ADDR_BLUE_CHARGING_018_BASE    (0x00000000 + 0x6A000)
#define FLASH_STRIDE_BLUE_CHARGING_018       8490
#define FLASH_COUNT_BLUE_CHARGING_018        1

#define FLASH_ADDR_BLUE_CHARGING_019_BASE    (0x00000000 + 0x6D000)
#define FLASH_STRIDE_BLUE_CHARGING_019       8490
#define FLASH_COUNT_BLUE_CHARGING_019        1

#define FLASH_ADDR_BLUE_CHARGING_020_BASE    (0x00000000 + 0x70000)
#define FLASH_STRIDE_BLUE_CHARGING_020       8490
#define FLASH_COUNT_BLUE_CHARGING_020        1

#define FLASH_ADDR_BLUE_CHARGING_021_BASE    (0x00000000 + 0x73000)
#define FLASH_STRIDE_BLUE_CHARGING_021       8490
#define FLASH_COUNT_BLUE_CHARGING_021        1

#define FLASH_ADDR_BLUE_CHARGING_022_BASE    (0x00000000 + 0x76000)
#define FLASH_STRIDE_BLUE_CHARGING_022       8490
#define FLASH_COUNT_BLUE_CHARGING_022        1

#define FLASH_ADDR_BLUE_CHARGING_023_BASE    (0x00000000 + 0x79000)
#define FLASH_STRIDE_BLUE_CHARGING_023       8490
#define FLASH_COUNT_BLUE_CHARGING_023        1

#define FLASH_ADDR_BLUE_CHARGING_024_BASE    (0x00000000 + 0x7C000)
#define FLASH_STRIDE_BLUE_CHARGING_024       8490
#define FLASH_COUNT_BLUE_CHARGING_024        1

#define FLASH_ADDR_BLUE_CHARGING_025_BASE    (0x00000000 + 0x7F000)
#define FLASH_STRIDE_BLUE_CHARGING_025       8490
#define FLASH_COUNT_BLUE_CHARGING_025        1

#define FLASH_ADDR_BLUE_CHARGING_026_BASE    (0x00000000 + 0x82000)
#define FLASH_STRIDE_BLUE_CHARGING_026       8490
#define FLASH_COUNT_BLUE_CHARGING_026        1

#define FLASH_ADDR_BLUE_CHARGING_027_BASE    (0x00000000 + 0x85000)
#define FLASH_STRIDE_BLUE_CHARGING_027       8490
#define FLASH_COUNT_BLUE_CHARGING_027        1

#define FLASH_ADDR_BLUE_CHARGING_028_BASE    (0x00000000 + 0x88000)
#define FLASH_STRIDE_BLUE_CHARGING_028       8490
#define FLASH_COUNT_BLUE_CHARGING_028        1

#define FLASH_ADDR_BLUE_CHARGING_029_BASE    (0x00000000 + 0x8B000)
#define FLASH_STRIDE_BLUE_CHARGING_029       8490
#define FLASH_COUNT_BLUE_CHARGING_029        1

#define FLASH_ADDR_BLUE_CHARGING_030_BASE    (0x00000000 + 0x8E000)
#define FLASH_STRIDE_BLUE_CHARGING_030       8490
#define FLASH_COUNT_BLUE_CHARGING_030        1

#define FLASH_ADDR_BLUE_CHARGING_031_BASE    (0x00000000 + 0x91000)
#define FLASH_STRIDE_BLUE_CHARGING_031       8490
#define FLASH_COUNT_BLUE_CHARGING_031        1

#define FLASH_ADDR_BLUE_CHARGING_032_BASE    (0x00000000 + 0x94000)
#define FLASH_STRIDE_BLUE_CHARGING_032       8490
#define FLASH_COUNT_BLUE_CHARGING_032        1

#define FLASH_ADDR_BLUE_CHARGING_033_BASE    (0x00000000 + 0x97000)
#define FLASH_STRIDE_BLUE_CHARGING_033       8490
#define FLASH_COUNT_BLUE_CHARGING_033        1

#define FLASH_ADDR_BLUE_CHARGING_034_BASE    (0x00000000 + 0x9A000)
#define FLASH_STRIDE_BLUE_CHARGING_034       8490
#define FLASH_COUNT_BLUE_CHARGING_034        1

#define FLASH_ADDR_BLUE_CHARGING_035_BASE    (0x00000000 + 0x9D000)
#define FLASH_STRIDE_BLUE_CHARGING_035       8490
#define FLASH_COUNT_BLUE_CHARGING_035        1

#define FLASH_ADDR_BLUE_CHARGING_036_BASE    (0x00000000 + 0xA0000)
#define FLASH_STRIDE_BLUE_CHARGING_036       8490
#define FLASH_COUNT_BLUE_CHARGING_036        1

#define FLASH_ADDR_BLUE_CHARGING_037_BASE    (0x00000000 + 0xA3000)
#define FLASH_STRIDE_BLUE_CHARGING_037       8490
#define FLASH_COUNT_BLUE_CHARGING_037        1

#define FLASH_ADDR_BLUE_CHARGING_038_BASE    (0x00000000 + 0xA6000)
#define FLASH_STRIDE_BLUE_CHARGING_038       8490
#define FLASH_COUNT_BLUE_CHARGING_038        1

#define FLASH_ADDR_BLUE_CHARGING_039_BASE    (0x00000000 + 0xA9000)
#define FLASH_STRIDE_BLUE_CHARGING_039       8490
#define FLASH_COUNT_BLUE_CHARGING_039        1

#define FLASH_ADDR_BLUE_CHARGING_040_BASE    (0x00000000 + 0xAC000)
#define FLASH_STRIDE_BLUE_CHARGING_040       8490
#define FLASH_COUNT_BLUE_CHARGING_040        1

#define FLASH_ADDR_CHARGE_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xAF000)
#define FLASH_STRIDE_CHARGE_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_CHARGE_HIGH_TEMP_PRO        1

#define FLASH_ADDR_CHARGE_TEMP_BASE    (0x00000000 + 0xB4000)
#define FLASH_STRIDE_CHARGE_TEMP       2718
#define FLASH_COUNT_CHARGE_TEMP        1

#define FLASH_ADDR_CI_BASE    (0x00000000 + 0xB5000)
#define FLASH_STRIDE_CI       1346
#define FLASH_COUNT_CI        1

#define FLASH_ADDR_CIRCUIT_PROTECTION_BASE    (0x00000000 + 0xB6000)
#define FLASH_STRIDE_CIRCUIT_PROTECTION       12866
#define FLASH_COUNT_CIRCUIT_PROTECTION        1

#define FLASH_ADDR_CIRCUIT_PROTECTION_TEXT_BASE    (0x00000000 + 0xBA000)
#define FLASH_STRIDE_CIRCUIT_PROTECTION_TEXT       17346
#define FLASH_COUNT_CIRCUIT_PROTECTION_TEXT        1

#define FLASH_ADDR_CIRCUIT_RECOVERY_BASE    (0x00000000 + 0xBF000)
#define FLASH_STRIDE_CIRCUIT_RECOVERY       9186
#define FLASH_COUNT_CIRCUIT_RECOVERY        1

#define FLASH_ADDR_CYCLE_INDEX_BASE    (0x00000000 + 0xC2000)
#define FLASH_STRIDE_CYCLE_INDEX       7746
#define FLASH_COUNT_CYCLE_INDEX        1

#define FLASH_ADDR_DI_BASE    (0x00000000 + 0xC4000)
#define FLASH_STRIDE_DI       678
#define FLASH_COUNT_DI        1

#define FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xC5000)
#define FLASH_STRIDE_DISCHARGE_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_DISCHARGE_HIGH_TEMP_PRO        1

#define FLASH_ADDR_DISCHARGE_TEMP_BASE    (0x00000000 + 0xCA000)
#define FLASH_STRIDE_DISCHARGE_TEMP       2718
#define FLASH_COUNT_DISCHARGE_TEMP        1

#define FLASH_ADDR_DOUHAO_BASE    (0x00000000 + 0xCB000)
#define FLASH_STRIDE_DOUHAO       450
#define FLASH_COUNT_DOUHAO        1

#define FLASH_ADDR_GONG_BASE    (0x00000000 + 0xCC000)
#define FLASH_STRIDE_GONG       678
#define FLASH_COUNT_GONG        1

#define FLASH_ADDR_HEALTH_BASE    (0x00000000 + 0xCD000)
#define FLASH_STRIDE_HEALTH       7746
#define FLASH_COUNT_HEALTH        1

#define FLASH_ADDR_LEFT_1_ORANGE_BASE    (0x00000000 + 0xCF000)
#define FLASH_STRIDE_LEFT_1_ORANGE       11586
#define FLASH_COUNT_LEFT_1_ORANGE        1

#define FLASH_ADDR_LEFT_2_BLUE_BASE    (0x00000000 + 0xD2000)
#define FLASH_STRIDE_LEFT_2_BLUE       8994
#define FLASH_COUNT_LEFT_2_BLUE        1

#define FLASH_ADDR_LEFT_2_ORANGE_BASE    (0x00000000 + 0xD5000)
#define FLASH_STRIDE_LEFT_2_ORANGE       8994
#define FLASH_COUNT_LEFT_2_ORANGE        1

#define FLASH_ADDR_LEFT_3_BLUE_BASE    (0x00000000 + 0xD8000)
#define FLASH_STRIDE_LEFT_3_BLUE       6402
#define FLASH_COUNT_LEFT_3_BLUE        1

#define FLASH_ADDR_MINI_BASE    (0x00000000 + 0xDA000)
#define FLASH_STRIDE_MINI       2946
#define FLASH_COUNT_MINI        1

#define FLASH_ADDR_NO_ABNORMAL_BASE    (0x00000000 + 0xDB000)
#define FLASH_STRIDE_NO_ABNORMAL       5026
#define FLASH_COUNT_NO_ABNORMAL        1

#define FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO_BASE    (0x00000000 + 0xDD000)
#define FLASH_STRIDE_NOAMAL_HIGH_TEMP_PRO       17346
#define FLASH_COUNT_NOAMAL_HIGH_TEMP_PRO        1

#define FLASH_ADDR_NOAMAL_TEMP_BASE    (0x00000000 + 0xE2000)
#define FLASH_STRIDE_NOAMAL_TEMP       2718
#define FLASH_COUNT_NOAMAL_TEMP        1

#define FLASH_ADDR_NUM_12_BASE    (0x00000000 + 0xE3000)
#define FLASH_STRIDE_NUM_12       346
#define FLASH_COUNT_NUM_12        40

#define FLASH_ADDR_NUM_16_BASE    (0x00000000 + 0xE7000)
#define FLASH_STRIDE_NUM_16       770
#define FLASH_COUNT_NUM_16        40

#define FLASH_ADDR_NUM_20_BASE    (0x00000000 + 0xEF000)
#define FLASH_STRIDE_NUM_20       738
#define FLASH_COUNT_NUM_20        10

#define FLASH_ADDR_NUM_20_COLON_BASE    (0x00000000 + 0xF1000)
#define FLASH_STRIDE_NUM_20_COLON       450
#define FLASH_COUNT_NUM_20_COLON        1

#define FLASH_ADDR_NUM_40_BASE    (0x00000000 + 0xF2000)
#define FLASH_STRIDE_NUM_40       1986
#define FLASH_COUNT_NUM_40        11

#define FLASH_ADDR_NUM_40_DEGREE_BASE    (0x00000000 + 0xF8000)
#define FLASH_STRIDE_NUM_40_DEGREE       1346
#define FLASH_COUNT_NUM_40_DEGREE        1

#define FLASH_ADDR_NUM_40_PERCENT_BASE    (0x00000000 + 0xF9000)
#define FLASH_STRIDE_NUM_40_PERCENT       1346
#define FLASH_COUNT_NUM_40_PERCENT        1

#define FLASH_ADDR_ORANGE_CHARGING_001_BASE    (0x00000000 + 0xFA000)
#define FLASH_STRIDE_ORANGE_CHARGING_001       8490
#define FLASH_COUNT_ORANGE_CHARGING_001        1

#define FLASH_ADDR_ORANGE_CHARGING_002_BASE    (0x00000000 + 0xFD000)
#define FLASH_STRIDE_ORANGE_CHARGING_002       8490
#define FLASH_COUNT_ORANGE_CHARGING_002        1

#define FLASH_ADDR_ORANGE_CHARGING_003_BASE    (0x00000000 + 0x100000)
#define FLASH_STRIDE_ORANGE_CHARGING_003       8490
#define FLASH_COUNT_ORANGE_CHARGING_003        1

#define FLASH_ADDR_ORANGE_CHARGING_004_BASE    (0x00000000 + 0x103000)
#define FLASH_STRIDE_ORANGE_CHARGING_004       8490
#define FLASH_COUNT_ORANGE_CHARGING_004        1

#define FLASH_ADDR_ORANGE_CHARGING_005_BASE    (0x00000000 + 0x106000)
#define FLASH_STRIDE_ORANGE_CHARGING_005       8490
#define FLASH_COUNT_ORANGE_CHARGING_005        1

#define FLASH_ADDR_ORANGE_CHARGING_006_BASE    (0x00000000 + 0x109000)
#define FLASH_STRIDE_ORANGE_CHARGING_006       8490
#define FLASH_COUNT_ORANGE_CHARGING_006        1

#define FLASH_ADDR_ORANGE_CHARGING_007_BASE    (0x00000000 + 0x10C000)
#define FLASH_STRIDE_ORANGE_CHARGING_007       8490
#define FLASH_COUNT_ORANGE_CHARGING_007        1

#define FLASH_ADDR_ORANGE_CHARGING_008_BASE    (0x00000000 + 0x10F000)
#define FLASH_STRIDE_ORANGE_CHARGING_008       8490
#define FLASH_COUNT_ORANGE_CHARGING_008        1

#define FLASH_ADDR_ORANGE_CHARGING_009_BASE    (0x00000000 + 0x112000)
#define FLASH_STRIDE_ORANGE_CHARGING_009       8490
#define FLASH_COUNT_ORANGE_CHARGING_009        1

#define FLASH_ADDR_ORANGE_CHARGING_010_BASE    (0x00000000 + 0x115000)
#define FLASH_STRIDE_ORANGE_CHARGING_010       8490
#define FLASH_COUNT_ORANGE_CHARGING_010        1

#define FLASH_ADDR_ORANGE_CHARGING_011_BASE    (0x00000000 + 0x118000)
#define FLASH_STRIDE_ORANGE_CHARGING_011       8490
#define FLASH_COUNT_ORANGE_CHARGING_011        1

#define FLASH_ADDR_ORANGE_CHARGING_012_BASE    (0x00000000 + 0x11B000)
#define FLASH_STRIDE_ORANGE_CHARGING_012       8490
#define FLASH_COUNT_ORANGE_CHARGING_012        1

#define FLASH_ADDR_ORANGE_CHARGING_013_BASE    (0x00000000 + 0x11E000)
#define FLASH_STRIDE_ORANGE_CHARGING_013       8490
#define FLASH_COUNT_ORANGE_CHARGING_013        1

#define FLASH_ADDR_ORANGE_CHARGING_014_BASE    (0x00000000 + 0x121000)
#define FLASH_STRIDE_ORANGE_CHARGING_014       8490
#define FLASH_COUNT_ORANGE_CHARGING_014        1

#define FLASH_ADDR_ORANGE_CHARGING_015_BASE    (0x00000000 + 0x124000)
#define FLASH_STRIDE_ORANGE_CHARGING_015       8490
#define FLASH_COUNT_ORANGE_CHARGING_015        1

#define FLASH_ADDR_ORANGE_CHARGING_016_BASE    (0x00000000 + 0x127000)
#define FLASH_STRIDE_ORANGE_CHARGING_016       8490
#define FLASH_COUNT_ORANGE_CHARGING_016        1

#define FLASH_ADDR_ORANGE_CHARGING_017_BASE    (0x00000000 + 0x12A000)
#define FLASH_STRIDE_ORANGE_CHARGING_017       8490
#define FLASH_COUNT_ORANGE_CHARGING_017        1

#define FLASH_ADDR_ORANGE_CHARGING_018_BASE    (0x00000000 + 0x12D000)
#define FLASH_STRIDE_ORANGE_CHARGING_018       8490
#define FLASH_COUNT_ORANGE_CHARGING_018        1

#define FLASH_ADDR_ORANGE_CHARGING_019_BASE    (0x00000000 + 0x130000)
#define FLASH_STRIDE_ORANGE_CHARGING_019       8490
#define FLASH_COUNT_ORANGE_CHARGING_019        1

#define FLASH_ADDR_ORANGE_CHARGING_020_BASE    (0x00000000 + 0x133000)
#define FLASH_STRIDE_ORANGE_CHARGING_020       8490
#define FLASH_COUNT_ORANGE_CHARGING_020        1

#define FLASH_ADDR_ORANGE_CHARGING_021_BASE    (0x00000000 + 0x136000)
#define FLASH_STRIDE_ORANGE_CHARGING_021       8490
#define FLASH_COUNT_ORANGE_CHARGING_021        1

#define FLASH_ADDR_ORANGE_CHARGING_022_BASE    (0x00000000 + 0x139000)
#define FLASH_STRIDE_ORANGE_CHARGING_022       8490
#define FLASH_COUNT_ORANGE_CHARGING_022        1

#define FLASH_ADDR_ORANGE_CHARGING_023_BASE    (0x00000000 + 0x13C000)
#define FLASH_STRIDE_ORANGE_CHARGING_023       8490
#define FLASH_COUNT_ORANGE_CHARGING_023        1

#define FLASH_ADDR_ORANGE_CHARGING_024_BASE    (0x00000000 + 0x13F000)
#define FLASH_STRIDE_ORANGE_CHARGING_024       8490
#define FLASH_COUNT_ORANGE_CHARGING_024        1

#define FLASH_ADDR_ORANGE_CHARGING_025_BASE    (0x00000000 + 0x142000)
#define FLASH_STRIDE_ORANGE_CHARGING_025       8490
#define FLASH_COUNT_ORANGE_CHARGING_025        1

#define FLASH_ADDR_ORANGE_CHARGING_026_BASE    (0x00000000 + 0x145000)
#define FLASH_STRIDE_ORANGE_CHARGING_026       8490
#define FLASH_COUNT_ORANGE_CHARGING_026        1

#define FLASH_ADDR_ORANGE_CHARGING_027_BASE    (0x00000000 + 0x148000)
#define FLASH_STRIDE_ORANGE_CHARGING_027       8490
#define FLASH_COUNT_ORANGE_CHARGING_027        1

#define FLASH_ADDR_ORANGE_CHARGING_028_BASE    (0x00000000 + 0x14B000)
#define FLASH_STRIDE_ORANGE_CHARGING_028       8490
#define FLASH_COUNT_ORANGE_CHARGING_028        1

#define FLASH_ADDR_ORANGE_CHARGING_029_BASE    (0x00000000 + 0x14E000)
#define FLASH_STRIDE_ORANGE_CHARGING_029       8490
#define FLASH_COUNT_ORANGE_CHARGING_029        1

#define FLASH_ADDR_ORANGE_CHARGING_030_BASE    (0x00000000 + 0x151000)
#define FLASH_STRIDE_ORANGE_CHARGING_030       8490
#define FLASH_COUNT_ORANGE_CHARGING_030        1

#define FLASH_ADDR_ORANGE_CHARGING_031_BASE    (0x00000000 + 0x154000)
#define FLASH_STRIDE_ORANGE_CHARGING_031       8490
#define FLASH_COUNT_ORANGE_CHARGING_031        1

#define FLASH_ADDR_ORANGE_CHARGING_032_BASE    (0x00000000 + 0x157000)
#define FLASH_STRIDE_ORANGE_CHARGING_032       8490
#define FLASH_COUNT_ORANGE_CHARGING_032        1

#define FLASH_ADDR_ORANGE_CHARGING_033_BASE    (0x00000000 + 0x15A000)
#define FLASH_STRIDE_ORANGE_CHARGING_033       8490
#define FLASH_COUNT_ORANGE_CHARGING_033        1

#define FLASH_ADDR_ORANGE_CHARGING_034_BASE    (0x00000000 + 0x15D000)
#define FLASH_STRIDE_ORANGE_CHARGING_034       8490
#define FLASH_COUNT_ORANGE_CHARGING_034        1

#define FLASH_ADDR_ORANGE_CHARGING_035_BASE    (0x00000000 + 0x160000)
#define FLASH_STRIDE_ORANGE_CHARGING_035       8490
#define FLASH_COUNT_ORANGE_CHARGING_035        1

#define FLASH_ADDR_ORANGE_CHARGING_036_BASE    (0x00000000 + 0x163000)
#define FLASH_STRIDE_ORANGE_CHARGING_036       8490
#define FLASH_COUNT_ORANGE_CHARGING_036        1

#define FLASH_ADDR_ORANGE_CHARGING_037_BASE    (0x00000000 + 0x166000)
#define FLASH_STRIDE_ORANGE_CHARGING_037       8490
#define FLASH_COUNT_ORANGE_CHARGING_037        1

#define FLASH_ADDR_ORANGE_CHARGING_038_BASE    (0x00000000 + 0x169000)
#define FLASH_STRIDE_ORANGE_CHARGING_038       8490
#define FLASH_COUNT_ORANGE_CHARGING_038        1

#define FLASH_ADDR_ORANGE_CHARGING_039_BASE    (0x00000000 + 0x16C000)
#define FLASH_STRIDE_ORANGE_CHARGING_039       8490
#define FLASH_COUNT_ORANGE_CHARGING_039        1

#define FLASH_ADDR_ORANGE_CHARGING_040_BASE    (0x00000000 + 0x16F000)
#define FLASH_STRIDE_ORANGE_CHARGING_040       8490
#define FLASH_COUNT_ORANGE_CHARGING_040        1

#define FLASH_ADDR_OUT_BASE    (0x00000000 + 0x172000)
#define FLASH_STRIDE_OUT       2178
#define FLASH_COUNT_OUT        1

#define FLASH_ADDR_POWER_PART_1_USB_A_BLUE_BASE    (0x00000000 + 0x173000)
#define FLASH_STRIDE_POWER_PART_1_USB_A_BLUE       5286
#define FLASH_COUNT_POWER_PART_1_USB_A_BLUE        1

#define FLASH_ADDR_POWER_PART_1_USB_A_WHITE_BASE    (0x00000000 + 0x175000)
#define FLASH_STRIDE_POWER_PART_1_USB_A_WHITE       5286
#define FLASH_COUNT_POWER_PART_1_USB_A_WHITE        1

#define FLASH_ADDR_POWER_PART_1_USB_C_BLUE_BASE    (0x00000000 + 0x177000)
#define FLASH_STRIDE_POWER_PART_1_USB_C_BLUE       5286
#define FLASH_COUNT_POWER_PART_1_USB_C_BLUE        1

#define FLASH_ADDR_POWER_PART_1_USB_C_WHITE_BASE    (0x00000000 + 0x179000)
#define FLASH_STRIDE_POWER_PART_1_USB_C_WHITE       5286
#define FLASH_COUNT_POWER_PART_1_USB_C_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_1_BLUE_BASE    (0x00000000 + 0x17B000)
#define FLASH_STRIDE_POWER_PART_2_PORT_1_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_1_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_1_WHITE_BASE    (0x00000000 + 0x17C000)
#define FLASH_STRIDE_POWER_PART_2_PORT_1_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_1_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_2_BLUE_BASE    (0x00000000 + 0x17D000)
#define FLASH_STRIDE_POWER_PART_2_PORT_2_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_2_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_2_WHITE_BASE    (0x00000000 + 0x17E000)
#define FLASH_STRIDE_POWER_PART_2_PORT_2_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_2_WHITE        1

#define FLASH_ADDR_POWER_PART_2_PORT_3_BLUE_BASE    (0x00000000 + 0x17F000)
#define FLASH_STRIDE_POWER_PART_2_PORT_3_BLUE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_3_BLUE        1

#define FLASH_ADDR_POWER_PART_2_PORT_3_WHITE_BASE    (0x00000000 + 0x180000)
#define FLASH_STRIDE_POWER_PART_2_PORT_3_WHITE       1506
#define FLASH_COUNT_POWER_PART_2_PORT_3_WHITE        1

#define FLASH_ADDR_POWER_PART_3_IN_BLUE_BASE    (0x00000000 + 0x181000)
#define FLASH_STRIDE_POWER_PART_3_IN_BLUE       6366
#define FLASH_COUNT_POWER_PART_3_IN_BLUE        1

#define FLASH_ADDR_POWER_PART_3_OUT_BLUE_BASE    (0x00000000 + 0x183000)
#define FLASH_STRIDE_POWER_PART_3_OUT_BLUE       6366
#define FLASH_COUNT_POWER_PART_3_OUT_BLUE        1

#define FLASH_ADDR_POWER_PART_3_WHITE_BASE    (0x00000000 + 0x185000)
#define FLASH_STRIDE_POWER_PART_3_WHITE       6366
#define FLASH_COUNT_POWER_PART_3_WHITE        1

#define FLASH_ADDR_POWER_PART_4_0_BLUE_BASE    (0x00000000 + 0x187000)
#define FLASH_STRIDE_POWER_PART_4_0_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_0_BLUE        1

#define FLASH_ADDR_POWER_PART_4_0_WHITE_BASE    (0x00000000 + 0x188000)
#define FLASH_STRIDE_POWER_PART_4_0_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_0_WHITE        1

#define FLASH_ADDR_POWER_PART_4_1_BLUE_BASE    (0x00000000 + 0x189000)
#define FLASH_STRIDE_POWER_PART_4_1_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_1_BLUE        1

#define FLASH_ADDR_POWER_PART_4_1_WHITE_BASE    (0x00000000 + 0x18A000)
#define FLASH_STRIDE_POWER_PART_4_1_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_1_WHITE        1

#define FLASH_ADDR_POWER_PART_4_2_BLUE_BASE    (0x00000000 + 0x18B000)
#define FLASH_STRIDE_POWER_PART_4_2_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_2_BLUE        1

#define FLASH_ADDR_POWER_PART_4_2_WHITE_BASE    (0x00000000 + 0x18C000)
#define FLASH_STRIDE_POWER_PART_4_2_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_2_WHITE        1

#define FLASH_ADDR_POWER_PART_4_3_BLUE_BASE    (0x00000000 + 0x18D000)
#define FLASH_STRIDE_POWER_PART_4_3_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_3_BLUE        1

#define FLASH_ADDR_POWER_PART_4_3_WHITE_BASE    (0x00000000 + 0x18E000)
#define FLASH_STRIDE_POWER_PART_4_3_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_3_WHITE        1

#define FLASH_ADDR_POWER_PART_4_4_BLUE_BASE    (0x00000000 + 0x18F000)
#define FLASH_STRIDE_POWER_PART_4_4_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_4_BLUE        1

#define FLASH_ADDR_POWER_PART_4_4_WHITE_BASE    (0x00000000 + 0x190000)
#define FLASH_STRIDE_POWER_PART_4_4_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_4_WHITE        1

#define FLASH_ADDR_POWER_PART_4_5_BLUE_BASE    (0x00000000 + 0x191000)
#define FLASH_STRIDE_POWER_PART_4_5_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_5_BLUE        1

#define FLASH_ADDR_POWER_PART_4_5_WHITE_BASE    (0x00000000 + 0x192000)
#define FLASH_STRIDE_POWER_PART_4_5_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_5_WHITE        1

#define FLASH_ADDR_POWER_PART_4_6_BLUE_BASE    (0x00000000 + 0x193000)
#define FLASH_STRIDE_POWER_PART_4_6_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_6_BLUE        1

#define FLASH_ADDR_POWER_PART_4_6_WHITE_BASE    (0x00000000 + 0x194000)
#define FLASH_STRIDE_POWER_PART_4_6_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_6_WHITE        1

#define FLASH_ADDR_POWER_PART_4_7_BLUE_BASE    (0x00000000 + 0x195000)
#define FLASH_STRIDE_POWER_PART_4_7_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_7_BLUE        1

#define FLASH_ADDR_POWER_PART_4_7_WHITE_BASE    (0x00000000 + 0x196000)
#define FLASH_STRIDE_POWER_PART_4_7_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_7_WHITE        1

#define FLASH_ADDR_POWER_PART_4_8_BLUE_BASE    (0x00000000 + 0x197000)
#define FLASH_STRIDE_POWER_PART_4_8_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_8_BLUE        1

#define FLASH_ADDR_POWER_PART_4_8_WHITE_BASE    (0x00000000 + 0x198000)
#define FLASH_STRIDE_POWER_PART_4_8_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_8_WHITE        1

#define FLASH_ADDR_POWER_PART_4_9_BLUE_BASE    (0x00000000 + 0x199000)
#define FLASH_STRIDE_POWER_PART_4_9_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_9_BLUE        1

#define FLASH_ADDR_POWER_PART_4_9_WHITE_BASE    (0x00000000 + 0x19A000)
#define FLASH_STRIDE_POWER_PART_4_9_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_9_WHITE        1

#define FLASH_ADDR_POWER_PART_4_BLUE_BASE    (0x00000000 + 0x19B000)
#define FLASH_STRIDE_POWER_PART_4_BLUE       1866
#define FLASH_COUNT_POWER_PART_4_BLUE        1

#define FLASH_ADDR_POWER_PART_4_WHITE_BASE    (0x00000000 + 0x19C000)
#define FLASH_STRIDE_POWER_PART_4_WHITE       1866
#define FLASH_COUNT_POWER_PART_4_WHITE        1

#define FLASH_ADDR_POWER_PART_5_BLUE_BASE    (0x00000000 + 0x19D000)
#define FLASH_STRIDE_POWER_PART_5_BLUE       3486
#define FLASH_COUNT_POWER_PART_5_BLUE        1

#define FLASH_ADDR_POWER_PART_5_WHITE_BASE    (0x00000000 + 0x19E000)
#define FLASH_STRIDE_POWER_PART_5_WHITE       3486
#define FLASH_COUNT_POWER_PART_5_WHITE        1

#define FLASH_ADDR_RIGHT_1_ORANGE_BASE    (0x00000000 + 0x19F000)
#define FLASH_STRIDE_RIGHT_1_ORANGE       11586
#define FLASH_COUNT_RIGHT_1_ORANGE        1

#define FLASH_ADDR_RIGHT_2_BLUE_BASE    (0x00000000 + 0x1A2000)
#define FLASH_STRIDE_RIGHT_2_BLUE       8994
#define FLASH_COUNT_RIGHT_2_BLUE        1

#define FLASH_ADDR_RIGHT_2_ORANGE_BASE    (0x00000000 + 0x1A5000)
#define FLASH_STRIDE_RIGHT_2_ORANGE       8994
#define FLASH_COUNT_RIGHT_2_ORANGE        1

#define FLASH_ADDR_RIGHT_3_BLUE_BASE    (0x00000000 + 0x1A8000)
#define FLASH_STRIDE_RIGHT_3_BLUE       6402
#define FLASH_COUNT_RIGHT_3_BLUE        1

#define FLASH_ADDR_SAFE_BASE    (0x00000000 + 0x1AA000)
#define FLASH_STRIDE_SAFE       12866
#define FLASH_COUNT_SAFE        1

#define FLASH_ADDR_SAFEGUARD_BASE    (0x00000000 + 0x1AE000)
#define FLASH_STRIDE_SAFEGUARD       26466
#define FLASH_COUNT_SAFEGUARD        1

#define FLASH_ADDR_TEMP_ABNORMAL_BASE    (0x00000000 + 0x1B5000)
#define FLASH_STRIDE_TEMP_ABNORMAL       15426
#define FLASH_COUNT_TEMP_ABNORMAL        1

#define FLASH_ADDR_TEMP_ORANGE_BASE    (0x00000000 + 0x1B9000)
#define FLASH_STRIDE_TEMP_ORANGE       12866
#define FLASH_COUNT_TEMP_ORANGE        1

#define FLASH_ADDR_TEMPERATURE_RECOVERY_BASE    (0x00000000 + 0x1BD000)
#define FLASH_STRIDE_TEMPERATURE_RECOVERY       9186
#define FLASH_COUNT_TEMPERATURE_RECOVERY        1

#define FLASH_ADDR_TIAO_BASE    (0x00000000 + 0x1C0000)
#define FLASH_STRIDE_TIAO       678
#define FLASH_COUNT_TIAO        1

#define FLASH_ADDR_TIMER_BASE    (0x00000000 + 0x1C1000)
#define FLASH_STRIDE_TIMER       1026
#define FLASH_COUNT_TIMER        1

#define FLASH_ADDR_TOTAL_VOLTAGE_BASE    (0x00000000 + 0x1C2000)
#define FLASH_STRIDE_TOTAL_VOLTAGE       1986
#define FLASH_COUNT_TOTAL_VOLTAGE        1

#define FLASH_ADDR_VOLTAGE_ABNORMAL_BASE    (0x00000000 + 0x1C3000)
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
#define FLASH_ADDR_A_CELL_VOLTAGE             (0x00000000 + 0x0000)
#define FLASH_SIZE_A_CELL_VOLTAGE             15426
#define FLASH_ADDR_ABNORMAL_TIME              (0x00000000 + 0x4000)
#define FLASH_SIZE_ABNORMAL_TIME              1474
#define FLASH_ADDR_ABNORMAL_V                 (0x00000000 + 0x5000)
#define FLASH_SIZE_ABNORMAL_V                 1474
#define FLASH_ADDR_BAT_0_BLUE                 (0x00000000 + 0x6000)
#define FLASH_SIZE_BAT_0_BLUE                 5250
#define FLASH_ADDR_BAT_0_ORANGE               (0x00000000 + 0x8000)
#define FLASH_SIZE_BAT_0_ORANGE               5250
#define FLASH_ADDR_BAT_1_BLUE                 (0x00000000 + 0xA000)
#define FLASH_SIZE_BAT_1_BLUE                 5250
#define FLASH_ADDR_BAT_1_ORANGE               (0x00000000 + 0xC000)
#define FLASH_SIZE_BAT_1_ORANGE               5250
#define FLASH_ADDR_BAT_2_BLUE                 (0x00000000 + 0xE000)
#define FLASH_SIZE_BAT_2_BLUE                 5250
#define FLASH_ADDR_BAT_2_ORANGE               (0x00000000 + 0x10000)
#define FLASH_SIZE_BAT_2_ORANGE               5250
#define FLASH_ADDR_BAT_3_BLUE                 (0x00000000 + 0x12000)
#define FLASH_SIZE_BAT_3_BLUE                 5250
#define FLASH_ADDR_BAT_3_ORANGE               (0x00000000 + 0x14000)
#define FLASH_SIZE_BAT_3_ORANGE               5250
#define FLASH_ADDR_BAT_4_BLUE                 (0x00000000 + 0x16000)
#define FLASH_SIZE_BAT_4_BLUE                 5250
#define FLASH_ADDR_BAT_4_ORANGE               (0x00000000 + 0x18000)
#define FLASH_SIZE_BAT_4_ORANGE               5250
#define FLASH_ADDR_BAT_5_BLUE                 (0x00000000 + 0x1A000)
#define FLASH_SIZE_BAT_5_BLUE                 5250
#define FLASH_ADDR_BAT_5_ORANGE               (0x00000000 + 0x1C000)
#define FLASH_SIZE_BAT_5_ORANGE               5250
#define FLASH_ADDR_BAT_6_BLUE                 (0x00000000 + 0x1E000)
#define FLASH_SIZE_BAT_6_BLUE                 5250
#define FLASH_ADDR_BAT_6_ORANGE               (0x00000000 + 0x20000)
#define FLASH_SIZE_BAT_6_ORANGE               5250
#define FLASH_ADDR_BAT_7_BLUE                 (0x00000000 + 0x22000)
#define FLASH_SIZE_BAT_7_BLUE                 5250
#define FLASH_ADDR_BAT_7_ORANGE               (0x00000000 + 0x24000)
#define FLASH_SIZE_BAT_7_ORANGE               5250
#define FLASH_ADDR_BAT_8_BLUE                 (0x00000000 + 0x26000)
#define FLASH_SIZE_BAT_8_BLUE                 5250
#define FLASH_ADDR_BAT_8_ORANGE               (0x00000000 + 0x28000)
#define FLASH_SIZE_BAT_8_ORANGE               5250
#define FLASH_ADDR_BAT_9_BLUE                 (0x00000000 + 0x2A000)
#define FLASH_SIZE_BAT_9_BLUE                 5250
#define FLASH_ADDR_BAT_9_ORANGE               (0x00000000 + 0x2C000)
#define FLASH_SIZE_BAT_9_ORANGE               5250
#define FLASH_ADDR_BAT_NUM                    (0x00000000 + 0x2E000)
#define FLASH_SIZE_BAT_NUM                    2562
#define FLASH_ADDR_BAT_PER_BLUE               (0x00000000 + 0x2F000)
#define FLASH_SIZE_BAT_PER_BLUE               6402
#define FLASH_ADDR_BAT_PER_ORANGE             (0x00000000 + 0x31000)
#define FLASH_SIZE_BAT_PER_ORANGE             6402
#define FLASH_ADDR_BAT_TMP                    (0x00000000 + 0x33000)
#define FLASH_SIZE_BAT_TMP                    15426
#define FLASH_ADDR_BLUE_CHARGING_001          (0x00000000 + 0x37000)
#define FLASH_SIZE_BLUE_CHARGING_001          8490
#define FLASH_ADDR_BLUE_CHARGING_002          (0x00000000 + 0x3A000)
#define FLASH_SIZE_BLUE_CHARGING_002          8490
#define FLASH_ADDR_BLUE_CHARGING_003          (0x00000000 + 0x3D000)
#define FLASH_SIZE_BLUE_CHARGING_003          8490
#define FLASH_ADDR_BLUE_CHARGING_004          (0x00000000 + 0x40000)
#define FLASH_SIZE_BLUE_CHARGING_004          8490
#define FLASH_ADDR_BLUE_CHARGING_005          (0x00000000 + 0x43000)
#define FLASH_SIZE_BLUE_CHARGING_005          8490
#define FLASH_ADDR_BLUE_CHARGING_006          (0x00000000 + 0x46000)
#define FLASH_SIZE_BLUE_CHARGING_006          8490
#define FLASH_ADDR_BLUE_CHARGING_007          (0x00000000 + 0x49000)
#define FLASH_SIZE_BLUE_CHARGING_007          8490
#define FLASH_ADDR_BLUE_CHARGING_008          (0x00000000 + 0x4C000)
#define FLASH_SIZE_BLUE_CHARGING_008          8490
#define FLASH_ADDR_BLUE_CHARGING_009          (0x00000000 + 0x4F000)
#define FLASH_SIZE_BLUE_CHARGING_009          8490
#define FLASH_ADDR_BLUE_CHARGING_010          (0x00000000 + 0x52000)
#define FLASH_SIZE_BLUE_CHARGING_010          8490
#define FLASH_ADDR_BLUE_CHARGING_011          (0x00000000 + 0x55000)
#define FLASH_SIZE_BLUE_CHARGING_011          8490
#define FLASH_ADDR_BLUE_CHARGING_012          (0x00000000 + 0x58000)
#define FLASH_SIZE_BLUE_CHARGING_012          8490
#define FLASH_ADDR_BLUE_CHARGING_013          (0x00000000 + 0x5B000)
#define FLASH_SIZE_BLUE_CHARGING_013          8490
#define FLASH_ADDR_BLUE_CHARGING_014          (0x00000000 + 0x5E000)
#define FLASH_SIZE_BLUE_CHARGING_014          8490
#define FLASH_ADDR_BLUE_CHARGING_015          (0x00000000 + 0x61000)
#define FLASH_SIZE_BLUE_CHARGING_015          8490
#define FLASH_ADDR_BLUE_CHARGING_016          (0x00000000 + 0x64000)
#define FLASH_SIZE_BLUE_CHARGING_016          8490
#define FLASH_ADDR_BLUE_CHARGING_017          (0x00000000 + 0x67000)
#define FLASH_SIZE_BLUE_CHARGING_017          8490
#define FLASH_ADDR_BLUE_CHARGING_018          (0x00000000 + 0x6A000)
#define FLASH_SIZE_BLUE_CHARGING_018          8490
#define FLASH_ADDR_BLUE_CHARGING_019          (0x00000000 + 0x6D000)
#define FLASH_SIZE_BLUE_CHARGING_019          8490
#define FLASH_ADDR_BLUE_CHARGING_020          (0x00000000 + 0x70000)
#define FLASH_SIZE_BLUE_CHARGING_020          8490
#define FLASH_ADDR_BLUE_CHARGING_021          (0x00000000 + 0x73000)
#define FLASH_SIZE_BLUE_CHARGING_021          8490
#define FLASH_ADDR_BLUE_CHARGING_022          (0x00000000 + 0x76000)
#define FLASH_SIZE_BLUE_CHARGING_022          8490
#define FLASH_ADDR_BLUE_CHARGING_023          (0x00000000 + 0x79000)
#define FLASH_SIZE_BLUE_CHARGING_023          8490
#define FLASH_ADDR_BLUE_CHARGING_024          (0x00000000 + 0x7C000)
#define FLASH_SIZE_BLUE_CHARGING_024          8490
#define FLASH_ADDR_BLUE_CHARGING_025          (0x00000000 + 0x7F000)
#define FLASH_SIZE_BLUE_CHARGING_025          8490
#define FLASH_ADDR_BLUE_CHARGING_026          (0x00000000 + 0x82000)
#define FLASH_SIZE_BLUE_CHARGING_026          8490
#define FLASH_ADDR_BLUE_CHARGING_027          (0x00000000 + 0x85000)
#define FLASH_SIZE_BLUE_CHARGING_027          8490
#define FLASH_ADDR_BLUE_CHARGING_028          (0x00000000 + 0x88000)
#define FLASH_SIZE_BLUE_CHARGING_028          8490
#define FLASH_ADDR_BLUE_CHARGING_029          (0x00000000 + 0x8B000)
#define FLASH_SIZE_BLUE_CHARGING_029          8490
#define FLASH_ADDR_BLUE_CHARGING_030          (0x00000000 + 0x8E000)
#define FLASH_SIZE_BLUE_CHARGING_030          8490
#define FLASH_ADDR_BLUE_CHARGING_031          (0x00000000 + 0x91000)
#define FLASH_SIZE_BLUE_CHARGING_031          8490
#define FLASH_ADDR_BLUE_CHARGING_032          (0x00000000 + 0x94000)
#define FLASH_SIZE_BLUE_CHARGING_032          8490
#define FLASH_ADDR_BLUE_CHARGING_033          (0x00000000 + 0x97000)
#define FLASH_SIZE_BLUE_CHARGING_033          8490
#define FLASH_ADDR_BLUE_CHARGING_034          (0x00000000 + 0x9A000)
#define FLASH_SIZE_BLUE_CHARGING_034          8490
#define FLASH_ADDR_BLUE_CHARGING_035          (0x00000000 + 0x9D000)
#define FLASH_SIZE_BLUE_CHARGING_035          8490
#define FLASH_ADDR_BLUE_CHARGING_036          (0x00000000 + 0xA0000)
#define FLASH_SIZE_BLUE_CHARGING_036          8490
#define FLASH_ADDR_BLUE_CHARGING_037          (0x00000000 + 0xA3000)
#define FLASH_SIZE_BLUE_CHARGING_037          8490
#define FLASH_ADDR_BLUE_CHARGING_038          (0x00000000 + 0xA6000)
#define FLASH_SIZE_BLUE_CHARGING_038          8490
#define FLASH_ADDR_BLUE_CHARGING_039          (0x00000000 + 0xA9000)
#define FLASH_SIZE_BLUE_CHARGING_039          8490
#define FLASH_ADDR_BLUE_CHARGING_040          (0x00000000 + 0xAC000)
#define FLASH_SIZE_BLUE_CHARGING_040          8490
#define FLASH_ADDR_CHARGE_HIGH_TEMP_PRO       (0x00000000 + 0xAF000)
#define FLASH_SIZE_CHARGE_HIGH_TEMP_PRO       17346
#define FLASH_ADDR_CHARGE_TEMP                (0x00000000 + 0xB4000)
#define FLASH_SIZE_CHARGE_TEMP                2718
#define FLASH_ADDR_CI                         (0x00000000 + 0xB5000)
#define FLASH_SIZE_CI                         1346
#define FLASH_ADDR_CIRCUIT_PROTECTION         (0x00000000 + 0xB6000)
#define FLASH_SIZE_CIRCUIT_PROTECTION         12866
#define FLASH_ADDR_CIRCUIT_PROTECTION_TEXT    (0x00000000 + 0xBA000)
#define FLASH_SIZE_CIRCUIT_PROTECTION_TEXT    17346
#define FLASH_ADDR_CIRCUIT_RECOVERY           (0x00000000 + 0xBF000)
#define FLASH_SIZE_CIRCUIT_RECOVERY           9186
#define FLASH_ADDR_CYCLE_INDEX                (0x00000000 + 0xC2000)
#define FLASH_SIZE_CYCLE_INDEX                7746
#define FLASH_ADDR_DI                         (0x00000000 + 0xC4000)
#define FLASH_SIZE_DI                         678
#define FLASH_ADDR_DISCHARGE_HIGH_TEMP_PRO    (0x00000000 + 0xC5000)
#define FLASH_SIZE_DISCHARGE_HIGH_TEMP_PRO    17346
#define FLASH_ADDR_DISCHARGE_TEMP             (0x00000000 + 0xCA000)
#define FLASH_SIZE_DISCHARGE_TEMP             2718
#define FLASH_ADDR_DOUHAO                     (0x00000000 + 0xCB000)
#define FLASH_SIZE_DOUHAO                     450
#define FLASH_ADDR_GONG                       (0x00000000 + 0xCC000)
#define FLASH_SIZE_GONG                       678
#define FLASH_ADDR_HEALTH                     (0x00000000 + 0xCD000)
#define FLASH_SIZE_HEALTH                     7746
#define FLASH_ADDR_LEFT_1_ORANGE              (0x00000000 + 0xCF000)
#define FLASH_SIZE_LEFT_1_ORANGE              11586
#define FLASH_ADDR_LEFT_2_BLUE                (0x00000000 + 0xD2000)
#define FLASH_SIZE_LEFT_2_BLUE                8994
#define FLASH_ADDR_LEFT_2_ORANGE              (0x00000000 + 0xD5000)
#define FLASH_SIZE_LEFT_2_ORANGE              8994
#define FLASH_ADDR_LEFT_3_BLUE                (0x00000000 + 0xD8000)
#define FLASH_SIZE_LEFT_3_BLUE                6402
#define FLASH_ADDR_MINI                       (0x00000000 + 0xDA000)
#define FLASH_SIZE_MINI                       2946
#define FLASH_ADDR_NO_ABNORMAL                (0x00000000 + 0xDB000)
#define FLASH_SIZE_NO_ABNORMAL                5026
#define FLASH_ADDR_NOAMAL_HIGH_TEMP_PRO       (0x00000000 + 0xDD000)
#define FLASH_SIZE_NOAMAL_HIGH_TEMP_PRO       17346
#define FLASH_ADDR_NOAMAL_TEMP                (0x00000000 + 0xE2000)
#define FLASH_SIZE_NOAMAL_TEMP                2718
#define FLASH_ADDR_NUM_12_0                   (0x00000000 + 0xE3000)
#define FLASH_SIZE_NUM_12_0                   226
#define FLASH_ADDR_NUM_12_1                   (0x00000000 + 0xE315A)
#define FLASH_SIZE_NUM_12_1                   186
#define FLASH_ADDR_NUM_12_2                   (0x00000000 + 0xE32B4)
#define FLASH_SIZE_NUM_12_2                   226
#define FLASH_ADDR_NUM_12_3                   (0x00000000 + 0xE340E)
#define FLASH_SIZE_NUM_12_3                   226
#define FLASH_ADDR_NUM_12_4                   (0x00000000 + 0xE3568)
#define FLASH_SIZE_NUM_12_4                   266
#define FLASH_ADDR_NUM_12_5                   (0x00000000 + 0xE36C2)
#define FLASH_SIZE_NUM_12_5                   226
#define FLASH_ADDR_NUM_12_6                   (0x00000000 + 0xE381C)
#define FLASH_SIZE_NUM_12_6                   226
#define FLASH_ADDR_NUM_12_7                   (0x00000000 + 0xE3976)
#define FLASH_SIZE_NUM_12_7                   226
#define FLASH_ADDR_NUM_12_8                   (0x00000000 + 0xE3AD0)
#define FLASH_SIZE_NUM_12_8                   226
#define FLASH_ADDR_NUM_12_9                   (0x00000000 + 0xE3C2A)
#define FLASH_SIZE_NUM_12_9                   226
#define FLASH_ADDR_NUM_12                     (0x00000000 + 0xE3D84)
#define FLASH_SIZE_NUM_12                     226
#define FLASH_ADDR_NUM_12_A                   (0x00000000 + 0xE3EDE)
#define FLASH_SIZE_NUM_12_A                   266
#define FLASH_ADDR_NUM_12_B                   (0x00000000 + 0xE4038)
#define FLASH_SIZE_NUM_12_B                   226
#define FLASH_ADDR_NUM_12_C                   (0x00000000 + 0xE4192)
#define FLASH_SIZE_NUM_12_C                   266
#define FLASH_ADDR_NUM_12_D                   (0x00000000 + 0xE42EC)
#define FLASH_SIZE_NUM_12_D                   266
#define FLASH_ADDR_NUM_12_E                   (0x00000000 + 0xE4446)
#define FLASH_SIZE_NUM_12_E                   226
#define FLASH_ADDR_NUM_12_F                   (0x00000000 + 0xE45A0)
#define FLASH_SIZE_NUM_12_F                   226
#define FLASH_ADDR_NUM_12_G                   (0x00000000 + 0xE46FA)
#define FLASH_SIZE_NUM_12_G                   266
#define FLASH_ADDR_NUM_12_H                   (0x00000000 + 0xE4854)
#define FLASH_SIZE_NUM_12_H                   266
#define FLASH_ADDR_NUM_12_I                   (0x00000000 + 0xE49AE)
#define FLASH_SIZE_NUM_12_I                   186
#define FLASH_ADDR_NUM_12_J                   (0x00000000 + 0xE4B08)
#define FLASH_SIZE_NUM_12_J                   226
#define FLASH_ADDR_NUM_12_K                   (0x00000000 + 0xE4C62)
#define FLASH_SIZE_NUM_12_K                   226
#define FLASH_ADDR_NUM_12_L                   (0x00000000 + 0xE4DBC)
#define FLASH_SIZE_NUM_12_L                   226
#define FLASH_ADDR_NUM_12_M                   (0x00000000 + 0xE4F16)
#define FLASH_SIZE_NUM_12_M                   306
#define FLASH_ADDR_NUM_12_N                   (0x00000000 + 0xE5070)
#define FLASH_SIZE_NUM_12_N                   266
#define FLASH_ADDR_NUM_12_O                   (0x00000000 + 0xE51CA)
#define FLASH_SIZE_NUM_12_O                   266
#define FLASH_ADDR_NUM_12_P                   (0x00000000 + 0xE5324)
#define FLASH_SIZE_NUM_12_P                   226
#define FLASH_ADDR_NUM_12_Q                   (0x00000000 + 0xE547E)
#define FLASH_SIZE_NUM_12_Q                   266
#define FLASH_ADDR_NUM_12_R                   (0x00000000 + 0xE55D8)
#define FLASH_SIZE_NUM_12_R                   226
#define FLASH_ADDR_NUM_12_S                   (0x00000000 + 0xE5732)
#define FLASH_SIZE_NUM_12_S                   226
#define FLASH_ADDR_NUM_12_T                   (0x00000000 + 0xE588C)
#define FLASH_SIZE_NUM_12_T                   226
#define FLASH_ADDR_NUM_12_U                   (0x00000000 + 0xE59E6)
#define FLASH_SIZE_NUM_12_U                   266
#define FLASH_ADDR_NUM_12_V                   (0x00000000 + 0xE5B40)
#define FLASH_SIZE_NUM_12_V                   266
#define FLASH_ADDR_NUM_12_W                   (0x00000000 + 0xE5C9A)
#define FLASH_SIZE_NUM_12_W                   346
#define FLASH_ADDR_NUM_12_X                   (0x00000000 + 0xE5DF4)
#define FLASH_SIZE_NUM_12_X                   266
#define FLASH_ADDR_NUM_12_Y                   (0x00000000 + 0xE5F4E)
#define FLASH_SIZE_NUM_12_Y                   266
#define FLASH_ADDR_NUM_12_Z                   (0x00000000 + 0xE60A8)
#define FLASH_SIZE_NUM_12_Z                   266
#define FLASH_ADDR_NUM_12_Z_COLON             (0x00000000 + 0xE6202)
#define FLASH_SIZE_NUM_12_Z_COLON             186
#define FLASH_ADDR_NUM_12_Z_DEGREE            (0x00000000 + 0xE635C)
#define FLASH_SIZE_NUM_12_Z_DEGREE            346
#define FLASH_ADDR_NUM_12_Z_DOT               (0x00000000 + 0xE64B6)
#define FLASH_SIZE_NUM_12_Z_DOT               146
#define FLASH_ADDR_NUM_16_0                   (0x00000000 + 0xE7000)
#define FLASH_SIZE_NUM_16_0                   450
#define FLASH_ADDR_NUM_16_1                   (0x00000000 + 0xE7302)
#define FLASH_SIZE_NUM_16_1                   322
#define FLASH_ADDR_NUM_16_2                   (0x00000000 + 0xE7604)
#define FLASH_SIZE_NUM_16_2                   450
#define FLASH_ADDR_NUM_16_3                   (0x00000000 + 0xE7906)
#define FLASH_SIZE_NUM_16_3                   450
#define FLASH_ADDR_NUM_16_4                   (0x00000000 + 0xE7C08)
#define FLASH_SIZE_NUM_16_4                   450
#define FLASH_ADDR_NUM_16_5                   (0x00000000 + 0xE7F0A)
#define FLASH_SIZE_NUM_16_5                   450
#define FLASH_ADDR_NUM_16_6                   (0x00000000 + 0xE820C)
#define FLASH_SIZE_NUM_16_6                   450
#define FLASH_ADDR_NUM_16_7                   (0x00000000 + 0xE850E)
#define FLASH_SIZE_NUM_16_7                   450
#define FLASH_ADDR_NUM_16_8                   (0x00000000 + 0xE8810)
#define FLASH_SIZE_NUM_16_8                   450
#define FLASH_ADDR_NUM_16_9                   (0x00000000 + 0xE8B12)
#define FLASH_SIZE_NUM_16_9                   450
#define FLASH_ADDR_NUM_16                     (0x00000000 + 0xE8E14)
#define FLASH_SIZE_NUM_16                     322
#define FLASH_ADDR_NUM_16_A                   (0x00000000 + 0xE9116)
#define FLASH_SIZE_NUM_16_A                   514
#define FLASH_ADDR_NUM_16_B                   (0x00000000 + 0xE9418)
#define FLASH_SIZE_NUM_16_B                   450
#define FLASH_ADDR_NUM_16_C                   (0x00000000 + 0xE971A)
#define FLASH_SIZE_NUM_16_C                   514
#define FLASH_ADDR_NUM_16_D                   (0x00000000 + 0xE9A1C)
#define FLASH_SIZE_NUM_16_D                   514
#define FLASH_ADDR_NUM_16_E                   (0x00000000 + 0xE9D1E)
#define FLASH_SIZE_NUM_16_E                   386
#define FLASH_ADDR_NUM_16_F                   (0x00000000 + 0xEA020)
#define FLASH_SIZE_NUM_16_F                   386
#define FLASH_ADDR_NUM_16_G                   (0x00000000 + 0xEA322)
#define FLASH_SIZE_NUM_16_G                   514
#define FLASH_ADDR_NUM_16_H                   (0x00000000 + 0xEA624)
#define FLASH_SIZE_NUM_16_H                   450
#define FLASH_ADDR_NUM_16_I                   (0x00000000 + 0xEA926)
#define FLASH_SIZE_NUM_16_I                   258
#define FLASH_ADDR_NUM_16_J                   (0x00000000 + 0xEAC28)
#define FLASH_SIZE_NUM_16_J                   386
#define FLASH_ADDR_NUM_16_K                   (0x00000000 + 0xEAF2A)
#define FLASH_SIZE_NUM_16_K                   450
#define FLASH_ADDR_NUM_16_L                   (0x00000000 + 0xEB22C)
#define FLASH_SIZE_NUM_16_L                   386
#define FLASH_ADDR_NUM_16_M                   (0x00000000 + 0xEB52E)
#define FLASH_SIZE_NUM_16_M                   578
#define FLASH_ADDR_NUM_16_N                   (0x00000000 + 0xEB830)
#define FLASH_SIZE_NUM_16_N                   450
#define FLASH_ADDR_NUM_16_O                   (0x00000000 + 0xEBB32)
#define FLASH_SIZE_NUM_16_O                   514
#define FLASH_ADDR_NUM_16_P                   (0x00000000 + 0xEBE34)
#define FLASH_SIZE_NUM_16_P                   386
#define FLASH_ADDR_NUM_16_Q                   (0x00000000 + 0xEC136)
#define FLASH_SIZE_NUM_16_Q                   514
#define FLASH_ADDR_NUM_16_R                   (0x00000000 + 0xEC438)
#define FLASH_SIZE_NUM_16_R                   450
#define FLASH_ADDR_NUM_16_S                   (0x00000000 + 0xEC73A)
#define FLASH_SIZE_NUM_16_S                   386
#define FLASH_ADDR_NUM_16_T                   (0x00000000 + 0xECA3C)
#define FLASH_SIZE_NUM_16_T                   450
#define FLASH_ADDR_NUM_16_U                   (0x00000000 + 0xECD3E)
#define FLASH_SIZE_NUM_16_U                   450
#define FLASH_ADDR_NUM_16_V                   (0x00000000 + 0xED040)
#define FLASH_SIZE_NUM_16_V                   514
#define FLASH_ADDR_NUM_16_W                   (0x00000000 + 0xED342)
#define FLASH_SIZE_NUM_16_W                   706
#define FLASH_ADDR_NUM_16_X                   (0x00000000 + 0xED644)
#define FLASH_SIZE_NUM_16_X                   514
#define FLASH_ADDR_NUM_16_Y                   (0x00000000 + 0xED946)
#define FLASH_SIZE_NUM_16_Y                   450
#define FLASH_ADDR_NUM_16_Z                   (0x00000000 + 0xEDC48)
#define FLASH_SIZE_NUM_16_Z                   450
#define FLASH_ADDR_NUM_16_Z_COLON             (0x00000000 + 0xEDF4A)
#define FLASH_SIZE_NUM_16_Z_COLON             258
#define FLASH_ADDR_NUM_16_Z_DEGREE            (0x00000000 + 0xEE24C)
#define FLASH_SIZE_NUM_16_Z_DEGREE            770
#define FLASH_ADDR_NUM_16_Z_DOT               (0x00000000 + 0xEE54E)
#define FLASH_SIZE_NUM_16_Z_DOT               258
#define FLASH_ADDR_NUM_20_0                   (0x00000000 + 0xEF000)
#define FLASH_SIZE_NUM_20_0                   738
#define FLASH_ADDR_NUM_20_1                   (0x00000000 + 0xEF2E2)
#define FLASH_SIZE_NUM_20_1                   738
#define FLASH_ADDR_NUM_20_2                   (0x00000000 + 0xEF5C4)
#define FLASH_SIZE_NUM_20_2                   642
#define FLASH_ADDR_NUM_20_3                   (0x00000000 + 0xEF8A6)
#define FLASH_SIZE_NUM_20_3                   642
#define FLASH_ADDR_NUM_20_4                   (0x00000000 + 0xEFB88)
#define FLASH_SIZE_NUM_20_4                   642
#define FLASH_ADDR_NUM_20_5                   (0x00000000 + 0xEFE6A)
#define FLASH_SIZE_NUM_20_5                   642
#define FLASH_ADDR_NUM_20_6                   (0x00000000 + 0xF014C)
#define FLASH_SIZE_NUM_20_6                   642
#define FLASH_ADDR_NUM_20_7                   (0x00000000 + 0xF042E)
#define FLASH_SIZE_NUM_20_7                   642
#define FLASH_ADDR_NUM_20_8                   (0x00000000 + 0xF0710)
#define FLASH_SIZE_NUM_20_8                   642
#define FLASH_ADDR_NUM_20_9                   (0x00000000 + 0xF09F2)
#define FLASH_SIZE_NUM_20_9                   642
#define FLASH_ADDR_NUM_20_COLON               (0x00000000 + 0xF1000)
#define FLASH_SIZE_NUM_20_COLON               450
#define FLASH_ADDR_NUM_40_0                   (0x00000000 + 0xF2000)
#define FLASH_SIZE_NUM_40_0                   1986
#define FLASH_ADDR_NUM_40_1                   (0x00000000 + 0xF27C2)
#define FLASH_SIZE_NUM_40_1                   1346
#define FLASH_ADDR_NUM_40_2                   (0x00000000 + 0xF2F84)
#define FLASH_SIZE_NUM_40_2                   1986
#define FLASH_ADDR_NUM_40_3                   (0x00000000 + 0xF3746)
#define FLASH_SIZE_NUM_40_3                   1986
#define FLASH_ADDR_NUM_40_4                   (0x00000000 + 0xF3F08)
#define FLASH_SIZE_NUM_40_4                   1986
#define FLASH_ADDR_NUM_40_5                   (0x00000000 + 0xF46CA)
#define FLASH_SIZE_NUM_40_5                   1986
#define FLASH_ADDR_NUM_40_6                   (0x00000000 + 0xF4E8C)
#define FLASH_SIZE_NUM_40_6                   1986
#define FLASH_ADDR_NUM_40_7                   (0x00000000 + 0xF564E)
#define FLASH_SIZE_NUM_40_7                   1986
#define FLASH_ADDR_NUM_40_8                   (0x00000000 + 0xF5E10)
#define FLASH_SIZE_NUM_40_8                   1986
#define FLASH_ADDR_NUM_40_9                   (0x00000000 + 0xF65D2)
#define FLASH_SIZE_NUM_40_9                   1986
#define FLASH_ADDR_NUM_40                     (0x00000000 + 0xF6D94)
#define FLASH_SIZE_NUM_40                     1346
#define FLASH_ADDR_NUM_40_DEGREE              (0x00000000 + 0xF8000)
#define FLASH_SIZE_NUM_40_DEGREE              1346
#define FLASH_ADDR_NUM_40_PERCENT             (0x00000000 + 0xF9000)
#define FLASH_SIZE_NUM_40_PERCENT             1346
#define FLASH_ADDR_ORANGE_CHARGING_001        (0x00000000 + 0xFA000)
#define FLASH_SIZE_ORANGE_CHARGING_001        8490
#define FLASH_ADDR_ORANGE_CHARGING_002        (0x00000000 + 0xFD000)
#define FLASH_SIZE_ORANGE_CHARGING_002        8490
#define FLASH_ADDR_ORANGE_CHARGING_003        (0x00000000 + 0x100000)
#define FLASH_SIZE_ORANGE_CHARGING_003        8490
#define FLASH_ADDR_ORANGE_CHARGING_004        (0x00000000 + 0x103000)
#define FLASH_SIZE_ORANGE_CHARGING_004        8490
#define FLASH_ADDR_ORANGE_CHARGING_005        (0x00000000 + 0x106000)
#define FLASH_SIZE_ORANGE_CHARGING_005        8490
#define FLASH_ADDR_ORANGE_CHARGING_006        (0x00000000 + 0x109000)
#define FLASH_SIZE_ORANGE_CHARGING_006        8490
#define FLASH_ADDR_ORANGE_CHARGING_007        (0x00000000 + 0x10C000)
#define FLASH_SIZE_ORANGE_CHARGING_007        8490
#define FLASH_ADDR_ORANGE_CHARGING_008        (0x00000000 + 0x10F000)
#define FLASH_SIZE_ORANGE_CHARGING_008        8490
#define FLASH_ADDR_ORANGE_CHARGING_009        (0x00000000 + 0x112000)
#define FLASH_SIZE_ORANGE_CHARGING_009        8490
#define FLASH_ADDR_ORANGE_CHARGING_010        (0x00000000 + 0x115000)
#define FLASH_SIZE_ORANGE_CHARGING_010        8490
#define FLASH_ADDR_ORANGE_CHARGING_011        (0x00000000 + 0x118000)
#define FLASH_SIZE_ORANGE_CHARGING_011        8490
#define FLASH_ADDR_ORANGE_CHARGING_012        (0x00000000 + 0x11B000)
#define FLASH_SIZE_ORANGE_CHARGING_012        8490
#define FLASH_ADDR_ORANGE_CHARGING_013        (0x00000000 + 0x11E000)
#define FLASH_SIZE_ORANGE_CHARGING_013        8490
#define FLASH_ADDR_ORANGE_CHARGING_014        (0x00000000 + 0x121000)
#define FLASH_SIZE_ORANGE_CHARGING_014        8490
#define FLASH_ADDR_ORANGE_CHARGING_015        (0x00000000 + 0x124000)
#define FLASH_SIZE_ORANGE_CHARGING_015        8490
#define FLASH_ADDR_ORANGE_CHARGING_016        (0x00000000 + 0x127000)
#define FLASH_SIZE_ORANGE_CHARGING_016        8490
#define FLASH_ADDR_ORANGE_CHARGING_017        (0x00000000 + 0x12A000)
#define FLASH_SIZE_ORANGE_CHARGING_017        8490
#define FLASH_ADDR_ORANGE_CHARGING_018        (0x00000000 + 0x12D000)
#define FLASH_SIZE_ORANGE_CHARGING_018        8490
#define FLASH_ADDR_ORANGE_CHARGING_019        (0x00000000 + 0x130000)
#define FLASH_SIZE_ORANGE_CHARGING_019        8490
#define FLASH_ADDR_ORANGE_CHARGING_020        (0x00000000 + 0x133000)
#define FLASH_SIZE_ORANGE_CHARGING_020        8490
#define FLASH_ADDR_ORANGE_CHARGING_021        (0x00000000 + 0x136000)
#define FLASH_SIZE_ORANGE_CHARGING_021        8490
#define FLASH_ADDR_ORANGE_CHARGING_022        (0x00000000 + 0x139000)
#define FLASH_SIZE_ORANGE_CHARGING_022        8490
#define FLASH_ADDR_ORANGE_CHARGING_023        (0x00000000 + 0x13C000)
#define FLASH_SIZE_ORANGE_CHARGING_023        8490
#define FLASH_ADDR_ORANGE_CHARGING_024        (0x00000000 + 0x13F000)
#define FLASH_SIZE_ORANGE_CHARGING_024        8490
#define FLASH_ADDR_ORANGE_CHARGING_025        (0x00000000 + 0x142000)
#define FLASH_SIZE_ORANGE_CHARGING_025        8490
#define FLASH_ADDR_ORANGE_CHARGING_026        (0x00000000 + 0x145000)
#define FLASH_SIZE_ORANGE_CHARGING_026        8490
#define FLASH_ADDR_ORANGE_CHARGING_027        (0x00000000 + 0x148000)
#define FLASH_SIZE_ORANGE_CHARGING_027        8490
#define FLASH_ADDR_ORANGE_CHARGING_028        (0x00000000 + 0x14B000)
#define FLASH_SIZE_ORANGE_CHARGING_028        8490
#define FLASH_ADDR_ORANGE_CHARGING_029        (0x00000000 + 0x14E000)
#define FLASH_SIZE_ORANGE_CHARGING_029        8490
#define FLASH_ADDR_ORANGE_CHARGING_030        (0x00000000 + 0x151000)
#define FLASH_SIZE_ORANGE_CHARGING_030        8490
#define FLASH_ADDR_ORANGE_CHARGING_031        (0x00000000 + 0x154000)
#define FLASH_SIZE_ORANGE_CHARGING_031        8490
#define FLASH_ADDR_ORANGE_CHARGING_032        (0x00000000 + 0x157000)
#define FLASH_SIZE_ORANGE_CHARGING_032        8490
#define FLASH_ADDR_ORANGE_CHARGING_033        (0x00000000 + 0x15A000)
#define FLASH_SIZE_ORANGE_CHARGING_033        8490
#define FLASH_ADDR_ORANGE_CHARGING_034        (0x00000000 + 0x15D000)
#define FLASH_SIZE_ORANGE_CHARGING_034        8490
#define FLASH_ADDR_ORANGE_CHARGING_035        (0x00000000 + 0x160000)
#define FLASH_SIZE_ORANGE_CHARGING_035        8490
#define FLASH_ADDR_ORANGE_CHARGING_036        (0x00000000 + 0x163000)
#define FLASH_SIZE_ORANGE_CHARGING_036        8490
#define FLASH_ADDR_ORANGE_CHARGING_037        (0x00000000 + 0x166000)
#define FLASH_SIZE_ORANGE_CHARGING_037        8490
#define FLASH_ADDR_ORANGE_CHARGING_038        (0x00000000 + 0x169000)
#define FLASH_SIZE_ORANGE_CHARGING_038        8490
#define FLASH_ADDR_ORANGE_CHARGING_039        (0x00000000 + 0x16C000)
#define FLASH_SIZE_ORANGE_CHARGING_039        8490
#define FLASH_ADDR_ORANGE_CHARGING_040        (0x00000000 + 0x16F000)
#define FLASH_SIZE_ORANGE_CHARGING_040        8490
#define FLASH_ADDR_OUT                        (0x00000000 + 0x172000)
#define FLASH_SIZE_OUT                        2178
#define FLASH_ADDR_POWER_PART_1_USB_A_BLUE    (0x00000000 + 0x173000)
#define FLASH_SIZE_POWER_PART_1_USB_A_BLUE    5286
#define FLASH_ADDR_POWER_PART_1_USB_A_WHITE   (0x00000000 + 0x175000)
#define FLASH_SIZE_POWER_PART_1_USB_A_WHITE   5286
#define FLASH_ADDR_POWER_PART_1_USB_C_BLUE    (0x00000000 + 0x177000)
#define FLASH_SIZE_POWER_PART_1_USB_C_BLUE    5286
#define FLASH_ADDR_POWER_PART_1_USB_C_WHITE   (0x00000000 + 0x179000)
#define FLASH_SIZE_POWER_PART_1_USB_C_WHITE   5286
#define FLASH_ADDR_POWER_PART_2_PORT_1_BLUE   (0x00000000 + 0x17B000)
#define FLASH_SIZE_POWER_PART_2_PORT_1_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_1_WHITE  (0x00000000 + 0x17C000)
#define FLASH_SIZE_POWER_PART_2_PORT_1_WHITE  1506
#define FLASH_ADDR_POWER_PART_2_PORT_2_BLUE   (0x00000000 + 0x17D000)
#define FLASH_SIZE_POWER_PART_2_PORT_2_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_2_WHITE  (0x00000000 + 0x17E000)
#define FLASH_SIZE_POWER_PART_2_PORT_2_WHITE  1506
#define FLASH_ADDR_POWER_PART_2_PORT_3_BLUE   (0x00000000 + 0x17F000)
#define FLASH_SIZE_POWER_PART_2_PORT_3_BLUE   1506
#define FLASH_ADDR_POWER_PART_2_PORT_3_WHITE  (0x00000000 + 0x180000)
#define FLASH_SIZE_POWER_PART_2_PORT_3_WHITE  1506
#define FLASH_ADDR_POWER_PART_3_IN_BLUE       (0x00000000 + 0x181000)
#define FLASH_SIZE_POWER_PART_3_IN_BLUE       6366
#define FLASH_ADDR_POWER_PART_3_OUT_BLUE      (0x00000000 + 0x183000)
#define FLASH_SIZE_POWER_PART_3_OUT_BLUE      6366
#define FLASH_ADDR_POWER_PART_3_WHITE         (0x00000000 + 0x185000)
#define FLASH_SIZE_POWER_PART_3_WHITE         6366
#define FLASH_ADDR_POWER_PART_4_0_BLUE        (0x00000000 + 0x187000)
#define FLASH_SIZE_POWER_PART_4_0_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_0_WHITE       (0x00000000 + 0x188000)
#define FLASH_SIZE_POWER_PART_4_0_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_1_BLUE        (0x00000000 + 0x189000)
#define FLASH_SIZE_POWER_PART_4_1_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_1_WHITE       (0x00000000 + 0x18A000)
#define FLASH_SIZE_POWER_PART_4_1_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_2_BLUE        (0x00000000 + 0x18B000)
#define FLASH_SIZE_POWER_PART_4_2_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_2_WHITE       (0x00000000 + 0x18C000)
#define FLASH_SIZE_POWER_PART_4_2_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_3_BLUE        (0x00000000 + 0x18D000)
#define FLASH_SIZE_POWER_PART_4_3_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_3_WHITE       (0x00000000 + 0x18E000)
#define FLASH_SIZE_POWER_PART_4_3_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_4_BLUE        (0x00000000 + 0x18F000)
#define FLASH_SIZE_POWER_PART_4_4_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_4_WHITE       (0x00000000 + 0x190000)
#define FLASH_SIZE_POWER_PART_4_4_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_5_BLUE        (0x00000000 + 0x191000)
#define FLASH_SIZE_POWER_PART_4_5_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_5_WHITE       (0x00000000 + 0x192000)
#define FLASH_SIZE_POWER_PART_4_5_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_6_BLUE        (0x00000000 + 0x193000)
#define FLASH_SIZE_POWER_PART_4_6_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_6_WHITE       (0x00000000 + 0x194000)
#define FLASH_SIZE_POWER_PART_4_6_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_7_BLUE        (0x00000000 + 0x195000)
#define FLASH_SIZE_POWER_PART_4_7_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_7_WHITE       (0x00000000 + 0x196000)
#define FLASH_SIZE_POWER_PART_4_7_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_8_BLUE        (0x00000000 + 0x197000)
#define FLASH_SIZE_POWER_PART_4_8_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_8_WHITE       (0x00000000 + 0x198000)
#define FLASH_SIZE_POWER_PART_4_8_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_9_BLUE        (0x00000000 + 0x199000)
#define FLASH_SIZE_POWER_PART_4_9_BLUE        1866
#define FLASH_ADDR_POWER_PART_4_9_WHITE       (0x00000000 + 0x19A000)
#define FLASH_SIZE_POWER_PART_4_9_WHITE       1866
#define FLASH_ADDR_POWER_PART_4_BLUE          (0x00000000 + 0x19B000)
#define FLASH_SIZE_POWER_PART_4_BLUE          1866
#define FLASH_ADDR_POWER_PART_4_WHITE         (0x00000000 + 0x19C000)
#define FLASH_SIZE_POWER_PART_4_WHITE         1866
#define FLASH_ADDR_POWER_PART_5_BLUE          (0x00000000 + 0x19D000)
#define FLASH_SIZE_POWER_PART_5_BLUE          3486
#define FLASH_ADDR_POWER_PART_5_WHITE         (0x00000000 + 0x19E000)
#define FLASH_SIZE_POWER_PART_5_WHITE         3486
#define FLASH_ADDR_RIGHT_1_ORANGE             (0x00000000 + 0x19F000)
#define FLASH_SIZE_RIGHT_1_ORANGE             11586
#define FLASH_ADDR_RIGHT_2_BLUE               (0x00000000 + 0x1A2000)
#define FLASH_SIZE_RIGHT_2_BLUE               8994
#define FLASH_ADDR_RIGHT_2_ORANGE             (0x00000000 + 0x1A5000)
#define FLASH_SIZE_RIGHT_2_ORANGE             8994
#define FLASH_ADDR_RIGHT_3_BLUE               (0x00000000 + 0x1A8000)
#define FLASH_SIZE_RIGHT_3_BLUE               6402
#define FLASH_ADDR_SAFE                       (0x00000000 + 0x1AA000)
#define FLASH_SIZE_SAFE                       12866
#define FLASH_ADDR_SAFEGUARD                  (0x00000000 + 0x1AE000)
#define FLASH_SIZE_SAFEGUARD                  26466
#define FLASH_ADDR_TEMP_ABNORMAL              (0x00000000 + 0x1B5000)
#define FLASH_SIZE_TEMP_ABNORMAL              15426
#define FLASH_ADDR_TEMP_ORANGE                (0x00000000 + 0x1B9000)
#define FLASH_SIZE_TEMP_ORANGE                12866
#define FLASH_ADDR_TEMPERATURE_RECOVERY       (0x00000000 + 0x1BD000)
#define FLASH_SIZE_TEMPERATURE_RECOVERY       9186
#define FLASH_ADDR_TIAO                       (0x00000000 + 0x1C0000)
#define FLASH_SIZE_TIAO                       678
#define FLASH_ADDR_TIMER                      (0x00000000 + 0x1C1000)
#define FLASH_SIZE_TIMER                      1026
#define FLASH_ADDR_TOTAL_VOLTAGE              (0x00000000 + 0x1C2000)
#define FLASH_SIZE_TOTAL_VOLTAGE              1986
#define FLASH_ADDR_VOLTAGE_ABNORMAL           (0x00000000 + 0x1C3000)
#define FLASH_SIZE_VOLTAGE_ABNORMAL           15426

#endif /* __FLASH_IMAGE_ADDR_H__ */
