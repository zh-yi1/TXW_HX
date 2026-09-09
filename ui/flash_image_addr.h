/*
 * flash_image_addr.h — Auto-generated, do not edit.
 *
 * P25Q64SH Flash Image Address Map (64 Mb = 8 MB)
 * Sector size: 4096 bytes (4 KB)
 *
 * Images:       249
 * Categories:   108
 * Flash used:   2167466 bytes (2116.7 KB)
 * Sectors used: 530 / 2048
 * Capacity:     8192 KB (8 MB)
 *
 * Category layout:
 *   AMPERE                               base=0x000000  stride=682    count=1     sectors=[0]
 *   AMPERE_DARK                          base=0x001000  stride=682    count=1     sectors=[1]
 *   BTN_1800S                            base=0x002000  stride=6338   count=1     sectors=[2 – 3]
 *   BTN_1800S_DARK                       base=0x004000  stride=6338   count=1     sectors=[4 – 5]
 *   BTN_300S                             base=0x006000  stride=6338   count=1     sectors=[6 – 7]
 *   BTN_300S_DARK                        base=0x008000  stride=6338   count=1     sectors=[8 – 9]
 *   BTN_30S                              base=0x00A000  stride=6338   count=1     sectors=[10 – 11]
 *   BTN_30S_DARK                         base=0x00C000  stride=6338   count=1     sectors=[12 – 13]
 *   BTN_60S                              base=0x00E000  stride=6338   count=1     sectors=[14 – 15]
 *   BTN_60S_DARK                         base=0x010000  stride=6338   count=1     sectors=[16 – 17]
 *   CELL_MODEL                           base=0x012000  stride=2562   count=1     sectors=[18]
 *   CI                                   base=0x013000  stride=858    count=1     sectors=[19]
 *   DEGREE_CENTIGRADE                    base=0x014000  stride=1122   count=1     sectors=[20]
 *   DI                                   base=0x015000  stride=678    count=1     sectors=[21]
 *   DOUBLE_CLICK_SWITCH                  base=0x016000  stride=9186   count=1     sectors=[22 – 24]
 *   DOUHAO                               base=0x019000  stride=450    count=1     sectors=[25]
 *   EMOJI_CHARGING                       base=0x01A000  stride=25826  count=1     sectors=[26 – 32]
 *   EMOJI_HEALTHY                        base=0x021000  stride=25826  count=1     sectors=[33 – 39]
 *   EMOJI_LOW_POWER                      base=0x028000  stride=25826  count=1     sectors=[40 – 46]
 *   EMOJI_NORMAL                         base=0x02F000  stride=25826  count=1     sectors=[47 – 53]
 *   GONG                                 base=0x036000  stride=678    count=1     sectors=[54]
 *   HIGH_POWER_CHARGING_ANIMA            base=0x037000  stride=25826  count=12    sectors=[55 – 130]
 *   HIGH_POWER_STANDBY_ANIMA             base=0x083000  stride=25826  count=12    sectors=[131 – 206]
 *   ICON_COUNT_DOWN                      base=0x0CF000  stride=866    count=1     sectors=[207]
 *   ICON_IN_1_BIG                        base=0x0D0000  stride=8226   count=1     sectors=[208 – 210]
 *   ICON_IN_1_LITTLE                     base=0x0D3000  stride=2706   count=1     sectors=[211]
 *   ICON_IN_2_BIG                        base=0x0D4000  stride=8226   count=1     sectors=[212 – 214]
 *   ICON_IN_2_LITTLE                     base=0x0D7000  stride=2706   count=1     sectors=[215]
 *   ICON_IN_3_BIG                        base=0x0D8000  stride=8226   count=1     sectors=[216 – 218]
 *   ICON_IN_3_LITTLE                     base=0x0DB000  stride=2706   count=1     sectors=[219]
 *   ICON_NORMAL_1_BIG                    base=0x0DC000  stride=8226   count=1     sectors=[220 – 222]
 *   ICON_NORMAL_2_BIG                    base=0x0DF000  stride=8226   count=1     sectors=[223 – 225]
 *   ICON_NORMAL_3_BIG                    base=0x0E2000  stride=8226   count=1     sectors=[226 – 228]
 *   ICON_OUT_1_BIG                       base=0x0E5000  stride=8226   count=1     sectors=[229 – 231]
 *   ICON_OUT_1_LITTLE                    base=0x0E8000  stride=2706   count=1     sectors=[232]
 *   ICON_OUT_2_BIG                       base=0x0E9000  stride=8226   count=1     sectors=[233 – 235]
 *   ICON_OUT_2_LITTLE                    base=0x0EC000  stride=2706   count=1     sectors=[236]
 *   ICON_OUT_3_BIG                       base=0x0ED000  stride=8226   count=1     sectors=[237 – 239]
 *   ICON_OUT_3_LITTLE                    base=0x0F0000  stride=2706   count=1     sectors=[240]
 *   ICON_PROTECTION                      base=0x0F1000  stride=12866  count=1     sectors=[241 – 244]
 *   ICON_SAFE                            base=0x0F5000  stride=12866  count=1     sectors=[245 – 248]
 *   ICON_TEMP_HIGH                       base=0x0F9000  stride=12866  count=1     sectors=[249 – 252]
 *   LOW_POWER_CHARGING_ANIMA             base=0x0FD000  stride=25826  count=12    sectors=[253 – 328]
 *   LOW_POWER_STANDBY_ANIMA              base=0x149000  stride=25826  count=12    sectors=[329 – 404]
 *   NUM_12                               base=0x195000  stride=346    count=40    sectors=[405 – 408]
 *   NUM_16                               base=0x199000  stride=770    count=40    sectors=[409 – 416]
 *   NUM_18                               base=0x1A1000  stride=570    count=10    sectors=[417 – 418]
 *   NUM_18_HOUR                          base=0x1A3000  stride=570    count=1     sectors=[419]
 *   NUM_18_MINUTE                        base=0x1A4000  stride=906    count=1     sectors=[420]
 *   NUM_20                               base=0x1A5000  stride=594    count=10    sectors=[421 – 422]
 *   NUM_20_1_NULL                        base=0x1A7000  stride=594    count=1     sectors=[423]
 *   NUM_20_1                             base=0x1A8000  stride=594    count=1     sectors=[424]
 *   NUM_48_0_ORANGE                      base=0x1A9000  stride=3330   count=1     sectors=[425]
 *   NUM_48_0_WHITE                       base=0x1AA000  stride=3330   count=1     sectors=[426]
 *   NUM_48_1_ORANGE                      base=0x1AB000  stride=2178   count=1     sectors=[427]
 *   NUM_48_1_WHITE                       base=0x1AC000  stride=2178   count=1     sectors=[428]
 *   NUM_48_2_ORANGE                      base=0x1AD000  stride=3330   count=1     sectors=[429]
 *   NUM_48_2_WHITE                       base=0x1AE000  stride=3330   count=1     sectors=[430]
 *   NUM_48_3_ORANGE                      base=0x1AF000  stride=3330   count=1     sectors=[431]
 *   NUM_48_3_WHITE                       base=0x1B0000  stride=3330   count=1     sectors=[432]
 *   NUM_48_4_ORANGE                      base=0x1B1000  stride=3330   count=1     sectors=[433]
 *   NUM_48_4_WHITE                       base=0x1B2000  stride=3330   count=1     sectors=[434]
 *   NUM_48_5_ORANGE                      base=0x1B3000  stride=3330   count=1     sectors=[435]
 *   NUM_48_5_WHITE                       base=0x1B4000  stride=3330   count=1     sectors=[436]
 *   NUM_48_6_ORANGE                      base=0x1B5000  stride=3330   count=1     sectors=[437]
 *   NUM_48_6_WHITE                       base=0x1B6000  stride=3330   count=1     sectors=[438]
 *   NUM_48_7_ORANGE                      base=0x1B7000  stride=3330   count=1     sectors=[439]
 *   NUM_48_7_WHITE                       base=0x1B8000  stride=3330   count=1     sectors=[440]
 *   NUM_48_8_ORANGE                      base=0x1B9000  stride=3330   count=1     sectors=[441]
 *   NUM_48_8_WHITE                       base=0x1BA000  stride=3330   count=1     sectors=[442]
 *   NUM_48_9_ORANGE                      base=0x1BB000  stride=3330   count=1     sectors=[443]
 *   NUM_48_9_WHITE                       base=0x1BC000  stride=3330   count=1     sectors=[444]
 *   NUM_48_PERCENT_ORANGE                base=0x1BD000  stride=3330   count=1     sectors=[445]
 *   NUM_48_PERCENT_WHITE                 base=0x1BE000  stride=3330   count=1     sectors=[446]
 *   OBLIQUE_LINE                         base=0x1BF000  stride=770    count=1     sectors=[447]
 *   OBLIQUE_LINE_DARK                    base=0x1C0000  stride=770    count=1     sectors=[448]
 *   PERCENT                              base=0x1C1000  stride=682    count=1     sectors=[449]
 *   POINT                                base=0x1C2000  stride=330    count=1     sectors=[450]
 *   STRIGULA_THREE_DARK                  base=0x1C3000  stride=1738   count=1     sectors=[451]
 *   STRIGULA_TWO_DARK                    base=0x1C4000  stride=1386   count=1     sectors=[452]
 *   TEMP_DROPS_TO_NORMAL                 base=0x1C5000  stride=9186   count=1     sectors=[453 – 455]
 *   TEXT_BAT_HEALTH                      base=0x1C8000  stride=4626   count=1     sectors=[456 – 457]
 *   TEXT_BAT_TEMP                        base=0x1CA000  stride=4626   count=1     sectors=[458 – 459]
 *   TEXT_CHARGING_HIGH_TEMP              base=0x1CC000  stride=17346  count=1     sectors=[460 – 464]
 *   TEXT_CHARGING_TEMP                   base=0x1D1000  stride=2718   count=1     sectors=[465]
 *   TEXT_CYCLE_INDEX                     base=0x1D2000  stride=4626   count=1     sectors=[466 – 467]
 *   TEXT_DISCHARGING_HIGH_TEMP           base=0x1D4000  stride=17346  count=1     sectors=[468 – 472]
 *   TEXT_DISCHARGING_TEMP                base=0x1D9000  stride=2718   count=1     sectors=[473]
 *   TEXT_LOW_POWER                       base=0x1DA000  stride=5258   count=1     sectors=[474 – 475]
 *   TEXT_MINI                            base=0x1DC000  stride=2466   count=1     sectors=[476]
 *   TEXT_NO_ABNORMAL_RECORDS             base=0x1DD000  stride=5026   count=1     sectors=[477 – 478]
 *   TEXT_PRESS_5S_TO_SETTING             base=0x1DF000  stride=5954   count=1     sectors=[479 – 480]
 *   TEXT_PROTECTION                      base=0x1E1000  stride=17346  count=2     sectors=[481 – 489]
 *   TEXT_SAFEGUARD                       base=0x1EA000  stride=26466  count=1     sectors=[490 – 496]
 *   TEXT_STANDING_HIGH_TEMP              base=0x1F1000  stride=17346  count=1     sectors=[497 – 501]
 *   TEXT_STANDING_TEMP                   base=0x1F6000  stride=2718   count=1     sectors=[502]
 *   TEXT_TIME                            base=0x1F7000  stride=1474   count=1     sectors=[503]
 *   TEXT_VERSION_NUMBER                  base=0x1F8000  stride=1902   count=1     sectors=[504]
 *   TEXT_VOLTAGE                         base=0x1F9000  stride=1474   count=1     sectors=[505]
 *   TEXTTOTAL_VOLTAGE                    base=0x1FA000  stride=1986   count=1     sectors=[506]
 *   TIAO                                 base=0x1FB000  stride=678    count=1     sectors=[507]
 *   TITLE_ABNORMAL_TEMP                  base=0x1FC000  stride=15426  count=1     sectors=[508 – 511]
 *   TITLE_ABNORMAL_VOLTAGE               base=0x200000  stride=15426  count=1     sectors=[512 – 515]
 *   TITLE_CELL_VOLTAGE                   base=0x204000  stride=15426  count=1     sectors=[516 – 519]
 *   TITLE_SCREEN_OFF_DURATION            base=0x208000  stride=15426  count=1     sectors=[520 – 523]
 *   TITLE_SOFTWARE_VERSION               base=0x20C000  stride=15426  count=1     sectors=[524 – 527]
 *   VOLT                                 base=0x210000  stride=682    count=1     sectors=[528]
 *   VOLT_DARK                            base=0x211000  stride=682    count=1     sectors=[529]
 */

