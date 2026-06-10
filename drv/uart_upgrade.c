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

typedef  void (*FunVoidType)(void);

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
    fsm_go(GO_BOOT);
}

/* ========================================================================== */
/*  Private Functions                                                         */
/* ========================================================================== */

/**
  * @brief  define the peripheral register clear function.
  * @param  None
  * @retval None
  */
static void sfr_reset(void)
{
    SYSCFG_UNLOCK();
    md_rmu_enable_gpio_reset();
    md_rmu_enable_usart1_reset();
    SYSCFG_LOCK();
}

/**
  * @brief  define the function used to jump to app program.
  * @param  None
  * @retval None
  */
void fsm_go(uint32_t para)
{
    FunVoidType JumpToApplication = NULL;
    uint32_t m_JumpAddress;
    uint32_t addr;

    __disable_irq();

    if(para == GO_APP)
    {
        addr = APP_ADDR;
    }
    else if(para == GO_BOOT) 
    {
        addr = BOOT_ADDR;
        WRITE_REG(MSC->FLASHKEY, 0x8ACE0246);
        WRITE_REG(MSC->FLASHKEY, 0x9BDF1357);
        IAPROM_PAGE_ERASE(CRC_CAL_PAGE_ADDR, ~CRC_CAL_PAGE_ADDR, 0);
        WRITE_REG(MSC->FLASHKEY, 0);
        WRITE_REG(MSC->FLASHKEY, 0);
    }
    /* reset registers of peripherals */
    sfr_reset();

    /* disable all peripherals' clock */
    SYSCFG_UNLOCK();
    md_cmu_disable_perh_all();
    SYSCFG_LOCK();

    /* disable all peripherals which may cause an interrupt,
    and clear all possible undisposed interrupt flag */ 
    NVIC->ICER[0] = 0xFFFFFFFF;
    NVIC->ICPR[0] = 0xFFFFFFFF;

    /* disable systick and clear the pending bit */
    SysTick->CTRL = 0;
    SCB->ICSR |= SCB_ICSR_PENDSTCLR_Msk;

    /* set start adress to app/boot flash*/
    if(para == GO_APP)
        MD_BOOT_FROM_FLASH();
    else if(para == GO_BOOT)
        MD_BOOT_FROM_BOOT_FLASH();

    /* interrupt vector remap */
    SYSCFG_UNLOCK();
    SYSCFG->MEMRMP = 0x10000;
    SYSCFG->VTOR = addr;
    SYSCFG_LOCK();

    __enable_irq();

    m_JumpAddress = *(volatile uint32_t *)((addr & 0xFFFFFF00) + 4);
    JumpToApplication = (FunVoidType) m_JumpAddress;
    
    /* init stack top */
    __set_MSP(*(volatile uint32_t *)(addr & 0xFFFFFF00));
    /* jump to app/boot flash */
    JumpToApplication();
}

