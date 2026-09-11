/*
 * flash_image_addr.h — Auto-generated, do not edit.
 *
 * P25Q64SH Flash Image Address Map (64 Mb = 8 MB)
 * Sector size: 4096 bytes (4 KB)
 *
 * Images:       310
 * Categories:   101
 * Flash used:   3986090 bytes (3892.7 KB)
 * Sectors used: 974 / 2048
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
 *   HEALTHY_ANIMA                        base=0x037000  stride=25826  count=12    sectors=[55 – 130]
 *   HIGH_POWER_CHARGING_ANIMA            base=0x083000  stride=25826  count=12    sectors=[131 – 206]
 *   HIGH_POWER_DISCHARGING_ANIMA         base=0x0CF000  stride=25826  count=12    sectors=[207 – 282]
 *   HIGH_POWER_STANDBY_ANIMA             base=0x11B000  stride=25826  count=12    sectors=[283 – 358]
 *   ICON_COUNT_DOWN                      base=0x167000  stride=866    count=1     sectors=[359]
 *   ICON_IN_1_BIG                        base=0x168000  stride=8386   count=1     sectors=[360 – 362]
 *   ICON_IN_1_LITTLE                     base=0x16B000  stride=2706   count=1     sectors=[363]
 *   ICON_IN_2_BIG                        base=0x16C000  stride=8386   count=1     sectors=[364 – 366]
 *   ICON_IN_2_LITTLE                     base=0x16F000  stride=2706   count=1     sectors=[367]
 *   ICON_IN_3_BIG                        base=0x170000  stride=8386   count=1     sectors=[368 – 370]
 *   ICON_IN_3_LITTLE                     base=0x173000  stride=2706   count=1     sectors=[371]
 *   ICON_NORMAL_1_BIG                    base=0x174000  stride=8226   count=1     sectors=[372 – 374]
 *   ICON_NORMAL_2_BIG                    base=0x177000  stride=8226   count=1     sectors=[375 – 377]
 *   ICON_NORMAL_3_BIG                    base=0x17A000  stride=8226   count=1     sectors=[378 – 380]
 *   ICON_OUT_1_BIG                       base=0x17D000  stride=8386   count=1     sectors=[381 – 383]
 *   ICON_OUT_1_LITTLE                    base=0x180000  stride=2706   count=1     sectors=[384]
 *   ICON_OUT_2_BIG                       base=0x181000  stride=8386   count=1     sectors=[385 – 387]
 *   ICON_OUT_2_LITTLE                    base=0x184000  stride=2706   count=1     sectors=[388]
 *   ICON_OUT_3_BIG                       base=0x185000  stride=8386   count=1     sectors=[389 – 391]
 *   ICON_OUT_3_LITTLE                    base=0x188000  stride=2706   count=1     sectors=[392]
 *   ICON_PROTECTION                      base=0x189000  stride=12866  count=1     sectors=[393 – 396]
 *   ICON_SAFE                            base=0x18D000  stride=12866  count=1     sectors=[397 – 400]
 *   ICON_TEMP_HIGH                       base=0x191000  stride=12866  count=1     sectors=[401 – 404]
 *   LOW_POWER_CHARGING_ANIMA             base=0x195000  stride=25826  count=12    sectors=[405 – 480]
 *   LOW_POWER_DISCHARGING_ANIMA          base=0x1E1000  stride=25826  count=12    sectors=[481 – 556]
 *   LOW_POWER_STANDBY_ANIMA              base=0x22D000  stride=25826  count=12    sectors=[557 – 632]
 *   NUM_12                               base=0x279000  stride=346    count=40    sectors=[633 – 636]
 *   NUM_16                               base=0x27D000  stride=770    count=40    sectors=[637 – 644]
 *   NUM_18                               base=0x285000  stride=570    count=10    sectors=[645 – 646]
 *   NUM_18_HOUR                          base=0x287000  stride=570    count=1     sectors=[647]
 *   NUM_18_MINUTE                        base=0x288000  stride=906    count=1     sectors=[648]
 *   NUM_20                               base=0x289000  stride=594    count=10    sectors=[649 – 650]
 *   NUM_20_1_NULL                        base=0x28B000  stride=594    count=1     sectors=[651]
 *   NUM_20_1                             base=0x28C000  stride=594    count=1     sectors=[652]
 *   NUM_48_0_WHITE                       base=0x28D000  stride=3330   count=1     sectors=[653]
 *   NUM_48_1_WHITE                       base=0x28E000  stride=2178   count=1     sectors=[654]
 *   NUM_48_2_WHITE                       base=0x28F000  stride=3330   count=1     sectors=[655]
 *   NUM_48_3_WHITE                       base=0x290000  stride=3330   count=1     sectors=[656]
 *   NUM_48_4_WHITE                       base=0x291000  stride=3330   count=1     sectors=[657]
 *   NUM_48_5_WHITE                       base=0x292000  stride=3330   count=1     sectors=[658]
 *   NUM_48_6_WHITE                       base=0x293000  stride=3330   count=1     sectors=[659]
 *   NUM_48_7_WHITE                       base=0x294000  stride=3330   count=1     sectors=[660]
 *   NUM_48_8_WHITE                       base=0x295000  stride=3330   count=1     sectors=[661]
 *   NUM_48_9_WHITE                       base=0x296000  stride=3330   count=1     sectors=[662]
 *   NUM_48_PERCENT_WHITE                 base=0x297000  stride=3330   count=1     sectors=[663]
 *   OBLIQUE_LINE                         base=0x298000  stride=770    count=1     sectors=[664]
 *   OBLIQUE_LINE_DARK                    base=0x299000  stride=770    count=1     sectors=[665]
 *   PERCENT                              base=0x29A000  stride=682    count=1     sectors=[666]
 *   POINT                                base=0x29B000  stride=330    count=1     sectors=[667]
 *   POWER_ON_ANIMA                       base=0x29C000  stride=25826  count=36    sectors=[668 – 894]
 *   STRIGULA_THREE_DARK                  base=0x37F000  stride=1738   count=1     sectors=[895]
 *   STRIGULA_TWO_DARK                    base=0x380000  stride=1386   count=1     sectors=[896]
 *   TEMP_DROPS_TO_NORMAL                 base=0x381000  stride=9186   count=1     sectors=[897 – 899]
 *   TEXT_BAT_HEALTH                      base=0x384000  stride=4626   count=1     sectors=[900 – 901]
 *   TEXT_BAT_TEMP                        base=0x386000  stride=4626   count=1     sectors=[902 – 903]
 *   TEXT_CHARGING_HIGH_TEMP              base=0x388000  stride=17346  count=1     sectors=[904 – 908]
 *   TEXT_CHARGING_TEMP                   base=0x38D000  stride=2718   count=1     sectors=[909]
 *   TEXT_CYCLE_INDEX                     base=0x38E000  stride=4626   count=1     sectors=[910 – 911]
 *   TEXT_DISCHARGING_HIGH_TEMP           base=0x390000  stride=17346  count=1     sectors=[912 – 916]
 *   TEXT_DISCHARGING_TEMP                base=0x395000  stride=2718   count=1     sectors=[917]
 *   TEXT_LOW_POWER                       base=0x396000  stride=5258   count=1     sectors=[918 – 919]
 *   TEXT_MINI                            base=0x398000  stride=2466   count=1     sectors=[920]
 *   TEXT_NO_ABNORMAL_RECORDS             base=0x399000  stride=5026   count=1     sectors=[921 – 922]
 *   TEXT_PRESS_5S_TO_SETTING             base=0x39B000  stride=5954   count=1     sectors=[923 – 924]
 *   TEXT_PROTECTION                      base=0x39D000  stride=17346  count=2     sectors=[925 – 933]
 *   TEXT_SAFEGUARD                       base=0x3A6000  stride=26466  count=1     sectors=[934 – 940]
 *   TEXT_STANDING_HIGH_TEMP              base=0x3AD000  stride=17346  count=1     sectors=[941 – 945]
 *   TEXT_STANDING_TEMP                   base=0x3B2000  stride=2718   count=1     sectors=[946]
 *   TEXT_TIME                            base=0x3B3000  stride=1474   count=1     sectors=[947]
 *   TEXT_VERSION_NUMBER                  base=0x3B4000  stride=1902   count=1     sectors=[948]
 *   TEXT_VOLTAGE                         base=0x3B5000  stride=1474   count=1     sectors=[949]
 *   TEXTTOTAL_VOLTAGE                    base=0x3B6000  stride=1986   count=1     sectors=[950]
 *   TIAO                                 base=0x3B7000  stride=678    count=1     sectors=[951]
 *   TITLE_ABNORMAL_TEMP                  base=0x3B8000  stride=15426  count=1     sectors=[952 – 955]
 *   TITLE_ABNORMAL_VOLTAGE               base=0x3BC000  stride=15426  count=1     sectors=[956 – 959]
 *   TITLE_CELL_VOLTAGE                   base=0x3C0000  stride=15426  count=1     sectors=[960 – 963]
 *   TITLE_SCREEN_OFF_DURATION            base=0x3C4000  stride=15426  count=1     sectors=[964 – 967]
 *   TITLE_SOFTWARE_VERSION               base=0x3C8000  stride=15426  count=1     sectors=[968 – 971]
 *   VOLT                                 base=0x3CC000  stride=682    count=1     sectors=[972]
 *   VOLT_DARK                            base=0x3CD000  stride=682    count=1     sectors=[973]
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

#define FLASH_ADDR_HEALTHY_ANIMA_BASE    (0x00000000 + 0x37000)
#define FLASH_STRIDE_HEALTHY_ANIMA       25826
#define FLASH_COUNT_HEALTHY_ANIMA        12

#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_BASE    (0x00000000 + 0x83000)
#define FLASH_STRIDE_HIGH_POWER_CHARGING_ANIMA       25826
#define FLASH_COUNT_HIGH_POWER_CHARGING_ANIMA        12

#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_BASE    (0x00000000 + 0xCF000)
#define FLASH_STRIDE_HIGH_POWER_DISCHARGING_ANIMA       25826
#define FLASH_COUNT_HIGH_POWER_DISCHARGING_ANIMA        12

#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_BASE    (0x00000000 + 0x11B000)
#define FLASH_STRIDE_HIGH_POWER_STANDBY_ANIMA       25826
#define FLASH_COUNT_HIGH_POWER_STANDBY_ANIMA        12

#define FLASH_ADDR_ICON_COUNT_DOWN_BASE    (0x00000000 + 0x167000)
#define FLASH_STRIDE_ICON_COUNT_DOWN       866
#define FLASH_COUNT_ICON_COUNT_DOWN        1

#define FLASH_ADDR_ICON_IN_1_BIG_BASE    (0x00000000 + 0x168000)
#define FLASH_STRIDE_ICON_IN_1_BIG       8386
#define FLASH_COUNT_ICON_IN_1_BIG        1

#define FLASH_ADDR_ICON_IN_1_LITTLE_BASE    (0x00000000 + 0x16B000)
#define FLASH_STRIDE_ICON_IN_1_LITTLE       2706
#define FLASH_COUNT_ICON_IN_1_LITTLE        1

#define FLASH_ADDR_ICON_IN_2_BIG_BASE    (0x00000000 + 0x16C000)
#define FLASH_STRIDE_ICON_IN_2_BIG       8386
#define FLASH_COUNT_ICON_IN_2_BIG        1

#define FLASH_ADDR_ICON_IN_2_LITTLE_BASE    (0x00000000 + 0x16F000)
#define FLASH_STRIDE_ICON_IN_2_LITTLE       2706
#define FLASH_COUNT_ICON_IN_2_LITTLE        1

#define FLASH_ADDR_ICON_IN_3_BIG_BASE    (0x00000000 + 0x170000)
#define FLASH_STRIDE_ICON_IN_3_BIG       8386
#define FLASH_COUNT_ICON_IN_3_BIG        1

#define FLASH_ADDR_ICON_IN_3_LITTLE_BASE    (0x00000000 + 0x173000)
#define FLASH_STRIDE_ICON_IN_3_LITTLE       2706
#define FLASH_COUNT_ICON_IN_3_LITTLE        1

#define FLASH_ADDR_ICON_NORMAL_1_BIG_BASE    (0x00000000 + 0x174000)
#define FLASH_STRIDE_ICON_NORMAL_1_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_1_BIG        1

#define FLASH_ADDR_ICON_NORMAL_2_BIG_BASE    (0x00000000 + 0x177000)
#define FLASH_STRIDE_ICON_NORMAL_2_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_2_BIG        1

#define FLASH_ADDR_ICON_NORMAL_3_BIG_BASE    (0x00000000 + 0x17A000)
#define FLASH_STRIDE_ICON_NORMAL_3_BIG       8226
#define FLASH_COUNT_ICON_NORMAL_3_BIG        1

#define FLASH_ADDR_ICON_OUT_1_BIG_BASE    (0x00000000 + 0x17D000)
#define FLASH_STRIDE_ICON_OUT_1_BIG       8386
#define FLASH_COUNT_ICON_OUT_1_BIG        1

#define FLASH_ADDR_ICON_OUT_1_LITTLE_BASE    (0x00000000 + 0x180000)
#define FLASH_STRIDE_ICON_OUT_1_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_1_LITTLE        1

#define FLASH_ADDR_ICON_OUT_2_BIG_BASE    (0x00000000 + 0x181000)
#define FLASH_STRIDE_ICON_OUT_2_BIG       8386
#define FLASH_COUNT_ICON_OUT_2_BIG        1

#define FLASH_ADDR_ICON_OUT_2_LITTLE_BASE    (0x00000000 + 0x184000)
#define FLASH_STRIDE_ICON_OUT_2_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_2_LITTLE        1

#define FLASH_ADDR_ICON_OUT_3_BIG_BASE    (0x00000000 + 0x185000)
#define FLASH_STRIDE_ICON_OUT_3_BIG       8386
#define FLASH_COUNT_ICON_OUT_3_BIG        1

#define FLASH_ADDR_ICON_OUT_3_LITTLE_BASE    (0x00000000 + 0x188000)
#define FLASH_STRIDE_ICON_OUT_3_LITTLE       2706
#define FLASH_COUNT_ICON_OUT_3_LITTLE        1

#define FLASH_ADDR_ICON_PROTECTION_BASE    (0x00000000 + 0x189000)
#define FLASH_STRIDE_ICON_PROTECTION       12866
#define FLASH_COUNT_ICON_PROTECTION        1

#define FLASH_ADDR_ICON_SAFE_BASE    (0x00000000 + 0x18D000)
#define FLASH_STRIDE_ICON_SAFE       12866
#define FLASH_COUNT_ICON_SAFE        1

#define FLASH_ADDR_ICON_TEMP_HIGH_BASE    (0x00000000 + 0x191000)
#define FLASH_STRIDE_ICON_TEMP_HIGH       12866
#define FLASH_COUNT_ICON_TEMP_HIGH        1

#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_BASE    (0x00000000 + 0x195000)
#define FLASH_STRIDE_LOW_POWER_CHARGING_ANIMA       25826
#define FLASH_COUNT_LOW_POWER_CHARGING_ANIMA        12

#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_BASE    (0x00000000 + 0x1E1000)
#define FLASH_STRIDE_LOW_POWER_DISCHARGING_ANIMA       25826
#define FLASH_COUNT_LOW_POWER_DISCHARGING_ANIMA        12

#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_BASE    (0x00000000 + 0x22D000)
#define FLASH_STRIDE_LOW_POWER_STANDBY_ANIMA       25826
#define FLASH_COUNT_LOW_POWER_STANDBY_ANIMA        12

#define FLASH_ADDR_NUM_12_BASE    (0x00000000 + 0x279000)
#define FLASH_STRIDE_NUM_12       346
#define FLASH_COUNT_NUM_12        40

#define FLASH_ADDR_NUM_16_BASE    (0x00000000 + 0x27D000)
#define FLASH_STRIDE_NUM_16       770
#define FLASH_COUNT_NUM_16        40

#define FLASH_ADDR_NUM_18_BASE    (0x00000000 + 0x285000)
#define FLASH_STRIDE_NUM_18       570
#define FLASH_COUNT_NUM_18        10

#define FLASH_ADDR_NUM_18_HOUR_BASE    (0x00000000 + 0x287000)
#define FLASH_STRIDE_NUM_18_HOUR       570
#define FLASH_COUNT_NUM_18_HOUR        1

#define FLASH_ADDR_NUM_18_MINUTE_BASE    (0x00000000 + 0x288000)
#define FLASH_STRIDE_NUM_18_MINUTE       906
#define FLASH_COUNT_NUM_18_MINUTE        1

#define FLASH_ADDR_NUM_20_BASE    (0x00000000 + 0x289000)
#define FLASH_STRIDE_NUM_20       594
#define FLASH_COUNT_NUM_20        10

#define FLASH_ADDR_NUM_20_1_NULL_BASE    (0x00000000 + 0x28B000)
#define FLASH_STRIDE_NUM_20_1_NULL       594
#define FLASH_COUNT_NUM_20_1_NULL        1

#define FLASH_ADDR_NUM_20_1_BASE    (0x00000000 + 0x28C000)
#define FLASH_STRIDE_NUM_20_1       594
#define FLASH_COUNT_NUM_20_1        1

#define FLASH_ADDR_NUM_48_0_WHITE_BASE    (0x00000000 + 0x28D000)
#define FLASH_STRIDE_NUM_48_0_WHITE       3330
#define FLASH_COUNT_NUM_48_0_WHITE        1

#define FLASH_ADDR_NUM_48_1_WHITE_BASE    (0x00000000 + 0x28E000)
#define FLASH_STRIDE_NUM_48_1_WHITE       2178
#define FLASH_COUNT_NUM_48_1_WHITE        1

#define FLASH_ADDR_NUM_48_2_WHITE_BASE    (0x00000000 + 0x28F000)
#define FLASH_STRIDE_NUM_48_2_WHITE       3330
#define FLASH_COUNT_NUM_48_2_WHITE        1

#define FLASH_ADDR_NUM_48_3_WHITE_BASE    (0x00000000 + 0x290000)
#define FLASH_STRIDE_NUM_48_3_WHITE       3330
#define FLASH_COUNT_NUM_48_3_WHITE        1

#define FLASH_ADDR_NUM_48_4_WHITE_BASE    (0x00000000 + 0x291000)
#define FLASH_STRIDE_NUM_48_4_WHITE       3330
#define FLASH_COUNT_NUM_48_4_WHITE        1

#define FLASH_ADDR_NUM_48_5_WHITE_BASE    (0x00000000 + 0x292000)
#define FLASH_STRIDE_NUM_48_5_WHITE       3330
#define FLASH_COUNT_NUM_48_5_WHITE        1

#define FLASH_ADDR_NUM_48_6_WHITE_BASE    (0x00000000 + 0x293000)
#define FLASH_STRIDE_NUM_48_6_WHITE       3330
#define FLASH_COUNT_NUM_48_6_WHITE        1

#define FLASH_ADDR_NUM_48_7_WHITE_BASE    (0x00000000 + 0x294000)
#define FLASH_STRIDE_NUM_48_7_WHITE       3330
#define FLASH_COUNT_NUM_48_7_WHITE        1

#define FLASH_ADDR_NUM_48_8_WHITE_BASE    (0x00000000 + 0x295000)
#define FLASH_STRIDE_NUM_48_8_WHITE       3330
#define FLASH_COUNT_NUM_48_8_WHITE        1

#define FLASH_ADDR_NUM_48_9_WHITE_BASE    (0x00000000 + 0x296000)
#define FLASH_STRIDE_NUM_48_9_WHITE       3330
#define FLASH_COUNT_NUM_48_9_WHITE        1

#define FLASH_ADDR_NUM_48_PERCENT_WHITE_BASE    (0x00000000 + 0x297000)
#define FLASH_STRIDE_NUM_48_PERCENT_WHITE       3330
#define FLASH_COUNT_NUM_48_PERCENT_WHITE        1

#define FLASH_ADDR_OBLIQUE_LINE_BASE    (0x00000000 + 0x298000)
#define FLASH_STRIDE_OBLIQUE_LINE       770
#define FLASH_COUNT_OBLIQUE_LINE        1

#define FLASH_ADDR_OBLIQUE_LINE_DARK_BASE    (0x00000000 + 0x299000)
#define FLASH_STRIDE_OBLIQUE_LINE_DARK       770
#define FLASH_COUNT_OBLIQUE_LINE_DARK        1

#define FLASH_ADDR_PERCENT_BASE    (0x00000000 + 0x29A000)
#define FLASH_STRIDE_PERCENT       682
#define FLASH_COUNT_PERCENT        1

#define FLASH_ADDR_POINT_BASE    (0x00000000 + 0x29B000)
#define FLASH_STRIDE_POINT       330
#define FLASH_COUNT_POINT        1

#define FLASH_ADDR_POWER_ON_ANIMA_BASE    (0x00000000 + 0x29C000)
#define FLASH_STRIDE_POWER_ON_ANIMA       25826
#define FLASH_COUNT_POWER_ON_ANIMA        36

#define FLASH_ADDR_STRIGULA_THREE_DARK_BASE    (0x00000000 + 0x37F000)
#define FLASH_STRIDE_STRIGULA_THREE_DARK       1738
#define FLASH_COUNT_STRIGULA_THREE_DARK        1

#define FLASH_ADDR_STRIGULA_TWO_DARK_BASE    (0x00000000 + 0x380000)
#define FLASH_STRIDE_STRIGULA_TWO_DARK       1386
#define FLASH_COUNT_STRIGULA_TWO_DARK        1

#define FLASH_ADDR_TEMP_DROPS_TO_NORMAL_BASE    (0x00000000 + 0x381000)
#define FLASH_STRIDE_TEMP_DROPS_TO_NORMAL       9186
#define FLASH_COUNT_TEMP_DROPS_TO_NORMAL        1

#define FLASH_ADDR_TEXT_BAT_HEALTH_BASE    (0x00000000 + 0x384000)
#define FLASH_STRIDE_TEXT_BAT_HEALTH       4626
#define FLASH_COUNT_TEXT_BAT_HEALTH        1

#define FLASH_ADDR_TEXT_BAT_TEMP_BASE    (0x00000000 + 0x386000)
#define FLASH_STRIDE_TEXT_BAT_TEMP       4626
#define FLASH_COUNT_TEXT_BAT_TEMP        1

#define FLASH_ADDR_TEXT_CHARGING_HIGH_TEMP_BASE    (0x00000000 + 0x388000)
#define FLASH_STRIDE_TEXT_CHARGING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_CHARGING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_CHARGING_TEMP_BASE    (0x00000000 + 0x38D000)
#define FLASH_STRIDE_TEXT_CHARGING_TEMP       2718
#define FLASH_COUNT_TEXT_CHARGING_TEMP        1

#define FLASH_ADDR_TEXT_CYCLE_INDEX_BASE    (0x00000000 + 0x38E000)
#define FLASH_STRIDE_TEXT_CYCLE_INDEX       4626
#define FLASH_COUNT_TEXT_CYCLE_INDEX        1

#define FLASH_ADDR_TEXT_DISCHARGING_HIGH_TEMP_BASE    (0x00000000 + 0x390000)
#define FLASH_STRIDE_TEXT_DISCHARGING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_DISCHARGING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_DISCHARGING_TEMP_BASE    (0x00000000 + 0x395000)
#define FLASH_STRIDE_TEXT_DISCHARGING_TEMP       2718
#define FLASH_COUNT_TEXT_DISCHARGING_TEMP        1

#define FLASH_ADDR_TEXT_LOW_POWER_BASE    (0x00000000 + 0x396000)
#define FLASH_STRIDE_TEXT_LOW_POWER       5258
#define FLASH_COUNT_TEXT_LOW_POWER        1

#define FLASH_ADDR_TEXT_MINI_BASE    (0x00000000 + 0x398000)
#define FLASH_STRIDE_TEXT_MINI       2466
#define FLASH_COUNT_TEXT_MINI        1

#define FLASH_ADDR_TEXT_NO_ABNORMAL_RECORDS_BASE    (0x00000000 + 0x399000)
#define FLASH_STRIDE_TEXT_NO_ABNORMAL_RECORDS       5026
#define FLASH_COUNT_TEXT_NO_ABNORMAL_RECORDS        1

#define FLASH_ADDR_TEXT_PRESS_5S_TO_SETTING_BASE    (0x00000000 + 0x39B000)
#define FLASH_STRIDE_TEXT_PRESS_5S_TO_SETTING       5954
#define FLASH_COUNT_TEXT_PRESS_5S_TO_SETTING        1

#define FLASH_ADDR_TEXT_PROTECTION_BASE    (0x00000000 + 0x39D000)
#define FLASH_STRIDE_TEXT_PROTECTION       17346
#define FLASH_COUNT_TEXT_PROTECTION        2

#define FLASH_ADDR_TEXT_SAFEGUARD_BASE    (0x00000000 + 0x3A6000)
#define FLASH_STRIDE_TEXT_SAFEGUARD       26466
#define FLASH_COUNT_TEXT_SAFEGUARD        1

#define FLASH_ADDR_TEXT_STANDING_HIGH_TEMP_BASE    (0x00000000 + 0x3AD000)
#define FLASH_STRIDE_TEXT_STANDING_HIGH_TEMP       17346
#define FLASH_COUNT_TEXT_STANDING_HIGH_TEMP        1

#define FLASH_ADDR_TEXT_STANDING_TEMP_BASE    (0x00000000 + 0x3B2000)
#define FLASH_STRIDE_TEXT_STANDING_TEMP       2718
#define FLASH_COUNT_TEXT_STANDING_TEMP        1

#define FLASH_ADDR_TEXT_TIME_BASE    (0x00000000 + 0x3B3000)
#define FLASH_STRIDE_TEXT_TIME       1474
#define FLASH_COUNT_TEXT_TIME        1

#define FLASH_ADDR_TEXT_VERSION_NUMBER_BASE    (0x00000000 + 0x3B4000)
#define FLASH_STRIDE_TEXT_VERSION_NUMBER       1902
#define FLASH_COUNT_TEXT_VERSION_NUMBER        1

#define FLASH_ADDR_TEXT_VOLTAGE_BASE    (0x00000000 + 0x3B5000)
#define FLASH_STRIDE_TEXT_VOLTAGE       1474
#define FLASH_COUNT_TEXT_VOLTAGE        1

#define FLASH_ADDR_TEXTTOTAL_VOLTAGE_BASE    (0x00000000 + 0x3B6000)
#define FLASH_STRIDE_TEXTTOTAL_VOLTAGE       1986
#define FLASH_COUNT_TEXTTOTAL_VOLTAGE        1

#define FLASH_ADDR_TIAO_BASE    (0x00000000 + 0x3B7000)
#define FLASH_STRIDE_TIAO       678
#define FLASH_COUNT_TIAO        1

#define FLASH_ADDR_TITLE_ABNORMAL_TEMP_BASE    (0x00000000 + 0x3B8000)
#define FLASH_STRIDE_TITLE_ABNORMAL_TEMP       15426
#define FLASH_COUNT_TITLE_ABNORMAL_TEMP        1

#define FLASH_ADDR_TITLE_ABNORMAL_VOLTAGE_BASE    (0x00000000 + 0x3BC000)
#define FLASH_STRIDE_TITLE_ABNORMAL_VOLTAGE       15426
#define FLASH_COUNT_TITLE_ABNORMAL_VOLTAGE        1

#define FLASH_ADDR_TITLE_CELL_VOLTAGE_BASE    (0x00000000 + 0x3C0000)
#define FLASH_STRIDE_TITLE_CELL_VOLTAGE       15426
#define FLASH_COUNT_TITLE_CELL_VOLTAGE        1

#define FLASH_ADDR_TITLE_SCREEN_OFF_DURATION_BASE    (0x00000000 + 0x3C4000)
#define FLASH_STRIDE_TITLE_SCREEN_OFF_DURATION       15426
#define FLASH_COUNT_TITLE_SCREEN_OFF_DURATION        1

#define FLASH_ADDR_TITLE_SOFTWARE_VERSION_BASE    (0x00000000 + 0x3C8000)
#define FLASH_STRIDE_TITLE_SOFTWARE_VERSION       15426
#define FLASH_COUNT_TITLE_SOFTWARE_VERSION        1

#define FLASH_ADDR_VOLT_BASE    (0x00000000 + 0x3CC000)
#define FLASH_STRIDE_VOLT       682
#define FLASH_COUNT_VOLT        1

#define FLASH_ADDR_VOLT_DARK_BASE    (0x00000000 + 0x3CD000)
#define FLASH_STRIDE_VOLT_DARK       682
#define FLASH_COUNT_VOLT_DARK        1


/*
 * Per-image index macros — for named access within a category.
 *   addr = FLASH_ADDR_<CAT>_BASE + FLASH_IDX_<CAT>_<ITEM> * FLASH_STRIDE_<CAT>
 */