#ifndef __FLASH_IMAGE_ADDR_H__
#define __FLASH_IMAGE_ADDR_H__

/*
 * Category base addresses — access images via:
 *   addr = FLASH_ADDR_<CAT>_BASE + index * FLASH_STRIDE_<CAT>
 */
#define FLASH_ADDR_AMPERE_BASE    (0x00000000 + 0x0000)
#define FLASH_STRIDE_AMPERE       682
#define FLASH_COUNT_AMPERE        1

#define FLASH_ADDR_AMPERE_DARK_BASE    (0x00000000 + 0x1000)
#define FLASH_STRIDE_AMPERE_DARK       682
#define FLASH_COUNT_AMPERE_DARK        1

#define FLASH_ADDR_BTN_1800S_BASE    (0x00000000 + 0x2000)
#define FLASH_STRIDE_BTN_1800S       6338
#define FLASH_COUNT_BTN_1800S        1

#define FLASH_ADDR_BTN_1800S_DARK_BASE    (0x00000000 + 0x4000)
#define FLASH_STRIDE_BTN_1800S_DARK       6338
#define FLASH_COUNT_BTN_1800S_DARK        1

#define FLASH_ADDR_BTN_300S_BASE    (0x00000000 + 0x6000)
#define FLASH_STRIDE_BTN_300S       6338
#define FLASH_COUNT_BTN_300S        1

#define FLASH_ADDR_BTN_300S_DARK_BASE    (0x00000000 + 0x8000)
#define FLASH_STRIDE_BTN_300S_DARK       6338
#define FLASH_COUNT_BTN_300S_DARK        1

#define FLASH_ADDR_BTN_30S_BASE    (0x00000000 + 0xA000)
#define FLASH_STRIDE_BTN_30S       6338
#define FLASH_COUNT_BTN_30S        1

#define FLASH_ADDR_BTN_30S_DARK_BASE    (0x00000000 + 0xC000)
#define FLASH_STRIDE_BTN_30S_DARK       6338
#define FLASH_COUNT_BTN_30S_DARK        1

#define FLASH_ADDR_BTN_60S_BASE    (0x00000000 + 0xE000)
#define FLASH_STRIDE_BTN_60S       6338
#define FLASH_COUNT_BTN_60S        1

#define FLASH_ADDR_BTN_60S_DARK_BASE    (0x00000000 + 0x10000)
#define FLASH_STRIDE_BTN_60S_DARK       6338
#define FLASH_COUNT_BTN_60S_DARK        1

#define FLASH_ADDR_CELL_MODEL_BASE    (0x00000000 + 0x12000)
#define FLASH_STRIDE_CELL_MODEL       2562
#define FLASH_COUNT_CELL_MODEL        1

#define FLASH_ADDR_CI_BASE    (0x00000000 + 0x13000)
#define FLASH_STRIDE_CI       858
#define FLASH_COUNT_CI        1

#define FLASH_ADDR_DEGREE_CENTIGRADE_BASE    (0x00000000 + 0x14000)
#define FLASH_STRIDE_DEGREE_CENTIGRADE       1122
#define FLASH_COUNT_DEGREE_CENTIGRADE        1

#define FLASH_ADDR_DI_BASE    (0x00000000 + 0x15000)
#define FLASH_STRIDE_DI       678
#define FLASH_COUNT_DI        1

#define FLASH_ADDR_DOUBLE_CLICK_SWITCH_BASE    (0x00000000 + 0x16000)
#define FLASH_STRIDE_DOUBLE_CLICK_SWITCH       9186
#define FLASH_COUNT_DOUBLE_CLICK_SWITCH        1

#define FLASH_ADDR_DOUHAO_BASE    (0x00000000 + 0x19000)
#define FLASH_STRIDE_DOUHAO       450
#define FLASH_COUNT_DOUHAO        1

#define FLASH_ADDR_EMOJI_CHARGING_BASE    (0x00000000 + 0x1A000)
#define FLASH_STRIDE_EMOJI_CHARGING       25826
#define FLASH_COUNT_EMOJI_CHARGING        1

#define FLASH_ADDR_EMOJI_HEALTHY_BASE    (0x00000000 + 0x21000)
#define FLASH_STRIDE_EMOJI_HEALTHY       25826
#define FLASH_COUNT_EMOJI_HEALTHY        1

#define FLASH_ADDR_EMOJI_LOW_POWER_BASE    (0x00000000 + 0x28000)
#define FLASH_STRIDE_EMOJI_LOW_POWER       25826
#define FLASH_COUNT_EMOJI_LOW_POWER        1

#define FLASH_ADDR_EMOJI_NORMAL_BASE    (0x00000000 + 0x2F000)
#define FLASH_STRIDE_EMOJI_NORMAL       25826
#define FLASH_COUNT_EMOJI_NORMAL        1

#define FLASH_ADDR_GONG_BASE    (0x00000000 + 0x36000)
#define FLASH_STRIDE_GONG       678
#define FLASH_COUNT_GONG        1

#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_BASE    (0x00000000 + 0x37000)
#define FLASH_STRIDE_HIGH_POWER_CHARGING_ANIMA       25826
#define FLASH_COUNT_HIGH_POWER_CHARGING_ANIMA        12

#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_BASE    (0x00000000 + 0x83000)
#define FLASH_STRIDE_HIGH_POWER_STANDBY_ANIMA       25826
#define FLASH_COUNT_HIGH_POWER_STANDBY_ANIMA        12

#define FLASH_ADDR_ICON_COUNT_DOWN_BASE    (0x00000000 + 0xCF000)
#define FLASH_STRIDE_ICON_COUNT_DOWN       866
#define FLASH_COUNT_ICON_COUNT_DOWN        1

#define FLASH_ADDR_ICON_IN_1_BIG_BASE    (0x00000000 + 0xD0000)
#define FLASH_STRIDE_ICON_IN_1_BIG       8226
#define FLASH_COUNT_ICON_IN_1_BIG        1

#define FLASH_ADDR_ICON_IN_1_LITTLE_BASE    (0x00000000 + 0xD3000)
#define FLASH_STRIDE_ICON_IN_1_LITTLE       2706
#define FLASH_COUNT_ICON_IN_1_LITTLE        1

#define FLASH_ADDR_ICON_IN_2_BIG_BASE    (0x00000000 + 0xD4000)
#define FLASH_STRIDE_ICON_IN_2_BIG       8226
#define FLASH_COUNT_ICON_IN_2_BIG        1

