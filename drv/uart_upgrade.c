/**********************************************************************************
 *
 * @file    uart_upgrade.c
 * @brief   Bootloader jump — direct jump on key combo trigger
 *
 * @note    key_combo_cb sets g_enter_upgrade flag.
 *          main() calls uart_upgrade_enter() which jumps to bootloader.
 *          Bootloader handles all USART communication for firmware upgrade.
 *
 **********************************************************************************
 */

#include "uart_upgrade.h"
#include "iap_rom.h"

/* Global state --------------------------------------------------------------- */
volatile uint8_t  g_enter_upgrade = 0;      /* set by key_combo_cb, consumed by main() */

/* Private function prototypes ----------------------------------------------- */
static void sfr_reset(void);
static void fsm_go(uint32_t para);

/* ========================================================================== */
/*  Public Functions                                                          */
/* ========================================================================== */

/**
  * @brief  Enter bootloader mode — reset peripherals and jump to bootloader.
  *         Called from main() when g_enter_upgrade is detected.
  * @retval None (never returns)
  */
void uart_upgrade_enter(void)
{
    fsm_go(UUPG_GO_BOOT);
}

/* ========================================================================== */
/*  Private Functions                                                         */
/* ========================================================================== */

/**
  * @brief  Reset peripheral registers before jumping.
  * @retval None
  */
static void sfr_reset(void)
{
    SYSCFG_UNLOCK();
    md_rmu_enable_gpio_reset();
    SYSCFG_LOCK();
}

/**
  * @brief  Jump to application or bootloader.
  * @param  para: UUPG_GO_APP or UUPG_GO_BOOT
  * @retval None (never returns)
  */
static void fsm_go(uint32_t para)
{
    typedef void (*FunVoidType)(void);
    FunVoidType JumpToApplication = NULL;
    uint32_t m_JumpAddress;
    uint32_t addr;

    __disable_irq();

    if (para == UUPG_GO_APP)
    {
        addr = UUPG_APP_ADDR;
    }
    else if (para == UUPG_GO_BOOT)
    {
        addr = UUPG_BOOT_ADDR;

        /* Unlock flash and erase CRC page to invalidate firmware checksum */
        WRITE_REG(MSC->FLASHKEY, 0x8ACE0246);
        WRITE_REG(MSC->FLASHKEY, 0x9BDF1357);
        IAPROM_PAGE_ERASE(CRC_CAL_PAGE_ADDR, ~CRC_CAL_PAGE_ADDR, 0);
        WRITE_REG(MSC->FLASHKEY, 0);
        WRITE_REG(MSC->FLASHKEY, 0);
    }

    /* Reset peripheral registers */
    sfr_reset();

    /* Disable all peripheral clocks */
    SYSCFG_UNLOCK();
    md_cmu_disable_perh_all();
    SYSCFG_LOCK();

    /* Disable all NVIC interrupts and clear pending */
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;

    /* Disable SysTick */
    SysTick->CTRL = 0;
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;

    /* Select boot source */
    if (para == UUPG_GO_APP)
        MD_BOOT_FROM_FLASH();
    else if (para == UUPG_GO_BOOT)
        MD_BOOT_FROM_BOOT_FLASH();

    /* Remap vector table */
    SYSCFG_UNLOCK();
    SYSCFG->MEMRMP = 0x10000;
    SYSCFG->VTOR = addr;
    SYSCFG_LOCK();

    __enable_irq();

    m_JumpAddress = *(volatile uint32_t *)((addr & 0xFFFFFF00) + 4);
    JumpToApplication = (FunVoidType)m_JumpAddress;

    /* Set MSP to new stack top and jump */
    __set_MSP(*(volatile uint32_t *)(addr & 0xFFFFFF00));
    JumpToApplication();
}