#define FLASH_IDX_HEALTHY_ANIMA_0  0
#define FLASH_IDX_HEALTHY_ANIMA_1  1
#define FLASH_IDX_HEALTHY_ANIMA_10  2
#define FLASH_IDX_HEALTHY_ANIMA_11  3
#define FLASH_IDX_HEALTHY_ANIMA_2  4
#define FLASH_IDX_HEALTHY_ANIMA_3  5
#define FLASH_IDX_HEALTHY_ANIMA_4  6
#define FLASH_IDX_HEALTHY_ANIMA_5  7
#define FLASH_IDX_HEALTHY_ANIMA_6  8
#define FLASH_IDX_HEALTHY_ANIMA_7  9
#define FLASH_IDX_HEALTHY_ANIMA_8  10
#define FLASH_IDX_HEALTHY_ANIMA_9  11

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

#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_0  0
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_1  1
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_10  2
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_11  3
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_2  4
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_3  5
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_4  6
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_5  7
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_6  8
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_7  9
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_8  10
#define FLASH_IDX_HIGH_POWER_DISCHARGING_ANIMA_9  11

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

#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_0  0
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_1  1
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_10  2
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_11  3
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_2  4
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_3  5
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_4  6
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_5  7
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_6  8
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_7  9
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_8  10
#define FLASH_IDX_LOW_POWER_DISCHARGING_ANIMA_9  11

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