#define FLASH_ADDR_ICON_IN_2_LITTLE_BASE    (0x00000000 + 0xD7000)
#define FLASH_STRIDE_ICON_IN_2_LITTLE       2706
#define FLASH_COUNT_ICON_IN_2_LITTLE        1

#define FLASH_ADDR_ICON_IN_3_BIG_BASE    (0x00000000 + 0xD8000)
#define FLASH_STRIDE_ICON_IN_3_BIG       8226
#define FLASH_COUNT_ICON_IN_3_BIG        1

#define FLASH_ADDR_ICON_IN_3_LITTLE_BASE    (0x00000000 + 0xDB000)
#define FLASH_STRIDE_ICON_IN_3_LITTLE       2706
#define FLASH_COUNT_ICON_IN_3_LITTLE        1

#define FLASH_ADDR_ICON_NORMAL_1_BIG_BASE    (0x00000000 + 0xDC000)
#define FLASH_STRIDE_ICON_NORMAL_1_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_1_BIG        1

#define FLASH_ADDR_ICON_NORMAL_2_BIG_BASE    (0x00000000 + 0xDF000)
#define FLASH_STRIDE_ICON_NORMAL_2_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_2_BIG        1

#define FLASH_ADDR_ICON_NORMAL_3_BIG_BASE    (0x00000000 + 0xE2000)
#define FLASH_STRIDE_ICON_NORMAL_3_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_3_BIG        1

#define FLASH_ADDR_ICON_OUT_1_BIG_BASE    (0x00000000 + 0xE5000)
#define FLASH_STRIDE_ICON_OUT_1_BIG       8226
#define FLASH_COUNT_ICON_OUT_1_BIG        1

#define FLASH_ADDR_ICON_OUT_1_LITTLE_BASE    (0x00000000 + 0xE8000)
#define FLASH_STRIDE_ICON_OUT_1_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_1_LITTLE        1

#define FLASH_ADDR_ICON_OUT_2_BIG_BASE    (0x00000000 + 0xE9000)
#define FLASH_STRIDE_ICON_OUT_2_BIG       8226
#define FLASH_COUNT_ICON_OUT_2_BIG        1

#define FLASH_ADDR_ICON_OUT_2_LITTLE_BASE    (0x00000000 + 0xEC000)
#define FLASH_STRIDE_ICON_OUT_2_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_2_LITTLE        1

#define FLASH_ADDR_ICON_OUT_3_BIG_BASE    (0x00000000 + 0xED000)
#define FLASH_STRIDE_ICON_OUT_3_BIG       8226
#define FLASH_COUNT_ICON_OUT_3_BIG        1

#define FLASH_ADDR_ICON_OUT_3_LITTLE_BASE    (0x00000000 + 0xF0000)
#define FLASH_STRIDE_ICON_OUT_3_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_3_LITTLE        1

#define FLASH_ADDR_ICON_PROTECTION_BASE    (0x00000000 + 0xF1000)
#define FLASH_STRIDE_ICON_PROTECTION       12866
#define FLASH_COUNT_ICON_PROTECTION        1

#define FLASH_ADDR_ICON_SAFE_BASE    (0x00000000 + 0xF5000)
#define FLASH_STRIDE_ICON_SAFE       12866
#define FLASH_COUNT_ICON_SAFE        1

#define FLASH_ADDR_ICON_TEMP_HIGH_BASE    (0x00000000 + 0xF9000)
#define FLASH_STRIDE_ICON_TEMP_HIGH       12866
#define FLASH_COUNT_ICON_TEMP_HIGH        1

#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_BASE    (0x00000000 + 0xFD000)
#define FLASH_STRIDE_LOW_POWER_CHARGING_ANIMA       25826
#define FLASH_COUNT_LOW_POWER_CHARGING_ANIMA        12

#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_BASE    (0x00000000 + 0x149000)
#define FLASH_STRIDE_LOW_POWER_STANDBY_ANIMA       25826
#define FLASH_COUNT_LOW_POWER_STANDBY_ANIMA        12

#define FLASH_ADDR_NUM_12_BASE    (0x00000000 + 0x195000)
#define FLASH_STRIDE_NUM_12       346
#define FLASH_COUNT_NUM_12        40

#define FLASH_ADDR_NUM_16_BASE    (0x00000000 + 0x199000)
#define FLASH_STRIDE_NUM_16       770
#define FLASH_COUNT_NUM_16        40

#define FLASH_ADDR_NUM_18_BASE    (0x00000000 + 0x1A1000)
#define FLASH_STRIDE_NUM_18       570
#define FLASH_COUNT_NUM_18        10

#define FLASH_ADDR_NUM_18_HOUR_BASE    (0x00000000 + 0x1A3000)
#define FLASH_STRIDE_NUM_18_HOUR       570
#define FLASH_COUNT_NUM_18_HOUR        1

#define FLASH_ADDR_NUM_18_MINUTE_BASE    (0x00000000 + 0x1A4000)
#define FLASH_STRIDE_NUM_18_MINUTE       906
#define FLASH_COUNT_NUM_18_MINUTE        1

#define FLASH_ADDR_NUM_20_BASE    (0x00000000 + 0x1A5000)
#define FLASH_STRIDE_NUM_20       594
#define FLASH_COUNT_NUM_20        10

#define FLASH_ADDR_NUM_20_1_NULL_BASE    (0x00000000 + 0x1A7000)
#define FLASH_STRIDE_NUM_20_1_NULL       594
#define FLASH_COUNT_NUM_20_1_NULL        1

#define FLASH_ADDR_NUM_20_1_BASE    (0x00000000 + 0x1A8000)
#define FLASH_STRIDE_NUM_20_1       594
#define FLASH_COUNT_NUM_20_1        1

#define FLASH_ADDR_NUM_48_0_ORANGE_BASE    (0x00000000 + 0x1A9000)
#define FLASH_STRIDE_NUM_48_0_ORANGE       3330
#define FLASH_COUNT_NUM_48_0_ORANGE        1

#define FLASH_ADDR_NUM_48_0_WHITE_BASE    (0x00000000 + 0x1AA000)
#define FLASH_STRIDE_NUM_48_0_WHITE       3330
#define FLASH_COUNT_NUM_48_0_WHITE        1

#define FLASH_ADDR_NUM_48_1_ORANGE_BASE    (0x00000000 + 0x1AB000)
#define FLASH_STRIDE_NUM_48_1_ORANGE       2178
#define FLASH_COUNT_NUM_48_1_ORANGE        1

#define FLASH_ADDR_NUM_48_1_WHITE_BASE    (0x00000000 + 0x1AC000)
#define FLASH_STRIDE_NUM_48_1_WHITE       2178
#define FLASH_COUNT_NUM_48_1_WHITE        1

#define FLASH_ADDR_NUM_48_2_ORANGE_BASE    (0x00000000 + 0x1AD000)
#define FLASH_STRIDE_NUM_48_2_ORANGE       3330
#define FLASH_COUNT_NUM_48_2_ORANGE        1

#define FLASH_ADDR_NUM_48_2_WHITE_BASE    (0x00000000 + 0x1AE000)
#define FLASH_STRIDE_NUM_48_2_WHITE       3330
#define FLASH_COUNT_NUM_48_2_WHITE        1

#define FLASH_ADDR_NUM_48_3_ORANGE_BASE    (0x00000000 + 0x1AF000)
#define FLASH_STRIDE_NUM_48_3_ORANGE       3330
#define FLASH_COUNT_NUM_48_3_ORANGE        1

#define FLASH_ADDR_NUM_48_3_WHITE_BASE    (0x00000000 + 0x1B0000)
#define FLASH_STRIDE_NUM_48_3_WHITE       3330
#define FLASH_COUNT_NUM_48_3_WHITE        1

#define FLASH_ADDR_NUM_48_4_ORANGE_BASE    (0x00000000 + 0x1B1000)
#define FLASH_STRIDE_NUM_48_4_ORANGE       3330
#define FLASH_COUNT_NUM_48_4_ORANGE        1

#define FLASH_ADDR_NUM_48_4_WHITE_BASE    (0x00000000 + 0x1B2000)
#define FLASH_STRIDE_NUM_48_4_WHITE       3330
#define FLASH_COUNT_NUM_48_4_WHITE        1

#define FLASH_ADDR_NUM_48_5_ORANGE_BASE    (0x00000000 + 0x1B3000)
#define FLASH_STRIDE_NUM_48_5_ORANGE       3330
#define FLASH_COUNT_NUM_48_5_ORANGE        1

#define FLASH_ADDR_NUM_48_5_WHITE_BASE    (0x00000000 + 0x1B4000)
#define FLASH_STRIDE_NUM_48_5_WHITE       3330
#define FLASH_COUNT_NUM_48_5_WHITE        1

#define FLASH_ADDR_NUM_48_6_ORANGE_BASE    (0x00000000 + 0x1B5000)
#define FLASH_STRIDE_NUM_48_6_ORANGE       3330
#define FLASH_COUNT_NUM_48_6_ORANGE        1

#define FLASH_ADDR_NUM_48_6_WHITE_BASE    (0x00000000 + 0x1B6000)
#define FLASH_STRIDE_NUM_48_6_WHITE       3330
#define FLASH_COUNT_NUM_48_6_WHITE        1

#define FLASH_ADDR_NUM_48_7_ORANGE_BASE    (0x00000000 + 0x1B7000)
#define FLASH_STRIDE_NUM_48_7_ORANGE       3330
#define FLASH_COUNT_NUM_48_7_ORANGE        1

#define FLASH_ADDR_NUM_48_7_WHITE_BASE    (0x00000000 + 0x1B8000)
#define FLASH_STRIDE_NUM_48_7_WHITE       3330
#define FLASH_COUNT_NUM_48_7_WHITE        1

