# Atmel_ARM_C
 ARM C related Projects

ASF UART project uses the Advanced Software Framework to create a peripheral interface for the ATSAMD10 microcontroller
Originally implemented using Hardware Abstraction Layer, but does not drive the interrupts as expected.

First implementation uses a USART in SERCOM2 of the Microcontroller pins PA10_RX and PA11_TX drives the UART using a TWD system

To build
Recommended using an ATSAMD10-Explorer Mini at either Microchip.com or Digikey.com
This board comes with a built in Virtual COM port or CDC USB bootloader making a lot of the painful debugging removed.

Use Atmel Studios 7.0
Project > Build Solution/Build <project>
Target the mEDBG Virtual COM port
 
 Use either the Visualization tool built into the IDE and connect to the terminal
 or
 Use Tera Term/PuTTy/HyperTerminal to access the Virtual COM/CDC_UART
 
 If anyone can contribute to this project by having the ADC spit out uint_16 numbers instead of HEX that would be greatly appreciated
