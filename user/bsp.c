/**
 * @brief   The Board Support Package (BSP)
 * @file    bsp.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    11.12.2022
 * @note    MCU:   STM32F103C8
 * @note    Clock: 8 MHz
 */
/******************************* Included files *******************************/
#include "stm32f10x.h"
/********************************* Definition *********************************/
#define SYSCLK_FREQ_48MHz  48000000
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
                                  This value must be a multiple of 0x200. */
/****************************** Private  functions ****************************/

/**
 * @brief Static function for reseting Clock Control Registers group (RCC)
 */
static void rcc_reset(void) {
    RCC->CR |= (uint32_t)0x00000001;    // HSION=1;
/*---------------------------- Reset defined bits ----------------------------*/
    RCC->CFGR &= (uint32_t)0xF8FF0000;  // SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO
    RCC->CR   &= (uint32_t)0xFEF6FFFF;  // HSEON, CSSON and PLLON
    RCC->CR   &= (uint32_t)0xFFFBFFFF;  // HSEBYP
    RCC->CFGR &= (uint32_t)0xFF80FFFF;  // PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE
/*----------------------------------------------------------------------------*/
    RCC->CIR = 0x009F0000;              // Disable all interrupts and clear pending bits
}

/**
 * @brief Static function for configuring flash
 */
static void flash_config(void) {
    FLASH->ACR |= FLASH_ACR_PRFTBE;     // Enable Prefetch Buffer

    /* Flash 1 wait state */
    FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_1;
}

/**
 * @brief Static function for configuring Clock Control Registers group (RCC)
 */
static void rcc_config(void) {
/*********************************** 48 MHz ***********************************/
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);        // HSE=ON
    while(!(RCC->CR & RCC_CR_HSERDY));
    RCC->CFGR |= RCC_CFGR_PLLMULL6;             // PLLMUL=6;
    RCC->CFGR |= RCC_CFGR_USBPRE;               // USBPRE=1;
    RCC->CFGR |= RCC_CFGR_PLLSRC;               // PLLSRC=HSE

    RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;  // AHB prescaler  = 1
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV1; // APB2 prescaler = 1
    RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV2; // APB1 prescaler = 2

    RCC->CR   |= RCC_CR_PLLON;                  // PLL=ON
    while(!(RCC->CR & RCC_CR_PLLRDY));

    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;     // SW=PLL

    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08);
    RCC->CR &= ~RCC_CR_HSION;                   //HSI=OFF;
/*----------------------------------------------------------------------------*/
#ifdef VECT_TAB_SRAM
    SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
    SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif 
}

/**
 * @brief Static function for configuring General Purpose Input Output
 * register group (GPIO)
 */
static void gpio_config(void) {
/********************************** PC13 LED **********************************/
   GPIOC->BSRR = GPIO_BSRR_BS13;    //PIN13 = 1 (LED off)
   GPIOC->CRH |= GPIO_CRH_MODE13_1; //PIN13: output, 2MHz, open-drain, general
/******************************** PA12 USB DP ********************************/
   GPIOA->CRH |= GPIO_CRH_MODE12_0; //PIN12: output, 10MHz
   GPIOA->CRH &= ~GPIO_CRH_CNF12;   //PIN12: output, push-pull, general
}

/**
 * @brief The function is exported to the startup file.
 */
void SystemInit (void) {
    rcc_reset();
    flash_config();
    rcc_config();
    gpio_config();
}


void bsp_led_off(void) {
    GPIOC->BSRR = GPIO_ODR_ODR13;
}

void bsp_led_on(void) {
    GPIOC->BRR = GPIO_ODR_ODR13;
}

void bsp_led_switch(void) {
    GPIOC->ODR ^= GPIO_ODR_ODR13;
}

void bsp_system_reset(void) {
    __NVIC_SystemReset();
}

void bsp_enable_irq(void) {
    __enable_irq();  /* enable interrupts */
}