#define FLASH_ADDR_NUM_48_8_ORANGE_BASE    (0x00000000 + 0x1B9000)
#define FLASH_STRIDE_NUM_48_8_ORANGE       3330
#define FLASH_COUNT_NUM_48_8_ORANGE        1

#define FLASH_ADDR_NUM_48_8_WHITE_BASE    (0x00000000 + 0x1BA000)
#define FLASH_STRIDE_NUM_48_8_WHITE       3330
#define FLASH_COUNT_NUM_48_8_WHITE        1

#define FLASH_ADDR_NUM_48_9_ORANGE_BASE    (0x00000000 + 0x1BB000)
#define FLASH_STRIDE_NUM_48_9_ORANGE       3330
#define FLASH_COUNT_NUM_48_9_ORANGE        1

#define FLASH_ADDR_NUM_48_9_WHITE_BASE    (0x00000000 + 0x1BC000)
#define FLASH_STRIDE_NUM_48_9_WHITE       3330
#define FLASH_COUNT_NUM_48_9_WHITE        1

#define FLASH_ADDR_NUM_48_PERCENT_ORANGE_BASE    (0x00000000 + 0x1BD000)
#define FLASH_STRIDE_NUM_48_PERCENT_ORANGE       3330
#define FLASH_COUNT_NUM_48_PERCENT_ORANGE        1

#define FLASH_ADDR_NUM_48_PERCENT_WHITE_BASE    (0x00000000 + 0x1BE000)
#define FLASH_STRIDE_NUM_48_PERCENT_WHITE       3330
#define FLASH_COUNT_NUM_48_PERCENT_WHITE        1

#define FLASH_ADDR_OBLIQUE_LINE_BASE    (0x00000000 + 0x1BF000)
#define FLASH_STRIDE_OBLIQUE_LINE       770
#define FLASH_COUNT_OBLIQUE_LINE        1

#define FLASH_ADDR_OBLIQUE_LINE_DARK_BASE    (0x00000000 + 0x1C0000)
#define FLASH_STRIDE_OBLIQUE_LINE_DARK       770
#define FLASH_COUNT_OBLIQUE_LINE_DARK        1

#define FLASH_ADDR_PERCENT_BASE    (0x00000000 + 0x1C1000)
#define FLASH_STRIDE_PERCENT       682
#define FLASH_COUNT_PERCENT        1

#define FLASH_ADDR_POINT_BASE    (0x00000000 + 0x1C2000)
#define FLASH_STRIDE_POINT       330
#define FLASH_COUNT_POINT        1

#define FLASH_ADDR_STRIGULA_THREE_DARK_BASE    (0x00000000 + 0x1C3000)
#define FLASH_STRIDE_STRIGULA_THREE_DARK       1738
#define FLASH_COUNT_STRIGULA_THREE_DARK        1

#define FLASH_ADDR_STRIGULA_TWO_DARK_BASE    (0x00000000 + 0x1C4000)
#define FLASH_STRIDE_STRIGULA_TWO_DARK       1386
#define FLASH_COUNT_STRIGULA_TWO_DARK        1

#define FLASH_ADDR_TEMP_DROPS_TO_NORMAL_BASE    (0x00000000 + 0x1C5000)
#define FLASH_STRIDE_TEMP_DROPS_TO_NORMAL       9186
#define FLASH_COUNT_TEMP_DROPS_TO_NORMAL        1

#define FLASH_ADDR_TEXT_BAT_HEALTH_BASE    (0x00000000 + 0x1C8000)
#define FLASH_STRIDE_TEXT_BAT_HEALTH       4626
#define FLASH_COUNT_TEXT_BAT_HEALTH        1

#define FLASH_ADDR_TEXT_BAT_TEMP_BASE    (0x00000000 + 0x1CA000)
#define FLASH_STRIDE_TEXT_BAT_TEMP       4626
#define FLASH_COUNT_TEXT_BAT_TEMP        1

#define FLASH_ADDR_TEXT_CHARGING_HIGH_TEMP_BASE    (0x00000000 + 0x1CC000)
#define FLASH_STRIDE_TEXT_CHARGING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_CHARGING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_CHARGING_TEMP_BASE    (0x00000000 + 0x1D1000)
#define FLASH_STRIDE_TEXT_CHARGING_TEMP       2718
#define FLASH_COUNT_TEXT_CHARGING_TEMP        1

#define FLASH_ADDR_TEXT_CYCLE_INDEX_BASE    (0x00000000 + 0x1D2000)
#define FLASH_STRIDE_TEXT_CYCLE_INDEX       4626
#define FLASH_COUNT_TEXT_CYCLE_INDEX        1

#define FLASH_ADDR_TEXT_DISCHARGING_HIGH_TEMP_BASE    (0x00000000 + 0x1D4000)
#define FLASH_STRIDE_TEXT_DISCHARGING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_DISCHARGING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_DISCHARGING_TEMP_BASE    (0x00000000 + 0x1D9000)
#define FLASH_STRIDE_TEXT_DISCHARGING_TEMP       2718
#define FLASH_COUNT_TEXT_DISCHARGING_TEMP        1

#define FLASH_ADDR_TEXT_LOW_POWER_BASE    (0x00000000 + 0x1DA000)
#define FLASH_STRIDE_TEXT_LOW_POWER       5258
#define FLASH_COUNT_TEXT_LOW_POWER        1

#define FLASH_ADDR_TEXT_MINI_BASE    (0x00000000 + 0x1DC000)
#define FLASH_STRIDE_TEXT_MINI       2466
#define FLASH_COUNT_TEXT_MINI        1

#define FLASH_ADDR_TEXT_NO_ABNORMAL_RECORDS_BASE    (0x00000000 + 0x1DD000)
#define FLASH_STRIDE_TEXT_NO_ABNORMAL_RECORDS       5026
#define FLASH_COUNT_TEXT_NO_ABNORMAL_RECORDS        1

#define FLASH_ADDR_TEXT_PRESS_5S_TO_SETTING_BASE    (0x00000000 + 0x1DF000)
#define FLASH_STRIDE_TEXT_PRESS_5S_TO_SETTING       5954
#define FLASH_COUNT_TEXT_PRESS_5S_TO_SETTING        1

#define FLASH_ADDR_TEXT_PROTECTION_BASE    (0x00000000 + 0x1E1000)
#define FLASH_STRIDE_TEXT_PROTECTION       17346
#define FLASH_COUNT_TEXT_PROTECTION        2

#define FLASH_ADDR_TEXT_SAFEGUARD_BASE    (0x00000000 + 0x1EA000)
#define FLASH_STRIDE_TEXT_SAFEGUARD       26466
#define FLASH_COUNT_TEXT_SAFEGUARD        1

#define FLASH_ADDR_TEXT_STANDING_HIGH_TEMP_BASE    (0x00000000 + 0x1F1000)
#define FLASH_STRIDE_TEXT_STANDING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_STANDING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_STANDING_TEMP_BASE    (0x00000000 + 0x1F6000)
#define FLASH_STRIDE_TEXT_STANDING_TEMP       2718
#define FLASH_COUNT_TEXT_STANDING_TEMP        1

#define FLASH_ADDR_TEXT_TIME_BASE    (0x00000000 + 0x1F7000)
#define FLASH_STRIDE_TEXT_TIME       1474
#define FLASH_COUNT_TEXT_TIME        1

#define FLASH_ADDR_TEXT_VERSION_NUMBER_BASE    (0x00000000 + 0x1F8000)
#define FLASH_STRIDE_TEXT_VERSION_NUMBER       1902
#define FLASH_COUNT_TEXT_VERSION_NUMBER        1

#define FLASH_ADDR_TEXT_VOLTAGE_BASE    (0x00000000 + 0x1F9000)
#define FLASH_STRIDE_TEXT_VOLTAGE       1474
#define FLASH_COUNT_TEXT_VOLTAGE        1

#define FLASH_ADDR_TEXTTOTAL_VOLTAGE_BASE    (0x00000000 + 0x1FA000)
#define FLASH_STRIDE_TEXTTOTAL_VOLTAGE       1986
#define FLASH_COUNT_TEXTTOTAL_VOLTAGE        1

#define FLASH_ADDR_TIAO_BASE    (0x00000000 + 0x1FB000)
#define FLASH_STRIDE_TIAO       678
#define FLASH_COUNT_TIAO        1

#define FLASH_ADDR_TITLE_ABNORMAL_TEMP_BASE    (0x00000000 + 0x1FC000)
#define FLASH_STRIDE_TITLE_ABNORMAL_TEMP       15426
#define FLASH_COUNT_TITLE_ABNORMAL_TEMP        1

#define FLASH_ADDR_TITLE_ABNORMAL_VOLTAGE_BASE    (0x00000000 + 0x200000)
#define FLASH_STRIDE_TITLE_ABNORMAL_VOLTAGE       15426
#define FLASH_COUNT_TITLE_ABNORMAL_VOLTAGE        1

#define FLASH_ADDR_TITLE_CELL_VOLTAGE_BASE    (0x00000000 + 0x204000)
#define FLASH_STRIDE_TITLE_CELL_VOLTAGE       15426
#define FLASH_COUNT_TITLE_CELL_VOLTAGE        1

#define FLASH_ADDR_TITLE_SCREEN_OFF_DURATION_BASE    (0x00000000 + 0x208000)
#define FLASH_STRIDE_TITLE_SCREEN_OFF_DURATION       15426
#define FLASH_COUNT_TITLE_SCREEN_OFF_DURATION        1