#define FLASH_IDX_POWER_ON_ANIMA_0  0
#define FLASH_IDX_POWER_ON_ANIMA_1  1
#define FLASH_IDX_POWER_ON_ANIMA_10  2
#define FLASH_IDX_POWER_ON_ANIMA_11  3
#define FLASH_IDX_POWER_ON_ANIMA_12  4
#define FLASH_IDX_POWER_ON_ANIMA_13  5
#define FLASH_IDX_POWER_ON_ANIMA_14  6
#define FLASH_IDX_POWER_ON_ANIMA_15  7
#define FLASH_IDX_POWER_ON_ANIMA_16  8
#define FLASH_IDX_POWER_ON_ANIMA_17  9
#define FLASH_IDX_POWER_ON_ANIMA_18  10
#define FLASH_IDX_POWER_ON_ANIMA_19  11
#define FLASH_IDX_POWER_ON_ANIMA_2  12
#define FLASH_IDX_POWER_ON_ANIMA_20  13
#define FLASH_IDX_POWER_ON_ANIMA_21  14
#define FLASH_IDX_POWER_ON_ANIMA_22  15
#define FLASH_IDX_POWER_ON_ANIMA_23  16
#define FLASH_IDX_POWER_ON_ANIMA_24  17
#define FLASH_IDX_POWER_ON_ANIMA_25  18
#define FLASH_IDX_POWER_ON_ANIMA_26  19
#define FLASH_IDX_POWER_ON_ANIMA_27  20
#define FLASH_IDX_POWER_ON_ANIMA_28  21
#define FLASH_IDX_POWER_ON_ANIMA_29  22
#define FLASH_IDX_POWER_ON_ANIMA_3  23
#define FLASH_IDX_POWER_ON_ANIMA_30  24
#define FLASH_IDX_POWER_ON_ANIMA_31  25
#define FLASH_IDX_POWER_ON_ANIMA_32  26
#define FLASH_IDX_POWER_ON_ANIMA_33  27
#define FLASH_IDX_POWER_ON_ANIMA_34  28
#define FLASH_IDX_POWER_ON_ANIMA_35  29
#define FLASH_IDX_POWER_ON_ANIMA_4  30
#define FLASH_IDX_POWER_ON_ANIMA_5  31
#define FLASH_IDX_POWER_ON_ANIMA_6  32
#define FLASH_IDX_POWER_ON_ANIMA_7  33
#define FLASH_IDX_POWER_ON_ANIMA_8  34
#define FLASH_IDX_POWER_ON_ANIMA_9  35

