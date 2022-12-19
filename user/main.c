/**
 * @file    main.c
 * @version 1.0.0
 * @authors Anton Chernov
 * @date    11.12.2022
 */
/******************************* Included files *******************************/
#include "bsp.h"
#include "usblib.h"
/********************************* Entry point ********************************/
int main(void) {
    USBLIB_Init();
    bsp_enable_irq();   /* enable interrupts */

    while (1);          /* Endless loop */
}
/*----------------------------------------------------------------------------*/
void uUSBLIB_DataReceivedHandler(uint16_t *Data, uint16_t Length) {
    USBLIB_Transmit(Data, Length);
}
/******************************************************************************/