#define FLASH_ADDR_TITLE_SOFTWARE_VERSION_BASE    (0x00000000 + 0x20C000)
#define FLASH_STRIDE_TITLE_SOFTWARE_VERSION       15426
#define FLASH_COUNT_TITLE_SOFTWARE_VERSION        1

#define FLASH_ADDR_VOLT_BASE    (0x00000000 + 0x210000)
#define FLASH_STRIDE_VOLT       682
#define FLASH_COUNT_VOLT        1

#define FLASH_ADDR_VOLT_DARK_BASE    (0x00000000 + 0x211000)
#define FLASH_STRIDE_VOLT_DARK       682
#define FLASH_COUNT_VOLT_DARK        1


/*
 * Per-image index macros — for named access within a category.
 *   addr = FLASH_ADDR_<CAT>_BASE + FLASH_IDX_<CAT>_<ITEM> * FLASH_STRIDE_<CAT>
 */
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_0  0
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_1  1
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_10  2
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_11  3
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_2  4
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_3  5
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_4  6
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_5  7
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_6  8
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_7  9
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_8  10
#define FLASH_IDX_HIGH_POWER_CHARGING_ANIMA_9  11

#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_0  0
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_1  1
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_10  2
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_11  3
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_2  4
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_3  5
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_4  6
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_5  7
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_6  8
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_7  9
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_8  10
#define FLASH_IDX_HIGH_POWER_STANDBY_ANIMA_9  11

#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_0  0
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_1  1
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_10  2
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_11  3
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_2  4
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_3  5
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_4  6
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_5  7
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_6  8
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_7  9
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_8  10
#define FLASH_IDX_LOW_POWER_CHARGING_ANIMA_9  11

#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_0  0
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_1  1
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_10  2
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_11  3
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_2  4
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_3  5
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_4  6
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_5  7
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_6  8
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_7  9
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_8  10
#define FLASH_IDX_LOW_POWER_STANDBY_ANIMA_9  11

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

#define FLASH_IDX_NUM_18_0  0
#define FLASH_IDX_NUM_18_1  1
#define FLASH_IDX_NUM_18_2  2
#define FLASH_IDX_NUM_18_3  3
#define FLASH_IDX_NUM_18_4  4
#define FLASH_IDX_NUM_18_5  5
#define FLASH_IDX_NUM_18_6  6
#define FLASH_IDX_NUM_18_7  7
#define FLASH_IDX_NUM_18_8  8
#define FLASH_IDX_NUM_18_9  9

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

#define FLASH_IDX_TEXT_PROTECTION_1  0
#define FLASH_IDX_TEXT_PROTECTION_2  1


/*
 * Absolute flash addresses and sizes for every image.
 */
