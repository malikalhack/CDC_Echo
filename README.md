# Introduction 
### CDC_Echo project
The project implements a Comunication Device Class (or more precisely Virtual COM Port device) that echoes the received packet.  
The project has been tested on Windows 7/10 and Linux Mint 20.2
# Build and Test
This project was created in the uVision Keil IDE.  
The project used **STM32F103C8** controller by default. If you use another controller, you must replace the contents of the *core* directory and correct the `SystemInit` function in the *bsp.с* file, as well as correct the binding of addresses to this controller in the *usblib.h* file:  
```c
#define USB_BASE       ((uint32_t)0x40005C00)
#define USB_PBUFFER    ((uint32_t)0x40006000)
```
Also correct the `USBLIB_Init` function in the *usblib.c* file.  
Current implementation create Virtual Com Port with next settings: 115200, 0, none, 8, but you can change these settings as you want:
```c
USBLIB_LineCoding lineCoding = {115200, 0, 0, 8};
```
