#include "bsp.h"
#include "usblib.h"


int main(void) {
    USBLIB_Init();
    bsp_enable_irq();  /* enable interrupts */

    while (1);
}

void uUSBLIB_DataReceivedHandler(uint16_t *Data, uint16_t Length) {
    USBLIB_Transmit(Data, Length);
}