#define FLASH_ADDR_AMPERE                        (0x00000000 + 0x0000)
#define FLASH_SIZE_AMPERE                        682
#define FLASH_ADDR_AMPERE_DARK                   (0x00000000 + 0x1000)
#define FLASH_SIZE_AMPERE_DARK                   682
#define FLASH_ADDR_BTN_1800S                     (0x00000000 + 0x2000)
#define FLASH_SIZE_BTN_1800S                     6338
#define FLASH_ADDR_BTN_1800S_DARK                (0x00000000 + 0x4000)
#define FLASH_SIZE_BTN_1800S_DARK                6338
#define FLASH_ADDR_BTN_300S                      (0x00000000 + 0x6000)
#define FLASH_SIZE_BTN_300S                      6338
#define FLASH_ADDR_BTN_300S_DARK                 (0x00000000 + 0x8000)
#define FLASH_SIZE_BTN_300S_DARK                 6338
#define FLASH_ADDR_BTN_30S                       (0x00000000 + 0xA000)
#define FLASH_SIZE_BTN_30S                       6338
#define FLASH_ADDR_BTN_30S_DARK                  (0x00000000 + 0xC000)
#define FLASH_SIZE_BTN_30S_DARK                  6338
#define FLASH_ADDR_BTN_60S                       (0x00000000 + 0xE000)
#define FLASH_SIZE_BTN_60S                       6338
#define FLASH_ADDR_BTN_60S_DARK                  (0x00000000 + 0x10000)
#define FLASH_SIZE_BTN_60S_DARK                  6338
#define FLASH_ADDR_CELL_MODEL                    (0x00000000 + 0x12000)
#define FLASH_SIZE_CELL_MODEL                    2562
#define FLASH_ADDR_CI                            (0x00000000 + 0x13000)
#define FLASH_SIZE_CI                            858
#define FLASH_ADDR_DEGREE_CENTIGRADE             (0x00000000 + 0x14000)
#define FLASH_SIZE_DEGREE_CENTIGRADE             1122
#define FLASH_ADDR_DI                            (0x00000000 + 0x15000)
#define FLASH_SIZE_DI                            678
#define FLASH_ADDR_DOUBLE_CLICK_SWITCH           (0x00000000 + 0x16000)
#define FLASH_SIZE_DOUBLE_CLICK_SWITCH           9186
#define FLASH_ADDR_DOUHAO                        (0x00000000 + 0x19000)
#define FLASH_SIZE_DOUHAO                        450
#define FLASH_ADDR_EMOJI_CHARGING                (0x00000000 + 0x1A000)
#define FLASH_SIZE_EMOJI_CHARGING                25826
#define FLASH_ADDR_EMOJI_HEALTHY                 (0x00000000 + 0x21000)
#define FLASH_SIZE_EMOJI_HEALTHY                 25826
#define FLASH_ADDR_EMOJI_LOW_POWER               (0x00000000 + 0x28000)
#define FLASH_SIZE_EMOJI_LOW_POWER               25826
#define FLASH_ADDR_EMOJI_NORMAL                  (0x00000000 + 0x2F000)
#define FLASH_SIZE_EMOJI_NORMAL                  25826
#define FLASH_ADDR_GONG                          (0x00000000 + 0x36000)
#define FLASH_SIZE_GONG                          678
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_0   (0x00000000 + 0x37000)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_0   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_1   (0x00000000 + 0x3D4E2)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_1   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_10  (0x00000000 + 0x439C4)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_10  25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_11  (0x00000000 + 0x49EA6)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_11  25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_2   (0x00000000 + 0x50388)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_2   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_3   (0x00000000 + 0x5686A)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_3   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_4   (0x00000000 + 0x5CD4C)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_4   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_5   (0x00000000 + 0x6322E)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_5   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_6   (0x00000000 + 0x69710)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_6   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_7   (0x00000000 + 0x6FBF2)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_7   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_8   (0x00000000 + 0x760D4)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_8   25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_9   (0x00000000 + 0x7C5B6)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_9   25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_0    (0x00000000 + 0x83000)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_0    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_1    (0x00000000 + 0x894E2)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_1    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_10   (0x00000000 + 0x8F9C4)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_10   25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_11   (0x00000000 + 0x95EA6)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_11   25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_2    (0x00000000 + 0x9C388)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_2    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_3    (0x00000000 + 0xA286A)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_3    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_4    (0x00000000 + 0xA8D4C)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_4    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_5    (0x00000000 + 0xAF22E)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_5    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_6    (0x00000000 + 0xB5710)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_6    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_7    (0x00000000 + 0xBBBF2)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_7    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_8    (0x00000000 + 0xC20D4)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_8    25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_9    (0x00000000 + 0xC85B6)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_9    25826
#define FLASH_ADDR_ICON_COUNT_DOWN               (0x00000000 + 0xCF000)
#define FLASH_SIZE_ICON_COUNT_DOWN               866
#define FLASH_ADDR_ICON_IN_1_BIG                 (0x00000000 + 0xD0000)
#define FLASH_SIZE_ICON_IN_1_BIG                 8226
#define FLASH_ADDR_ICON_IN_1_LITTLE              (0x00000000 + 0xD3000)
#define FLASH_SIZE_ICON_IN_1_LITTLE              2706
#define FLASH_ADDR_ICON_IN_2_BIG                 (0x00000000 + 0xD4000)
#define FLASH_SIZE_ICON_IN_2_BIG                 8226
#define FLASH_ADDR_ICON_IN_2_LITTLE              (0x00000000 + 0xD7000)
#define FLASH_SIZE_ICON_IN_2_LITTLE              2706
#define FLASH_ADDR_ICON_IN_3_BIG                 (0x00000000 + 0xD8000)
#define FLASH_SIZE_ICON_IN_3_BIG                 8226
#define FLASH_ADDR_ICON_IN_3_LITTLE              (0x00000000 + 0xDB000)
#define FLASH_SIZE_ICON_IN_3_LITTLE              2706
#define FLASH_ADDR_ICON_NORMAL_1_BIG             (0x00000000 + 0xDC000)
#define FLASH_SIZE_ICON_NORMAL_1_BIG             8226
#define FLASH_ADDR_ICON_NORMAL_2_BIG             (0x00000000 + 0xDF000)
#define FLASH_SIZE_ICON_NORMAL_2_BIG             8226
#define FLASH_ADDR_ICON_NORMAL_3_BIG             (0x00000000 + 0xE2000)
#define FLASH_SIZE_ICON_NORMAL_3_BIG             8226
#define FLASH_ADDR_ICON_OUT_1_BIG                (0x00000000 + 0xE5000)
#define FLASH_SIZE_ICON_OUT_1_BIG                8226
#define FLASH_ADDR_ICON_OUT_1_LITTLE             (0x00000000 + 0xE8000)
#define FLASH_SIZE_ICON_OUT_1_LITTLE             2706
#define FLASH_ADDR_ICON_OUT_2_BIG                (0x00000000 + 0xE9000)
#define FLASH_SIZE_ICON_OUT_2_BIG                8226
#define FLASH_ADDR_ICON_OUT_2_LITTLE             (0x00000000 + 0xEC000)
#define FLASH_SIZE_ICON_OUT_2_LITTLE             2706
#define FLASH_ADDR_ICON_OUT_3_BIG                (0x00000000 + 0xED000)
#define FLASH_SIZE_ICON_OUT_3_BIG                8226
#define FLASH_ADDR_ICON_OUT_3_LITTLE             (0x00000000 + 0xF0000)
#define FLASH_SIZE_ICON_OUT_3_LITTLE             2706
#define FLASH_ADDR_ICON_PROTECTION               (0x00000000 + 0xF1000)
#define FLASH_SIZE_ICON_PROTECTION               12866
#define FLASH_ADDR_ICON_SAFE                     (0x00000000 + 0xF5000)
#define FLASH_SIZE_ICON_SAFE                     12866
#define FLASH_ADDR_ICON_TEMP_HIGH                (0x00000000 + 0xF9000)
#define FLASH_SIZE_ICON_TEMP_HIGH                12866
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_0    (0x00000000 + 0xFD000)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_0    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_1    (0x00000000 + 0x1034E2)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_1    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_10   (0x00000000 + 0x1099C4)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_10   25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_11   (0x00000000 + 0x10FEA6)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_11   25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_2    (0x00000000 + 0x116388)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_2    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_3    (0x00000000 + 0x11C86A)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_3    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_4    (0x00000000 + 0x122D4C)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_4    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_5    (0x00000000 + 0x12922E)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_5    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_6    (0x00000000 + 0x12F710)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_6    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_7    (0x00000000 + 0x135BF2)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_7    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_8    (0x00000000 + 0x13C0D4)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_8    25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_9    (0x00000000 + 0x1425B6)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_9    25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_0     (0x00000000 + 0x149000)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_0     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_1     (0x00000000 + 0x14F4E2)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_1     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_10    (0x00000000 + 0x1559C4)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_10    25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_11    (0x00000000 + 0x15BEA6)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_11    25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_2     (0x00000000 + 0x162388)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_2     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_3     (0x00000000 + 0x16886A)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_3     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_4     (0x00000000 + 0x16ED4C)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_4     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_5     (0x00000000 + 0x17522E)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_5     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_6     (0x00000000 + 0x17B710)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_6     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_7     (0x00000000 + 0x181BF2)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_7     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_8     (0x00000000 + 0x1880D4)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_8     25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_9     (0x00000000 + 0x18E5B6)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_9     25826
#define FLASH_ADDR_NUM_12_0                      (0x00000000 + 0x195000)
#define FLASH_SIZE_NUM_12_0                      226
#define FLASH_ADDR_NUM_12_1                      (0x00000000 + 0x19515A)
#define FLASH_SIZE_NUM_12_1                      186
#define FLASH_ADDR_NUM_12_2                      (0x00000000 + 0x1952B4)
#define FLASH_SIZE_NUM_12_2                      226
#define FLASH_ADDR_NUM_12_3                      (0x00000000 + 0x19540E)
#define FLASH_SIZE_NUM_12_3                      226
#define FLASH_ADDR_NUM_12_4                      (0x00000000 + 0x195568)
#define FLASH_SIZE_NUM_12_4                      266
#define FLASH_ADDR_NUM_12_5                      (0x00000000 + 0x1956C2)
#define FLASH_SIZE_NUM_12_5                      226
#define FLASH_ADDR_NUM_12_6                      (0x00000000 + 0x19581C)
#define FLASH_SIZE_NUM_12_6                      226
#define FLASH_ADDR_NUM_12_7                      (0x00000000 + 0x195976)
#define FLASH_SIZE_NUM_12_7                      226
#define FLASH_ADDR_NUM_12_8                      (0x00000000 + 0x195AD0)
#define FLASH_SIZE_NUM_12_8                      226
#define FLASH_ADDR_NUM_12_9                      (0x00000000 + 0x195C2A)
#define FLASH_SIZE_NUM_12_9                      226
#define FLASH_ADDR_NUM_12                        (0x00000000 + 0x195D84)
#define FLASH_SIZE_NUM_12                        226
#define FLASH_ADDR_NUM_12_A                      (0x00000000 + 0x195EDE)
#define FLASH_SIZE_NUM_12_A                      266
#define FLASH_ADDR_NUM_12_B                      (0x00000000 + 0x196038)
#define FLASH_SIZE_NUM_12_B                      226
#define FLASH_ADDR_NUM_12_C                      (0x00000000 + 0x196192)
#define FLASH_SIZE_NUM_12_C                      266
#define FLASH_ADDR_NUM_12_D                      (0x00000000 + 0x1962EC)
#define FLASH_SIZE_NUM_12_D                      266
#define FLASH_ADDR_NUM_12_E                      (0x00000000 + 0x196446)
#define FLASH_SIZE_NUM_12_E                      226
#define FLASH_ADDR_NUM_12_F                      (0x00000000 + 0x1965A0)
#define FLASH_SIZE_NUM_12_F                      226
#define FLASH_ADDR_NUM_12_G                      (0x00000000 + 0x1966FA)
#define FLASH_SIZE_NUM_12_G                      266
#define FLASH_ADDR_NUM_12_H                      (0x00000000 + 0x196854)
#define FLASH_SIZE_NUM_12_H                      266
#define FLASH_ADDR_NUM_12_I                      (0x00000000 + 0x1969AE)
#define FLASH_SIZE_NUM_12_I                      186
#define FLASH_ADDR_NUM_12_J                      (0x00000000 + 0x196B08)
#define FLASH_SIZE_NUM_12_J                      226
#define FLASH_ADDR_NUM_12_K                      (0x00000000 + 0x196C62)
#define FLASH_SIZE_NUM_12_K                      226
#define FLASH_ADDR_NUM_12_L                      (0x00000000 + 0x196DBC)
#define FLASH_SIZE_NUM_12_L                      226
#define FLASH_ADDR_NUM_12_M                      (0x00000000 + 0x196F16)
#define FLASH_SIZE_NUM_12_M                      306
#define FLASH_ADDR_NUM_12_N                      (0x00000000 + 0x197070)
#define FLASH_SIZE_NUM_12_N                      266
#define FLASH_ADDR_NUM_12_O                      (0x00000000 + 0x1971CA)
#define FLASH_SIZE_NUM_12_O                      266
#define FLASH_ADDR_NUM_12_P                      (0x00000000 + 0x197324)
#define FLASH_SIZE_NUM_12_P                      226
#define FLASH_ADDR_NUM_12_Q                      (0x00000000 + 0x19747E)
#define FLASH_SIZE_NUM_12_Q                      266
#define FLASH_ADDR_NUM_12_R                      (0x00000000 + 0x1975D8)
#define FLASH_SIZE_NUM_12_R                      226
#define FLASH_ADDR_NUM_12_S                      (0x00000000 + 0x197732)
#define FLASH_SIZE_NUM_12_S                      226
#define FLASH_ADDR_NUM_12_T                      (0x00000000 + 0x19788C)
#define FLASH_SIZE_NUM_12_T                      226
#define FLASH_ADDR_NUM_12_U                      (0x00000000 + 0x1979E6)
#define FLASH_SIZE_NUM_12_U                      266
#define FLASH_ADDR_NUM_12_V                      (0x00000000 + 0x197B40)
#define FLASH_SIZE_NUM_12_V                      266
#define FLASH_ADDR_NUM_12_W                      (0x00000000 + 0x197C9A)
#define FLASH_SIZE_NUM_12_W                      346
#define FLASH_ADDR_NUM_12_X                      (0x00000000 + 0x197DF4)
#define FLASH_SIZE_NUM_12_X                      266
#define FLASH_ADDR_NUM_12_Y                      (0x00000000 + 0x197F4E)
#define FLASH_SIZE_NUM_12_Y                      266
#define FLASH_ADDR_NUM_12_Z                      (0x00000000 + 0x1980A8)
#define FLASH_SIZE_NUM_12_Z                      266
#define FLASH_ADDR_NUM_12_Z_COLON                (0x00000000 + 0x198202)
#define FLASH_SIZE_NUM_12_Z_COLON                186
#define FLASH_ADDR_NUM_12_Z_DEGREE               (0x00000000 + 0x19835C)
#define FLASH_SIZE_NUM_12_Z_DEGREE               346
#define FLASH_ADDR_NUM_12_Z_DOT                  (0x00000000 + 0x1984B6)
#define FLASH_SIZE_NUM_12_Z_DOT                  146
#define FLASH_ADDR_NUM_16_0                      (0x00000000 + 0x199000)
#define FLASH_SIZE_NUM_16_0                      450
#define FLASH_ADDR_NUM_16_1                      (0x00000000 + 0x199302)
#define FLASH_SIZE_NUM_16_1                      322
#define FLASH_ADDR_NUM_16_2                      (0x00000000 + 0x199604)
#define FLASH_SIZE_NUM_16_2                      450
#define FLASH_ADDR_NUM_16_3                      (0x00000000 + 0x199906)
#define FLASH_SIZE_NUM_16_3                      450
#define FLASH_ADDR_NUM_16_4                      (0x00000000 + 0x199C08)
#define FLASH_SIZE_NUM_16_4                      450
#define FLASH_ADDR_NUM_16_5                      (0x00000000 + 0x199F0A)
#define FLASH_SIZE_NUM_16_5                      450
#define FLASH_ADDR_NUM_16_6                      (0x00000000 + 0x19A20C)
#define FLASH_SIZE_NUM_16_6                      450
#define FLASH_ADDR_NUM_16_7                      (0x00000000 + 0x19A50E)
#define FLASH_SIZE_NUM_16_7                      450
#define FLASH_ADDR_NUM_16_8                      (0x00000000 + 0x19A810)
#define FLASH_SIZE_NUM_16_8                      450
#define FLASH_ADDR_NUM_16_9                      (0x00000000 + 0x19AB12)
#define FLASH_SIZE_NUM_16_9                      450
#define FLASH_ADDR_NUM_16                        (0x00000000 + 0x19AE14)
#define FLASH_SIZE_NUM_16                        322
#define FLASH_ADDR_NUM_16_A                      (0x00000000 + 0x19B116)
#define FLASH_SIZE_NUM_16_A                      514
#define FLASH_ADDR_NUM_16_B                      (0x00000000 + 0x19B418)
#define FLASH_SIZE_NUM_16_B                      450
#define FLASH_ADDR_NUM_16_C                      (0x00000000 + 0x19B71A)
#define FLASH_SIZE_NUM_16_C                      514
#define FLASH_ADDR_NUM_16_D                      (0x00000000 + 0x19BA1C)
#define FLASH_SIZE_NUM_16_D                      514
#define FLASH_ADDR_NUM_16_E                      (0x00000000 + 0x19BD1E)
#define FLASH_SIZE_NUM_16_E                      386
#define FLASH_ADDR_NUM_16_F                      (0x00000000 + 0x19C020)
#define FLASH_SIZE_NUM_16_F                      386
#define FLASH_ADDR_NUM_16_G                      (0x00000000 + 0x19C322)
#define FLASH_SIZE_NUM_16_G                      514
#define FLASH_ADDR_NUM_16_H                      (0x00000000 + 0x19C624)
#define FLASH_SIZE_NUM_16_H                      450
#define FLASH_ADDR_NUM_16_I                      (0x00000000 + 0x19C926)
#define FLASH_SIZE_NUM_16_I                      258
#define FLASH_ADDR_NUM_16_J                      (0x00000000 + 0x19CC28)
#define FLASH_SIZE_NUM_16_J                      386
#define FLASH_ADDR_NUM_16_K                      (0x00000000 + 0x19CF2A)
#define FLASH_SIZE_NUM_16_K                      450
#define FLASH_ADDR_NUM_16_L                      (0x00000000 + 0x19D22C)
#define FLASH_SIZE_NUM_16_L                      386
#define FLASH_ADDR_NUM_16_M                      (0x00000000 + 0x19D52E)
#define FLASH_SIZE_NUM_16_M                      578
#define FLASH_ADDR_NUM_16_N                      (0x00000000 + 0x19D830)
#define FLASH_SIZE_NUM_16_N                      450
#define FLASH_ADDR_NUM_16_O                      (0x00000000 + 0x19DB32)
#define FLASH_SIZE_NUM_16_O                      514
#define FLASH_ADDR_NUM_16_P                      (0x00000000 + 0x19DE34)
#define FLASH_SIZE_NUM_16_P                      386
#define FLASH_ADDR_NUM_16_Q                      (0x00000000 + 0x19E136)
#define FLASH_SIZE_NUM_16_Q                      514
#define FLASH_ADDR_NUM_16_R                      (0x00000000 + 0x19E438)
#define FLASH_SIZE_NUM_16_R                      450
#define FLASH_ADDR_NUM_16_S                      (0x00000000 + 0x19E73A)
#define FLASH_SIZE_NUM_16_S                      386
#define FLASH_ADDR_NUM_16_T                      (0x00000000 + 0x19EA3C)
#define FLASH_SIZE_NUM_16_T                      450
#define FLASH_ADDR_NUM_16_U                      (0x00000000 + 0x19ED3E)
#define FLASH_SIZE_NUM_16_U                      450
#define FLASH_ADDR_NUM_16_V                      (0x00000000 + 0x19F040)
#define FLASH_SIZE_NUM_16_V                      514
#define FLASH_ADDR_NUM_16_W                      (0x00000000 + 0x19F342)
#define FLASH_SIZE_NUM_16_W                      706
#define FLASH_ADDR_NUM_16_X                      (0x00000000 + 0x19F644)
#define FLASH_SIZE_NUM_16_X                      514
#define FLASH_ADDR_NUM_16_Y                      (0x00000000 + 0x19F946)
#define FLASH_SIZE_NUM_16_Y                      450
#define FLASH_ADDR_NUM_16_Z                      (0x00000000 + 0x19FC48)
#define FLASH_SIZE_NUM_16_Z                      450
#define FLASH_ADDR_NUM_16_Z_COLON                (0x00000000 + 0x19FF4A)
#define FLASH_SIZE_NUM_16_Z_COLON                258
#define FLASH_ADDR_NUM_16_Z_DEGREE               (0x00000000 + 0x1A024C)
#define FLASH_SIZE_NUM_16_Z_DEGREE               770
#define FLASH_ADDR_NUM_16_Z_DOT                  (0x00000000 + 0x1A054E)
#define FLASH_SIZE_NUM_16_Z_DOT                  258
#define FLASH_ADDR_NUM_18_0                      (0x00000000 + 0x1A1000)
#define FLASH_SIZE_NUM_18_0                      570
#define FLASH_ADDR_NUM_18_1                      (0x00000000 + 0x1A123A)
#define FLASH_SIZE_NUM_18_1                      318
#define FLASH_ADDR_NUM_18_2                      (0x00000000 + 0x1A1474)
#define FLASH_SIZE_NUM_18_2                      570
#define FLASH_ADDR_NUM_18_3                      (0x00000000 + 0x1A16AE)
#define FLASH_SIZE_NUM_18_3                      570
#define FLASH_ADDR_NUM_18_4                      (0x00000000 + 0x1A18E8)
#define FLASH_SIZE_NUM_18_4                      570
#define FLASH_ADDR_NUM_18_5                      (0x00000000 + 0x1A1B22)
#define FLASH_SIZE_NUM_18_5                      570
#define FLASH_ADDR_NUM_18_6                      (0x00000000 + 0x1A1D5C)
#define FLASH_SIZE_NUM_18_6                      570
#define FLASH_ADDR_NUM_18_7                      (0x00000000 + 0x1A1F96)
#define FLASH_SIZE_NUM_18_7                      486
#define FLASH_ADDR_NUM_18_8                      (0x00000000 + 0x1A21D0)
#define FLASH_SIZE_NUM_18_8                      570
#define FLASH_ADDR_NUM_18_9                      (0x00000000 + 0x1A240A)
#define FLASH_SIZE_NUM_18_9                      570
#define FLASH_ADDR_NUM_18_HOUR                   (0x00000000 + 0x1A3000)
#define FLASH_SIZE_NUM_18_HOUR                   570
#define FLASH_ADDR_NUM_18_MINUTE                 (0x00000000 + 0x1A4000)
#define FLASH_SIZE_NUM_18_MINUTE                 906
#define FLASH_ADDR_NUM_20_0                      (0x00000000 + 0x1A5000)
#define FLASH_SIZE_NUM_20_0                      594
#define FLASH_ADDR_NUM_20_1                      (0x00000000 + 0x1A5252)
#define FLASH_SIZE_NUM_20_1                      418
#define FLASH_ADDR_NUM_20_2                      (0x00000000 + 0x1A54A4)
#define FLASH_SIZE_NUM_20_2                      594
#define FLASH_ADDR_NUM_20_3                      (0x00000000 + 0x1A56F6)
#define FLASH_SIZE_NUM_20_3                      594
#define FLASH_ADDR_NUM_20_4                      (0x00000000 + 0x1A5948)
#define FLASH_SIZE_NUM_20_4                      594
#define FLASH_ADDR_NUM_20_5                      (0x00000000 + 0x1A5B9A)
#define FLASH_SIZE_NUM_20_5                      594
#define FLASH_ADDR_NUM_20_6                      (0x00000000 + 0x1A5DEC)
#define FLASH_SIZE_NUM_20_6                      594
#define FLASH_ADDR_NUM_20_7                      (0x00000000 + 0x1A603E)
#define FLASH_SIZE_NUM_20_7                      594
#define FLASH_ADDR_NUM_20_8                      (0x00000000 + 0x1A6290)
#define FLASH_SIZE_NUM_20_8                      594
#define FLASH_ADDR_NUM_20_9                      (0x00000000 + 0x1A64E2)
#define FLASH_SIZE_NUM_20_9                      594
#define FLASH_ADDR_NUM_20_1_NULL                 (0x00000000 + 0x1A7000)
#define FLASH_SIZE_NUM_20_1_NULL                 594
#define FLASH_ADDR_NUM_20_1_S                    (0x00000000 + 0x1A8000)
#define FLASH_SIZE_NUM_20_1_S                    594
#define FLASH_ADDR_NUM_48_0_ORANGE               (0x00000000 + 0x1A9000)
#define FLASH_SIZE_NUM_48_0_ORANGE               3330
#define FLASH_ADDR_NUM_48_0_WHITE                (0x00000000 + 0x1AA000)
#define FLASH_SIZE_NUM_48_0_WHITE                3330
#define FLASH_ADDR_NUM_48_1_ORANGE               (0x00000000 + 0x1AB000)
#define FLASH_SIZE_NUM_48_1_ORANGE               2178
#define FLASH_ADDR_NUM_48_1_WHITE                (0x00000000 + 0x1AC000)
#define FLASH_SIZE_NUM_48_1_WHITE                2178
#define FLASH_ADDR_NUM_48_2_ORANGE               (0x00000000 + 0x1AD000)
#define FLASH_SIZE_NUM_48_2_ORANGE               3330
#define FLASH_ADDR_NUM_48_2_WHITE                (0x00000000 + 0x1AE000)
#define FLASH_SIZE_NUM_48_2_WHITE                3330
#define FLASH_ADDR_NUM_48_3_ORANGE               (0x00000000 + 0x1AF000)
#define FLASH_SIZE_NUM_48_3_ORANGE               3330
#define FLASH_ADDR_NUM_48_3_WHITE                (0x00000000 + 0x1B0000)
#define FLASH_SIZE_NUM_48_3_WHITE                3330
#define FLASH_ADDR_NUM_48_4_ORANGE               (0x00000000 + 0x1B1000)
#define FLASH_SIZE_NUM_48_4_ORANGE               3330
#define FLASH_ADDR_NUM_48_4_WHITE                (0x00000000 + 0x1B2000)
#define FLASH_SIZE_NUM_48_4_WHITE                3330
#define FLASH_ADDR_NUM_48_5_ORANGE               (0x00000000 + 0x1B3000)
#define FLASH_SIZE_NUM_48_5_ORANGE               3330
#define FLASH_ADDR_NUM_48_5_WHITE                (0x00000000 + 0x1B4000)
#define FLASH_SIZE_NUM_48_5_WHITE                3330
#define FLASH_ADDR_NUM_48_6_ORANGE               (0x00000000 + 0x1B5000)
#define FLASH_SIZE_NUM_48_6_ORANGE               3330
#define FLASH_ADDR_NUM_48_6_WHITE                (0x00000000 + 0x1B6000)
#define FLASH_SIZE_NUM_48_6_WHITE                3330
#define FLASH_ADDR_NUM_48_7_ORANGE               (0x00000000 + 0x1B7000)
#define FLASH_SIZE_NUM_48_7_ORANGE               3330
#define FLASH_ADDR_NUM_48_7_WHITE                (0x00000000 + 0x1B8000)
#define FLASH_SIZE_NUM_48_7_WHITE                3330
#define FLASH_ADDR_NUM_48_8_ORANGE               (0x00000000 + 0x1B9000)
#define FLASH_SIZE_NUM_48_8_ORANGE               3330
#define FLASH_ADDR_NUM_48_8_WHITE                (0x00000000 + 0x1BA000)
#define FLASH_SIZE_NUM_48_8_WHITE                3330
#define FLASH_ADDR_NUM_48_9_ORANGE               (0x00000000 + 0x1BB000)
#define FLASH_SIZE_NUM_48_9_ORANGE               3330
#define FLASH_ADDR_NUM_48_9_WHITE                (0x00000000 + 0x1BC000)
#define FLASH_SIZE_NUM_48_9_WHITE                3330
#define FLASH_ADDR_NUM_48_PERCENT_ORANGE         (0x00000000 + 0x1BD000)
#define FLASH_SIZE_NUM_48_PERCENT_ORANGE         3330
#define FLASH_ADDR_NUM_48_PERCENT_WHITE          (0x00000000 + 0x1BE000)
#define FLASH_SIZE_NUM_48_PERCENT_WHITE          3330
#define FLASH_ADDR_OBLIQUE_LINE                  (0x00000000 + 0x1BF000)
#define FLASH_SIZE_OBLIQUE_LINE                  770
#define FLASH_ADDR_OBLIQUE_LINE_DARK             (0x00000000 + 0x1C0000)
#define FLASH_SIZE_OBLIQUE_LINE_DARK             770
#define FLASH_ADDR_PERCENT                       (0x00000000 + 0x1C1000)
#define FLASH_SIZE_PERCENT                       682
#define FLASH_ADDR_POINT                         (0x00000000 + 0x1C2000)
#define FLASH_SIZE_POINT                         330
#define FLASH_ADDR_STRIGULA_THREE_DARK           (0x00000000 + 0x1C3000)
#define FLASH_SIZE_STRIGULA_THREE_DARK           1738
#define FLASH_ADDR_STRIGULA_TWO_DARK             (0x00000000 + 0x1C4000)
#define FLASH_SIZE_STRIGULA_TWO_DARK             1386
#define FLASH_ADDR_TEMP_DROPS_TO_NORMAL          (0x00000000 + 0x1C5000)
#define FLASH_SIZE_TEMP_DROPS_TO_NORMAL          9186
#define FLASH_ADDR_TEXT_BAT_HEALTH               (0x00000000 + 0x1C8000)
#define FLASH_SIZE_TEXT_BAT_HEALTH               4626
#define FLASH_ADDR_TEXT_BAT_TEMP                 (0x00000000 + 0x1CA000)
#define FLASH_SIZE_TEXT_BAT_TEMP                 4626
#define FLASH_ADDR_TEXT_CHARGING_HIGH_TEMP       (0x00000000 + 0x1CC000)
#define FLASH_SIZE_TEXT_CHARGING_HIGH_TEMP       17346
#define FLASH_ADDR_TEXT_CHARGING_TEMP            (0x00000000 + 0x1D1000)
#define FLASH_SIZE_TEXT_CHARGING_TEMP            2718
#define FLASH_ADDR_TEXT_CYCLE_INDEX              (0x00000000 + 0x1D2000)
#define FLASH_SIZE_TEXT_CYCLE_INDEX              4626
#define FLASH_ADDR_TEXT_DISCHARGING_HIGH_TEMP    (0x00000000 + 0x1D4000)
#define FLASH_SIZE_TEXT_DISCHARGING_HIGH_TEMP    17346
#define FLASH_ADDR_TEXT_DISCHARGING_TEMP         (0x00000000 + 0x1D9000)
#define FLASH_SIZE_TEXT_DISCHARGING_TEMP         2718
#define FLASH_ADDR_TEXT_LOW_POWER                (0x00000000 + 0x1DA000)
#define FLASH_SIZE_TEXT_LOW_POWER                5258
#define FLASH_ADDR_TEXT_MINI                     (0x00000000 + 0x1DC000)
#define FLASH_SIZE_TEXT_MINI                     2466
#define FLASH_ADDR_TEXT_NO_ABNORMAL_RECORDS      (0x00000000 + 0x1DD000)
#define FLASH_SIZE_TEXT_NO_ABNORMAL_RECORDS      5026
#define FLASH_ADDR_TEXT_PRESS_5S_TO_SETTING      (0x00000000 + 0x1DF000)
#define FLASH_SIZE_TEXT_PRESS_5S_TO_SETTING      5954
#define FLASH_ADDR_TEXT_PROTECTION_1             (0x00000000 + 0x1E1000)
#define FLASH_SIZE_TEXT_PROTECTION_1             17346
#define FLASH_ADDR_TEXT_PROTECTION_2             (0x00000000 + 0x1E53C2)
#define FLASH_SIZE_TEXT_PROTECTION_2             9186
#define FLASH_ADDR_TEXT_SAFEGUARD                (0x00000000 + 0x1EA000)
#define FLASH_SIZE_TEXT_SAFEGUARD                26466
#define FLASH_ADDR_TEXT_STANDING_HIGH_TEMP       (0x00000000 + 0x1F1000)
#define FLASH_SIZE_TEXT_STANDING_HIGH_TEMP       17346
#define FLASH_ADDR_TEXT_STANDING_TEMP            (0x00000000 + 0x1F6000)
#define FLASH_SIZE_TEXT_STANDING_TEMP            2718
#define FLASH_ADDR_TEXT_TIME                     (0x00000000 + 0x1F7000)
#define FLASH_SIZE_TEXT_TIME                     1474
#define FLASH_ADDR_TEXT_VERSION_NUMBER           (0x00000000 + 0x1F8000)
#define FLASH_SIZE_TEXT_VERSION_NUMBER           1902
#define FLASH_ADDR_TEXT_VOLTAGE                  (0x00000000 + 0x1F9000)
#define FLASH_SIZE_TEXT_VOLTAGE                  1474
#define FLASH_ADDR_TEXTTOTAL_VOLTAGE             (0x00000000 + 0x1FA000)
#define FLASH_SIZE_TEXTTOTAL_VOLTAGE             1986
#define FLASH_ADDR_TIAO                          (0x00000000 + 0x1FB000)
#define FLASH_SIZE_TIAO                          678
#define FLASH_ADDR_TITLE_ABNORMAL_TEMP           (0x00000000 + 0x1FC000)
#define FLASH_SIZE_TITLE_ABNORMAL_TEMP           15426
#define FLASH_ADDR_TITLE_ABNORMAL_VOLTAGE        (0x00000000 + 0x200000)
#define FLASH_SIZE_TITLE_ABNORMAL_VOLTAGE        15426
#define FLASH_ADDR_TITLE_CELL_VOLTAGE            (0x00000000 + 0x204000)
#define FLASH_SIZE_TITLE_CELL_VOLTAGE            15426
#define FLASH_ADDR_TITLE_SCREEN_OFF_DURATION     (0x00000000 + 0x208000)
#define FLASH_SIZE_TITLE_SCREEN_OFF_DURATION     15426
#define FLASH_ADDR_TITLE_SOFTWARE_VERSION        (0x00000000 + 0x20C000)
#define FLASH_SIZE_TITLE_SOFTWARE_VERSION        15426
#define FLASH_ADDR_VOLT                          (0x00000000 + 0x210000)
#define FLASH_SIZE_VOLT                          682
#define FLASH_ADDR_VOLT_DARK                     (0x00000000 + 0x211000)
#define FLASH_SIZE_VOLT_DARK                     682

#endif /* __FLASH_IMAGE_ADDR_H__ */
