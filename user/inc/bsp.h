/**
 * @brief   The Board Support Package (BSP)
 * @file    bsp.h
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    11.12.2022
 * @note    MCU:   STM32F103C8
 * @note    Clock: 8 MHz
 */

#ifndef BSP_H_
#define BSP_H_
/*************** Application Programming Interface prototypes *****************/

/**
 * @brief The wrapper for __NVIC_SystemReset funtion.
 */
__declspec(noreturn) void bsp_system_reset(void);

/**
 * @brief The wrapper for __enable_irq funtion.
 */
void bsp_enable_irq(void);

/**
 * @brief The function turns off the only LED.
 */
void bsp_led_off(void);

/**
 * @brief The function turns on the only LED.
 */
void bsp_led_on(void);

/**
 * @brief The function switches the only LED.
 */
void bsp_led_switch(void);

/******************************************************************************/
#endif /* !BSP_H_ */
