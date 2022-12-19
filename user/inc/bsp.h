// The Board Support Package (BSP).

#ifndef BSP_H_
#define BSP_H_

__declspec(noreturn) void bsp_system_reset(void);

void bsp_enable_irq(void);

void bsp_usb_config(void);

void bsp_led_off(void);

void bsp_led_on(void);

void bsp_led_switch(void);

//void bsp_set_systick_callback(void (*)(void));

#endif /* !BSP_H_ */