#define FLASH_IDX_TEXT_PROTECTION_1  0
#define FLASH_IDX_TEXT_PROTECTION_2  1


/*
 * Absolute flash addresses and sizes for every image.
 */
#define FLASH_ADDR_AMPERE                           (0x00000000 + 0x0000)
#define FLASH_SIZE_AMPERE                           682
#define FLASH_ADDR_AMPERE_DARK                      (0x00000000 + 0x1000)
#define FLASH_SIZE_AMPERE_DARK                      682
#define FLASH_ADDR_BTN_1800S                        (0x00000000 + 0x2000)
#define FLASH_SIZE_BTN_1800S                        6338
#define FLASH_ADDR_BTN_1800S_DARK                   (0x00000000 + 0x4000)
#define FLASH_SIZE_BTN_1800S_DARK                   6338
#define FLASH_ADDR_BTN_300S                         (0x00000000 + 0x6000)
#define FLASH_SIZE_BTN_300S                         6338
#define FLASH_ADDR_BTN_300S_DARK                    (0x00000000 + 0x8000)
#define FLASH_SIZE_BTN_300S_DARK                    6338
#define FLASH_ADDR_BTN_30S                          (0x00000000 + 0xA000)
#define FLASH_SIZE_BTN_30S                          6338
#define FLASH_ADDR_BTN_30S_DARK                     (0x00000000 + 0xC000)
#define FLASH_SIZE_BTN_30S_DARK                     6338
#define FLASH_ADDR_BTN_60S                          (0x00000000 + 0xE000)
#define FLASH_SIZE_BTN_60S                          6338
#define FLASH_ADDR_BTN_60S_DARK                     (0x00000000 + 0x10000)
#define FLASH_SIZE_BTN_60S_DARK                     6338
#define FLASH_ADDR_CELL_MODEL                       (0x00000000 + 0x12000)
#define FLASH_SIZE_CELL_MODEL                       2562
#define FLASH_ADDR_CI                               (0x00000000 + 0x13000)
#define FLASH_SIZE_CI                               858
#define FLASH_ADDR_DEGREE_CENTIGRADE                (0x00000000 + 0x14000)
#define FLASH_SIZE_DEGREE_CENTIGRADE                1122
#define FLASH_ADDR_DI                               (0x00000000 + 0x15000)
#define FLASH_SIZE_DI                               678
#define FLASH_ADDR_DOUBLE_CLICK_SWITCH              (0x00000000 + 0x16000)
#define FLASH_SIZE_DOUBLE_CLICK_SWITCH              9186
#define FLASH_ADDR_DOUHAO                           (0x00000000 + 0x19000)
#define FLASH_SIZE_DOUHAO                           450
#define FLASH_ADDR_EMOJI_CHARGING                   (0x00000000 + 0x1A000)
#define FLASH_SIZE_EMOJI_CHARGING                   25826
#define FLASH_ADDR_EMOJI_HEALTHY                    (0x00000000 + 0x21000)
#define FLASH_SIZE_EMOJI_HEALTHY                    25826
#define FLASH_ADDR_EMOJI_LOW_POWER                  (0x00000000 + 0x28000)
#define FLASH_SIZE_EMOJI_LOW_POWER                  25826
#define FLASH_ADDR_EMOJI_NORMAL                     (0x00000000 + 0x2F000)
#define FLASH_SIZE_EMOJI_NORMAL                     25826
#define FLASH_ADDR_GONG                             (0x00000000 + 0x36000)
#define FLASH_SIZE_GONG                             678
#define FLASH_ADDR_HEALTHY_ANIMA_0                  (0x00000000 + 0x37000)
#define FLASH_SIZE_HEALTHY_ANIMA_0                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_1                  (0x00000000 + 0x3D4E2)
#define FLASH_SIZE_HEALTHY_ANIMA_1                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_10                 (0x00000000 + 0x439C4)
#define FLASH_SIZE_HEALTHY_ANIMA_10                 25826
#define FLASH_ADDR_HEALTHY_ANIMA_11                 (0x00000000 + 0x49EA6)
#define FLASH_SIZE_HEALTHY_ANIMA_11                 25826
#define FLASH_ADDR_HEALTHY_ANIMA_2                  (0x00000000 + 0x50388)
#define FLASH_SIZE_HEALTHY_ANIMA_2                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_3                  (0x00000000 + 0x5686A)
#define FLASH_SIZE_HEALTHY_ANIMA_3                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_4                  (0x00000000 + 0x5CD4C)
#define FLASH_SIZE_HEALTHY_ANIMA_4                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_5                  (0x00000000 + 0x6322E)
#define FLASH_SIZE_HEALTHY_ANIMA_5                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_6                  (0x00000000 + 0x69710)
#define FLASH_SIZE_HEALTHY_ANIMA_6                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_7                  (0x00000000 + 0x6FBF2)
#define FLASH_SIZE_HEALTHY_ANIMA_7                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_8                  (0x00000000 + 0x760D4)
#define FLASH_SIZE_HEALTHY_ANIMA_8                  25826
#define FLASH_ADDR_HEALTHY_ANIMA_9                  (0x00000000 + 0x7C5B6)
#define FLASH_SIZE_HEALTHY_ANIMA_9                  25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_0      (0x00000000 + 0x83000)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_0      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_1      (0x00000000 + 0x894E2)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_1      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_10     (0x00000000 + 0x8F9C4)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_10     25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_11     (0x00000000 + 0x95EA6)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_11     25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_2      (0x00000000 + 0x9C388)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_2      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_3      (0x00000000 + 0xA286A)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_3      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_4      (0x00000000 + 0xA8D4C)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_4      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_5      (0x00000000 + 0xAF22E)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_5      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_6      (0x00000000 + 0xB5710)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_6      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_7      (0x00000000 + 0xBBBF2)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_7      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_8      (0x00000000 + 0xC20D4)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_8      25826
#define FLASH_ADDR_HIGH_POWER_CHARGING_ANIMA_9      (0x00000000 + 0xC85B6)
#define FLASH_SIZE_HIGH_POWER_CHARGING_ANIMA_9      25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_0   (0x00000000 + 0xCF000)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_0   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_1   (0x00000000 + 0xD54E2)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_1   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_10  (0x00000000 + 0xDB9C4)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_10  25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_11  (0x00000000 + 0xE1EA6)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_11  25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_2   (0x00000000 + 0xE8388)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_2   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_3   (0x00000000 + 0xEE86A)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_3   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_4   (0x00000000 + 0xF4D4C)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_4   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_5   (0x00000000 + 0xFB22E)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_5   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_6   (0x00000000 + 0x101710)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_6   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_7   (0x00000000 + 0x107BF2)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_7   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_8   (0x00000000 + 0x10E0D4)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_8   25826
#define FLASH_ADDR_HIGH_POWER_DISCHARGING_ANIMA_9   (0x00000000 + 0x1145B6)
#define FLASH_SIZE_HIGH_POWER_DISCHARGING_ANIMA_9   25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_0       (0x00000000 + 0x11B000)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_0       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_1       (0x00000000 + 0x1214E2)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_1       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_10      (0x00000000 + 0x1279C4)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_10      25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_11      (0x00000000 + 0x12DEA6)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_11      25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_2       (0x00000000 + 0x134388)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_2       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_3       (0x00000000 + 0x13A86A)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_3       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_4       (0x00000000 + 0x140D4C)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_4       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_5       (0x00000000 + 0x14722E)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_5       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_6       (0x00000000 + 0x14D710)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_6       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_7       (0x00000000 + 0x153BF2)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_7       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_8       (0x00000000 + 0x15A0D4)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_8       25826
#define FLASH_ADDR_HIGH_POWER_STANDBY_ANIMA_9       (0x00000000 + 0x1605B6)
#define FLASH_SIZE_HIGH_POWER_STANDBY_ANIMA_9       25826
#define FLASH_ADDR_ICON_COUNT_DOWN                  (0x00000000 + 0x167000)
#define FLASH_SIZE_ICON_COUNT_DOWN                  866
#define FLASH_ADDR_ICON_IN_1_BIG                    (0x00000000 + 0x168000)
#define FLASH_SIZE_ICON_IN_1_BIG                    8386
#define FLASH_ADDR_ICON_IN_1_LITTLE                 (0x00000000 + 0x16B000)
#define FLASH_SIZE_ICON_IN_1_LITTLE                 2706
#define FLASH_ADDR_ICON_IN_2_BIG                    (0x00000000 + 0x16C000)
#define FLASH_SIZE_ICON_IN_2_BIG                    8386
#define FLASH_ADDR_ICON_IN_2_LITTLE                 (0x00000000 + 0x16F000)
#define FLASH_SIZE_ICON_IN_2_LITTLE                 2706
#define FLASH_ADDR_ICON_IN_3_BIG                    (0x00000000 + 0x170000)
#define FLASH_SIZE_ICON_IN_3_BIG                    8386
#define FLASH_ADDR_ICON_IN_3_LITTLE                 (0x00000000 + 0x173000)
#define FLASH_SIZE_ICON_IN_3_LITTLE                 2706
#define FLASH_ADDR_ICON_NORMAL_1_BIG                (0x00000000 + 0x174000)
#define FLASH_SIZE_ICON_NORMAL_1_BIG                8226
#define FLASH_ADDR_ICON_NORMAL_2_BIG                (0x00000000 + 0x177000)
#define FLASH_SIZE_ICON_NORMAL_2_BIG                8226
#define FLASH_ADDR_ICON_NORMAL_3_BIG                (0x00000000 + 0x17A000)
#define FLASH_SIZE_ICON_NORMAL_3_BIG                8226
#define FLASH_ADDR_ICON_OUT_1_BIG                   (0x00000000 + 0x17D000)
#define FLASH_SIZE_ICON_OUT_1_BIG                   8386
#define FLASH_ADDR_ICON_OUT_1_LITTLE                (0x00000000 + 0x180000)
#define FLASH_SIZE_ICON_OUT_1_LITTLE                2706
#define FLASH_ADDR_ICON_OUT_2_BIG                   (0x00000000 + 0x181000)
#define FLASH_SIZE_ICON_OUT_2_BIG                   8386
#define FLASH_ADDR_ICON_OUT_2_LITTLE                (0x00000000 + 0x184000)
#define FLASH_SIZE_ICON_OUT_2_LITTLE                2706
#define FLASH_ADDR_ICON_OUT_3_BIG                   (0x00000000 + 0x185000)
#define FLASH_SIZE_ICON_OUT_3_BIG                   8386
#define FLASH_ADDR_ICON_OUT_3_LITTLE                (0x00000000 + 0x188000)
#define FLASH_SIZE_ICON_OUT_3_LITTLE                2706
#define FLASH_ADDR_ICON_PROTECTION                  (0x00000000 + 0x189000)
#define FLASH_SIZE_ICON_PROTECTION                  12866
#define FLASH_ADDR_ICON_SAFE                        (0x00000000 + 0x18D000)
#define FLASH_SIZE_ICON_SAFE                        12866
#define FLASH_ADDR_ICON_TEMP_HIGH                   (0x00000000 + 0x191000)
#define FLASH_SIZE_ICON_TEMP_HIGH                   12866
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_0       (0x00000000 + 0x195000)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_0       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_1       (0x00000000 + 0x19B4E2)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_1       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_10      (0x00000000 + 0x1A19C4)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_10      25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_11      (0x00000000 + 0x1A7EA6)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_11      25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_2       (0x00000000 + 0x1AE388)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_2       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_3       (0x00000000 + 0x1B486A)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_3       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_4       (0x00000000 + 0x1BAD4C)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_4       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_5       (0x00000000 + 0x1C122E)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_5       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_6       (0x00000000 + 0x1C7710)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_6       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_7       (0x00000000 + 0x1CDBF2)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_7       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_8       (0x00000000 + 0x1D40D4)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_8       25826
#define FLASH_ADDR_LOW_POWER_CHARGING_ANIMA_9       (0x00000000 + 0x1DA5B6)
#define FLASH_SIZE_LOW_POWER_CHARGING_ANIMA_9       25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_0    (0x00000000 + 0x1E1000)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_0    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_1    (0x00000000 + 0x1E74E2)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_1    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_10   (0x00000000 + 0x1ED9C4)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_10   25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_11   (0x00000000 + 0x1F3EA6)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_11   25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_2    (0x00000000 + 0x1FA388)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_2    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_3    (0x00000000 + 0x20086A)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_3    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_4    (0x00000000 + 0x206D4C)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_4    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_5    (0x00000000 + 0x20D22E)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_5    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_6    (0x00000000 + 0x213710)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_6    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_7    (0x00000000 + 0x219BF2)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_7    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_8    (0x00000000 + 0x2200D4)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_8    25826
#define FLASH_ADDR_LOW_POWER_DISCHARGING_ANIMA_9    (0x00000000 + 0x2265B6)
#define FLASH_SIZE_LOW_POWER_DISCHARGING_ANIMA_9    25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_0        (0x00000000 + 0x22D000)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_0        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_1        (0x00000000 + 0x2334E2)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_1        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_10       (0x00000000 + 0x2399C4)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_10       25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_11       (0x00000000 + 0x23FEA6)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_11       25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_2        (0x00000000 + 0x246388)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_2        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_3        (0x00000000 + 0x24C86A)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_3        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_4        (0x00000000 + 0x252D4C)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_4        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_5        (0x00000000 + 0x25922E)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_5        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_6        (0x00000000 + 0x25F710)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_6        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_7        (0x00000000 + 0x265BF2)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_7        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_8        (0x00000000 + 0x26C0D4)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_8        25826
#define FLASH_ADDR_LOW_POWER_STANDBY_ANIMA_9        (0x00000000 + 0x2725B6)
#define FLASH_SIZE_LOW_POWER_STANDBY_ANIMA_9        25826
#define FLASH_ADDR_NUM_12_0                         (0x00000000 + 0x279000)
#define FLASH_SIZE_NUM_12_0                         226
#define FLASH_ADDR_NUM_12_1                         (0x00000000 + 0x27915A)
#define FLASH_SIZE_NUM_12_1                         186
#define FLASH_ADDR_NUM_12_2                         (0x00000000 + 0x2792B4)
#define FLASH_SIZE_NUM_12_2                         226
#define FLASH_ADDR_NUM_12_3                         (0x00000000 + 0x27940E)
#define FLASH_SIZE_NUM_12_3                         226
#define FLASH_ADDR_NUM_12_4                         (0x00000000 + 0x279568)
#define FLASH_SIZE_NUM_12_4                         266
#define FLASH_ADDR_NUM_12_5                         (0x00000000 + 0x2796C2)
#define FLASH_SIZE_NUM_12_5                         226
#define FLASH_ADDR_NUM_12_6                         (0x00000000 + 0x27981C)
#define FLASH_SIZE_NUM_12_6                         226
#define FLASH_ADDR_NUM_12_7                         (0x00000000 + 0x279976)
#define FLASH_SIZE_NUM_12_7                         226
#define FLASH_ADDR_NUM_12_8                         (0x00000000 + 0x279AD0)
#define FLASH_SIZE_NUM_12_8                         226
#define FLASH_ADDR_NUM_12_9                         (0x00000000 + 0x279C2A)
#define FLASH_SIZE_NUM_12_9                         226
#define FLASH_ADDR_NUM_12                           (0x00000000 + 0x279D84)
#define FLASH_SIZE_NUM_12                           226
#define FLASH_ADDR_NUM_12_A                         (0x00000000 + 0x279EDE)
#define FLASH_SIZE_NUM_12_A                         266
#define FLASH_ADDR_NUM_12_B                         (0x00000000 + 0x27A038)
#define FLASH_SIZE_NUM_12_B                         226
#define FLASH_ADDR_NUM_12_C                         (0x00000000 + 0x27A192)
#define FLASH_SIZE_NUM_12_C                         266
#define FLASH_ADDR_NUM_12_D                         (0x00000000 + 0x27A2EC)
#define FLASH_SIZE_NUM_12_D                         266
#define FLASH_ADDR_NUM_12_E                         (0x00000000 + 0x27A446)
#define FLASH_SIZE_NUM_12_E                         226
#define FLASH_ADDR_NUM_12_F                         (0x00000000 + 0x27A5A0)
#define FLASH_SIZE_NUM_12_F                         226
#define FLASH_ADDR_NUM_12_G                         (0x00000000 + 0x27A6FA)
#define FLASH_SIZE_NUM_12_G                         266
#define FLASH_ADDR_NUM_12_H                         (0x00000000 + 0x27A854)
#define FLASH_SIZE_NUM_12_H                         266
#define FLASH_ADDR_NUM_12_I                         (0x00000000 + 0x27A9AE)
#define FLASH_SIZE_NUM_12_I                         186
#define FLASH_ADDR_NUM_12_J                         (0x00000000 + 0x27AB08)
#define FLASH_SIZE_NUM_12_J                         226
#define FLASH_ADDR_NUM_12_K                         (0x00000000 + 0x27AC62)
#define FLASH_SIZE_NUM_12_K                         226
#define FLASH_ADDR_NUM_12_L                         (0x00000000 + 0x27ADBC)
#define FLASH_SIZE_NUM_12_L                         226
#define FLASH_ADDR_NUM_12_M                         (0x00000000 + 0x27AF16)
#define FLASH_SIZE_NUM_12_M                         306
#define FLASH_ADDR_NUM_12_N                         (0x00000000 + 0x27B070)
#define FLASH_SIZE_NUM_12_N                         266
#define FLASH_ADDR_NUM_12_O                         (0x00000000 + 0x27B1CA)
#define FLASH_SIZE_NUM_12_O                         266
#define FLASH_ADDR_NUM_12_P                         (0x00000000 + 0x27B324)
#define FLASH_SIZE_NUM_12_P                         226
#define FLASH_ADDR_NUM_12_Q                         (0x00000000 + 0x27B47E)
#define FLASH_SIZE_NUM_12_Q                         266
#define FLASH_ADDR_NUM_12_R                         (0x00000000 + 0x27B5D8)
#define FLASH_SIZE_NUM_12_R                         226
#define FLASH_ADDR_NUM_12_S                         (0x00000000 + 0x27B732)
#define FLASH_SIZE_NUM_12_S                         226
#define FLASH_ADDR_NUM_12_T                         (0x00000000 + 0x27B88C)
#define FLASH_SIZE_NUM_12_T                         226
#define FLASH_ADDR_NUM_12_U                         (0x00000000 + 0x27B9E6)
#define FLASH_SIZE_NUM_12_U                         266
#define FLASH_ADDR_NUM_12_V                         (0x00000000 + 0x27BB40)
#define FLASH_SIZE_NUM_12_V                         266
#define FLASH_ADDR_NUM_12_W                         (0x00000000 + 0x27BC9A)
#define FLASH_SIZE_NUM_12_W                         346
#define FLASH_ADDR_NUM_12_X                         (0x00000000 + 0x27BDF4)
#define FLASH_SIZE_NUM_12_X                         266
#define FLASH_ADDR_NUM_12_Y                         (0x00000000 + 0x27BF4E)
#define FLASH_SIZE_NUM_12_Y                         266
#define FLASH_ADDR_NUM_12_Z                         (0x00000000 + 0x27C0A8)
#define FLASH_SIZE_NUM_12_Z                         266
#define FLASH_ADDR_NUM_12_Z_COLON                   (0x00000000 + 0x27C202)
#define FLASH_SIZE_NUM_12_Z_COLON                   186
#define FLASH_ADDR_NUM_12_Z_DEGREE                  (0x00000000 + 0x27C35C)
#define FLASH_SIZE_NUM_12_Z_DEGREE                  346
#define FLASH_ADDR_NUM_12_Z_DOT                     (0x00000000 + 0x27C4B6)
#define FLASH_SIZE_NUM_12_Z_DOT                     146
#define FLASH_ADDR_NUM_16_0                         (0x00000000 + 0x27D000)
#define FLASH_SIZE_NUM_16_0                         450
#define FLASH_ADDR_NUM_16_1                         (0x00000000 + 0x27D302)
#define FLASH_SIZE_NUM_16_1                         322
#define FLASH_ADDR_NUM_16_2                         (0x00000000 + 0x27D604)
#define FLASH_SIZE_NUM_16_2                         450
#define FLASH_ADDR_NUM_16_3                         (0x00000000 + 0x27D906)
#define FLASH_SIZE_NUM_16_3                         450
#define FLASH_ADDR_NUM_16_4                         (0x00000000 + 0x27DC08)
#define FLASH_SIZE_NUM_16_4                         450
#define FLASH_ADDR_NUM_16_5                         (0x00000000 + 0x27DF0A)
#define FLASH_SIZE_NUM_16_5                         450
#define FLASH_ADDR_NUM_16_6                         (0x00000000 + 0x27E20C)
#define FLASH_SIZE_NUM_16_6                         450
#define FLASH_ADDR_NUM_16_7                         (0x00000000 + 0x27E50E)
#define FLASH_SIZE_NUM_16_7                         450
#define FLASH_ADDR_NUM_16_8                         (0x00000000 + 0x27E810)
#define FLASH_SIZE_NUM_16_8                         450
#define FLASH_ADDR_NUM_16_9                         (0x00000000 + 0x27EB12)
#define FLASH_SIZE_NUM_16_9                         450
#define FLASH_ADDR_NUM_16                           (0x00000000 + 0x27EE14)
#define FLASH_SIZE_NUM_16                           322
#define FLASH_ADDR_NUM_16_A                         (0x00000000 + 0x27F116)
#define FLASH_SIZE_NUM_16_A                         514
#define FLASH_ADDR_NUM_16_B                         (0x00000000 + 0x27F418)
#define FLASH_SIZE_NUM_16_B                         450
#define FLASH_ADDR_NUM_16_C                         (0x00000000 + 0x27F71A)
#define FLASH_SIZE_NUM_16_C                         514
#define FLASH_ADDR_NUM_16_D                         (0x00000000 + 0x27FA1C)
#define FLASH_SIZE_NUM_16_D                         514
#define FLASH_ADDR_NUM_16_E                         (0x00000000 + 0x27FD1E)
#define FLASH_SIZE_NUM_16_E                         386
#define FLASH_ADDR_NUM_16_F                         (0x00000000 + 0x280020)
#define FLASH_SIZE_NUM_16_F                         386
#define FLASH_ADDR_NUM_16_G                         (0x00000000 + 0x280322)
#define FLASH_SIZE_NUM_16_G                         514
#define FLASH_ADDR_NUM_16_H                         (0x00000000 + 0x280624)
#define FLASH_SIZE_NUM_16_H                         450
#define FLASH_ADDR_NUM_16_I                         (0x00000000 + 0x280926)
#define FLASH_SIZE_NUM_16_I                         258
#define FLASH_ADDR_NUM_16_J                         (0x00000000 + 0x280C28)
#define FLASH_SIZE_NUM_16_J                         386
#define FLASH_ADDR_NUM_16_K                         (0x00000000 + 0x280F2A)
#define FLASH_SIZE_NUM_16_K                         450
#define FLASH_ADDR_NUM_16_L                         (0x00000000 + 0x28122C)
#define FLASH_SIZE_NUM_16_L                         386
#define FLASH_ADDR_NUM_16_M                         (0x00000000 + 0x28152E)
#define FLASH_SIZE_NUM_16_M                         578
#define FLASH_ADDR_NUM_16_N                         (0x00000000 + 0x281830)
#define FLASH_SIZE_NUM_16_N                         450
#define FLASH_ADDR_NUM_16_O                         (0x00000000 + 0x281B32)
#define FLASH_SIZE_NUM_16_O                         514
#define FLASH_ADDR_NUM_16_P                         (0x00000000 + 0x281E34)
#define FLASH_SIZE_NUM_16_P                         386
#define FLASH_ADDR_NUM_16_Q                         (0x00000000 + 0x282136)
#define FLASH_SIZE_NUM_16_Q                         514
#define FLASH_ADDR_NUM_16_R                         (0x00000000 + 0x282438)
#define FLASH_SIZE_NUM_16_R                         450
#define FLASH_ADDR_NUM_16_S                         (0x00000000 + 0x28273A)
#define FLASH_SIZE_NUM_16_S                         386
#define FLASH_ADDR_NUM_16_T                         (0x00000000 + 0x282A3C)
#define FLASH_SIZE_NUM_16_T                         450
#define FLASH_ADDR_NUM_16_U                         (0x00000000 + 0x282D3E)
#define FLASH_SIZE_NUM_16_U                         450
#define FLASH_ADDR_NUM_16_V                         (0x00000000 + 0x283040)
#define FLASH_SIZE_NUM_16_V                         514
#define FLASH_ADDR_NUM_16_W                         (0x00000000 + 0x283342)
#define FLASH_SIZE_NUM_16_W                         706
#define FLASH_ADDR_NUM_16_X                         (0x00000000 + 0x283644)
#define FLASH_SIZE_NUM_16_X                         514
#define FLASH_ADDR_NUM_16_Y                         (0x00000000 + 0x283946)
#define FLASH_SIZE_NUM_16_Y                         450
#define FLASH_ADDR_NUM_16_Z                         (0x00000000 + 0x283C48)
#define FLASH_SIZE_NUM_16_Z                         450
#define FLASH_ADDR_NUM_16_Z_COLON                   (0x00000000 + 0x283F4A)
#define FLASH_SIZE_NUM_16_Z_COLON                   258
#define FLASH_ADDR_NUM_16_Z_DEGREE                  (0x00000000 + 0x28424C)
#define FLASH_SIZE_NUM_16_Z_DEGREE                  770
#define FLASH_ADDR_NUM_16_Z_DOT                     (0x00000000 + 0x28454E)
#define FLASH_SIZE_NUM_16_Z_DOT                     258
#define FLASH_ADDR_NUM_18_0                         (0x00000000 + 0x285000)
#define FLASH_SIZE_NUM_18_0                         570
#define FLASH_ADDR_NUM_18_1                         (0x00000000 + 0x28523A)
#define FLASH_SIZE_NUM_18_1                         318
#define FLASH_ADDR_NUM_18_2                         (0x00000000 + 0x285474)
#define FLASH_SIZE_NUM_18_2                         570
#define FLASH_ADDR_NUM_18_3                         (0x00000000 + 0x2856AE)
#define FLASH_SIZE_NUM_18_3                         570
#define FLASH_ADDR_NUM_18_4                         (0x00000000 + 0x2858E8)
#define FLASH_SIZE_NUM_18_4                         570
#define FLASH_ADDR_NUM_18_5                         (0x00000000 + 0x285B22)
#define FLASH_SIZE_NUM_18_5                         570
#define FLASH_ADDR_NUM_18_6                         (0x00000000 + 0x285D5C)
#define FLASH_SIZE_NUM_18_6                         570
#define FLASH_ADDR_NUM_18_7                         (0x00000000 + 0x285F96)
#define FLASH_SIZE_NUM_18_7                         486
#define FLASH_ADDR_NUM_18_8                         (0x00000000 + 0x2861D0)
#define FLASH_SIZE_NUM_18_8                         570
#define FLASH_ADDR_NUM_18_9                         (0x00000000 + 0x28640A)
#define FLASH_SIZE_NUM_18_9                         570
#define FLASH_ADDR_NUM_18_HOUR                      (0x00000000 + 0x287000)
#define FLASH_SIZE_NUM_18_HOUR                      570
#define FLASH_ADDR_NUM_18_MINUTE                    (0x00000000 + 0x288000)
#define FLASH_SIZE_NUM_18_MINUTE                    906
#define FLASH_ADDR_NUM_20_0                         (0x00000000 + 0x289000)
#define FLASH_SIZE_NUM_20_0                         594
#define FLASH_ADDR_NUM_20_1                         (0x00000000 + 0x289252)
#define FLASH_SIZE_NUM_20_1                         418
#define FLASH_ADDR_NUM_20_2                         (0x00000000 + 0x2894A4)
#define FLASH_SIZE_NUM_20_2                         594
#define FLASH_ADDR_NUM_20_3                         (0x00000000 + 0x2896F6)
#define FLASH_SIZE_NUM_20_3                         594
#define FLASH_ADDR_NUM_20_4                         (0x00000000 + 0x289948)
#define FLASH_SIZE_NUM_20_4                         594
#define FLASH_ADDR_NUM_20_5                         (0x00000000 + 0x289B9A)
#define FLASH_SIZE_NUM_20_5                         594
#define FLASH_ADDR_NUM_20_6                         (0x00000000 + 0x289DEC)
#define FLASH_SIZE_NUM_20_6                         594
#define FLASH_ADDR_NUM_20_7                         (0x00000000 + 0x28A03E)
#define FLASH_SIZE_NUM_20_7                         594
#define FLASH_ADDR_NUM_20_8                         (0x00000000 + 0x28A290)
#define FLASH_SIZE_NUM_20_8                         594
#define FLASH_ADDR_NUM_20_9                         (0x00000000 + 0x28A4E2)
#define FLASH_SIZE_NUM_20_9                         594
#define FLASH_ADDR_NUM_20_1_NULL                    (0x00000000 + 0x28B000)
#define FLASH_SIZE_NUM_20_1_NULL                    594
#define FLASH_ADDR_NUM_20_1_S                       (0x00000000 + 0x28C000)
#define FLASH_SIZE_NUM_20_1_S                       594
#define FLASH_ADDR_NUM_48_0_WHITE                   (0x00000000 + 0x28D000)
#define FLASH_SIZE_NUM_48_0_WHITE                   3330
#define FLASH_ADDR_NUM_48_1_WHITE                   (0x00000000 + 0x28E000)
#define FLASH_SIZE_NUM_48_1_WHITE                   2178
#define FLASH_ADDR_NUM_48_2_WHITE                   (0x00000000 + 0x28F000)
#define FLASH_SIZE_NUM_48_2_WHITE                   3330
#define FLASH_ADDR_NUM_48_3_WHITE                   (0x00000000 + 0x290000)
#define FLASH_SIZE_NUM_48_3_WHITE                   3330
#define FLASH_ADDR_NUM_48_4_WHITE                   (0x00000000 + 0x291000)
#define FLASH_SIZE_NUM_48_4_WHITE                   3330
#define FLASH_ADDR_NUM_48_5_WHITE                   (0x00000000 + 0x292000)
#define FLASH_SIZE_NUM_48_5_WHITE                   3330
#define FLASH_ADDR_NUM_48_6_WHITE                   (0x00000000 + 0x293000)
#define FLASH_SIZE_NUM_48_6_WHITE                   3330
#define FLASH_ADDR_NUM_48_7_WHITE                   (0x00000000 + 0x294000)
#define FLASH_SIZE_NUM_48_7_WHITE                   3330
#define FLASH_ADDR_NUM_48_8_WHITE                   (0x00000000 + 0x295000)
#define FLASH_SIZE_NUM_48_8_WHITE                   3330
#define FLASH_ADDR_NUM_48_9_WHITE                   (0x00000000 + 0x296000)
#define FLASH_SIZE_NUM_48_9_WHITE                   3330
#define FLASH_ADDR_NUM_48_PERCENT_WHITE             (0x00000000 + 0x297000)
#define FLASH_SIZE_NUM_48_PERCENT_WHITE             3330
#define FLASH_ADDR_OBLIQUE_LINE                     (0x00000000 + 0x298000)
#define FLASH_SIZE_OBLIQUE_LINE                     770
#define FLASH_ADDR_OBLIQUE_LINE_DARK                (0x00000000 + 0x299000)
#define FLASH_SIZE_OBLIQUE_LINE_DARK                770
#define FLASH_ADDR_PERCENT                          (0x00000000 + 0x29A000)
#define FLASH_SIZE_PERCENT                          682
#define FLASH_ADDR_POINT                            (0x00000000 + 0x29B000)
#define FLASH_SIZE_POINT                            330
#define FLASH_ADDR_POWER_ON_ANIMA_0                 (0x00000000 + 0x29C000)
#define FLASH_SIZE_POWER_ON_ANIMA_0                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_1                 (0x00000000 + 0x2A24E2)
#define FLASH_SIZE_POWER_ON_ANIMA_1                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_10                (0x00000000 + 0x2A89C4)
#define FLASH_SIZE_POWER_ON_ANIMA_10                25826
#define FLASH_ADDR_POWER_ON_ANIMA_11                (0x00000000 + 0x2AEEA6)
#define FLASH_SIZE_POWER_ON_ANIMA_11                25826
#define FLASH_ADDR_POWER_ON_ANIMA_12                (0x00000000 + 0x2B5388)
#define FLASH_SIZE_POWER_ON_ANIMA_12                25826
#define FLASH_ADDR_POWER_ON_ANIMA_13                (0x00000000 + 0x2BB86A)
#define FLASH_SIZE_POWER_ON_ANIMA_13                25826
#define FLASH_ADDR_POWER_ON_ANIMA_14                (0x00000000 + 0x2C1D4C)
#define FLASH_SIZE_POWER_ON_ANIMA_14                25826
#define FLASH_ADDR_POWER_ON_ANIMA_15                (0x00000000 + 0x2C822E)
#define FLASH_SIZE_POWER_ON_ANIMA_15                25826
#define FLASH_ADDR_POWER_ON_ANIMA_16                (0x00000000 + 0x2CE710)
#define FLASH_SIZE_POWER_ON_ANIMA_16                25826
#define FLASH_ADDR_POWER_ON_ANIMA_17                (0x00000000 + 0x2D4BF2)
#define FLASH_SIZE_POWER_ON_ANIMA_17                25826
#define FLASH_ADDR_POWER_ON_ANIMA_18                (0x00000000 + 0x2DB0D4)
#define FLASH_SIZE_POWER_ON_ANIMA_18                25826
#define FLASH_ADDR_POWER_ON_ANIMA_19                (0x00000000 + 0x2E15B6)
#define FLASH_SIZE_POWER_ON_ANIMA_19                25826
#define FLASH_ADDR_POWER_ON_ANIMA_2                 (0x00000000 + 0x2E7A98)
#define FLASH_SIZE_POWER_ON_ANIMA_2                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_20                (0x00000000 + 0x2EDF7A)
#define FLASH_SIZE_POWER_ON_ANIMA_20                25826
#define FLASH_ADDR_POWER_ON_ANIMA_21                (0x00000000 + 0x2F445C)
#define FLASH_SIZE_POWER_ON_ANIMA_21                25826
#define FLASH_ADDR_POWER_ON_ANIMA_22                (0x00000000 + 0x2FA93E)
#define FLASH_SIZE_POWER_ON_ANIMA_22                25826
#define FLASH_ADDR_POWER_ON_ANIMA_23                (0x00000000 + 0x300E20)
#define FLASH_SIZE_POWER_ON_ANIMA_23                25826
#define FLASH_ADDR_POWER_ON_ANIMA_24                (0x00000000 + 0x307302)
#define FLASH_SIZE_POWER_ON_ANIMA_24                25826
#define FLASH_ADDR_POWER_ON_ANIMA_25                (0x00000000 + 0x30D7E4)
#define FLASH_SIZE_POWER_ON_ANIMA_25                25826
#define FLASH_ADDR_POWER_ON_ANIMA_26                (0x00000000 + 0x313CC6)
#define FLASH_SIZE_POWER_ON_ANIMA_26                25826
#define FLASH_ADDR_POWER_ON_ANIMA_27                (0x00000000 + 0x31A1A8)
#define FLASH_SIZE_POWER_ON_ANIMA_27                25826
#define FLASH_ADDR_POWER_ON_ANIMA_28                (0x00000000 + 0x32068A)
#define FLASH_SIZE_POWER_ON_ANIMA_28                25826
#define FLASH_ADDR_POWER_ON_ANIMA_29                (0x00000000 + 0x326B6C)
#define FLASH_SIZE_POWER_ON_ANIMA_29                25826
#define FLASH_ADDR_POWER_ON_ANIMA_3                 (0x00000000 + 0x32D04E)
#define FLASH_SIZE_POWER_ON_ANIMA_3                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_30                (0x00000000 + 0x333530)
#define FLASH_SIZE_POWER_ON_ANIMA_30                25826
#define FLASH_ADDR_POWER_ON_ANIMA_31                (0x00000000 + 0x339A12)
#define FLASH_SIZE_POWER_ON_ANIMA_31                25826
#define FLASH_ADDR_POWER_ON_ANIMA_32                (0x00000000 + 0x33FEF4)
#define FLASH_SIZE_POWER_ON_ANIMA_32                25826
#define FLASH_ADDR_POWER_ON_ANIMA_33                (0x00000000 + 0x3463D6)
#define FLASH_SIZE_POWER_ON_ANIMA_33                25826
#define FLASH_ADDR_POWER_ON_ANIMA_34                (0x00000000 + 0x34C8B8)
#define FLASH_SIZE_POWER_ON_ANIMA_34                25826
#define FLASH_ADDR_POWER_ON_ANIMA_35                (0x00000000 + 0x352D9A)
#define FLASH_SIZE_POWER_ON_ANIMA_35                25826
#define FLASH_ADDR_POWER_ON_ANIMA_4                 (0x00000000 + 0x35927C)
#define FLASH_SIZE_POWER_ON_ANIMA_4                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_5                 (0x00000000 + 0x35F75E)
#define FLASH_SIZE_POWER_ON_ANIMA_5                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_6                 (0x00000000 + 0x365C40)
#define FLASH_SIZE_POWER_ON_ANIMA_6                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_7                 (0x00000000 + 0x36C122)
#define FLASH_SIZE_POWER_ON_ANIMA_7                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_8                 (0x00000000 + 0x372604)
#define FLASH_SIZE_POWER_ON_ANIMA_8                 25826
#define FLASH_ADDR_POWER_ON_ANIMA_9                 (0x00000000 + 0x378AE6)
#define FLASH_SIZE_POWER_ON_ANIMA_9                 25826
#define FLASH_ADDR_STRIGULA_THREE_DARK              (0x00000000 + 0x37F000)
#define FLASH_SIZE_STRIGULA_THREE_DARK              1738
#define FLASH_ADDR_STRIGULA_TWO_DARK                (0x00000000 + 0x380000)
#define FLASH_SIZE_STRIGULA_TWO_DARK                1386
#define FLASH_ADDR_TEMP_DROPS_TO_NORMAL             (0x00000000 + 0x381000)
#define FLASH_SIZE_TEMP_DROPS_TO_NORMAL             9186
#define FLASH_ADDR_TEXT_BAT_HEALTH                  (0x00000000 + 0x384000)
#define FLASH_SIZE_TEXT_BAT_HEALTH                  4626
#define FLASH_ADDR_TEXT_BAT_TEMP                    (0x00000000 + 0x386000)
#define FLASH_SIZE_TEXT_BAT_TEMP                    4626
#define FLASH_ADDR_TEXT_CHARGING_HIGH_TEMP          (0x00000000 + 0x388000)
#define FLASH_SIZE_TEXT_CHARGING_HIGH_TEMP          17346
#define FLASH_ADDR_TEXT_CHARGING_TEMP               (0x00000000 + 0x38D000)
#define FLASH_SIZE_TEXT_CHARGING_TEMP               2718
#define FLASH_ADDR_TEXT_CYCLE_INDEX                 (0x00000000 + 0x38E000)
#define FLASH_SIZE_TEXT_CYCLE_INDEX                 4626
#define FLASH_ADDR_TEXT_DISCHARGING_HIGH_TEMP       (0x00000000 + 0x390000)
#define FLASH_SIZE_TEXT_DISCHARGING_HIGH_TEMP       17346
#define FLASH_ADDR_TEXT_DISCHARGING_TEMP            (0x00000000 + 0x395000)
#define FLASH_SIZE_TEXT_DISCHARGING_TEMP            2718
#define FLASH_ADDR_TEXT_LOW_POWER                   (0x00000000 + 0x396000)
#define FLASH_SIZE_TEXT_LOW_POWER                   5258
#define FLASH_ADDR_TEXT_MINI                        (0x00000000 + 0x398000)
#define FLASH_SIZE_TEXT_MINI                        2466
#define FLASH_ADDR_TEXT_NO_ABNORMAL_RECORDS         (0x00000000 + 0x399000)
#define FLASH_SIZE_TEXT_NO_ABNORMAL_RECORDS         5026
#define FLASH_ADDR_TEXT_PRESS_5S_TO_SETTING         (0x00000000 + 0x39B000)
#define FLASH_SIZE_TEXT_PRESS_5S_TO_SETTING         5954
#define FLASH_ADDR_TEXT_PROTECTION_1                (0x00000000 + 0x39D000)
#define FLASH_SIZE_TEXT_PROTECTION_1                17346
#define FLASH_ADDR_TEXT_PROTECTION_2                (0x00000000 + 0x3A13C2)
#define FLASH_SIZE_TEXT_PROTECTION_2                9186
#define FLASH_ADDR_TEXT_SAFEGUARD                   (0x00000000 + 0x3A6000)
#define FLASH_SIZE_TEXT_SAFEGUARD                   26466
#define FLASH_ADDR_TEXT_STANDING_HIGH_TEMP          (0x00000000 + 0x3AD000)
#define FLASH_SIZE_TEXT_STANDING_HIGH_TEMP          17346
#define FLASH_ADDR_TEXT_STANDING_TEMP               (0x00000000 + 0x3B2000)
#define FLASH_SIZE_TEXT_STANDING_TEMP               2718
#define FLASH_ADDR_TEXT_TIME                        (0x00000000 + 0x3B3000)
#define FLASH_SIZE_TEXT_TIME                        1474
#define FLASH_ADDR_TEXT_VERSION_NUMBER              (0x00000000 + 0x3B4000)
#define FLASH_SIZE_TEXT_VERSION_NUMBER              1902
#define FLASH_ADDR_TEXT_VOLTAGE                     (0x00000000 + 0x3B5000)
#define FLASH_SIZE_TEXT_VOLTAGE                     1474
#define FLASH_ADDR_TEXTTOTAL_VOLTAGE                (0x00000000 + 0x3B6000)
#define FLASH_SIZE_TEXTTOTAL_VOLTAGE                1986
#define FLASH_ADDR_TIAO                             (0x00000000 + 0x3B7000)
#define FLASH_SIZE_TIAO                             678
#define FLASH_ADDR_TITLE_ABNORMAL_TEMP              (0x00000000 + 0x3B8000)
#define FLASH_SIZE_TITLE_ABNORMAL_TEMP              15426
#define FLASH_ADDR_TITLE_ABNORMAL_VOLTAGE           (0x00000000 + 0x3BC000)
#define FLASH_SIZE_TITLE_ABNORMAL_VOLTAGE           15426
#define FLASH_ADDR_TITLE_CELL_VOLTAGE               (0x00000000 + 0x3C0000)
#define FLASH_SIZE_TITLE_CELL_VOLTAGE               15426
#define FLASH_ADDR_TITLE_SCREEN_OFF_DURATION        (0x00000000 + 0x3C4000)
#define FLASH_SIZE_TITLE_SCREEN_OFF_DURATION        15426
#define FLASH_ADDR_TITLE_SOFTWARE_VERSION           (0x00000000 + 0x3C8000)
#define FLASH_SIZE_TITLE_SOFTWARE_VERSION           15426
#define FLASH_ADDR_VOLT                             (0x00000000 + 0x3CC000)
#define FLASH_SIZE_VOLT                             682
#define FLASH_ADDR_VOLT_DARK                        (0x00000000 + 0x3CD000)
#define FLASH_SIZE_VOLT_DARK                        682

#endif /* __FLASH_IMAGE_ADDR_H__ */
