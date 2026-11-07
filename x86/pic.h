//----------PIC-----------------
//PIC- an interrupt controller that manages interrupt signals received from devices by combining multiple interrupts into a single interrupt output. 
//The PIC manages interrupt requests from peripheral devices, prioritizes them, and sends them to the CPU

#ifndef PIC_H
#define PIC_H

#include "stdint.h"

#define PIC1 0x20 //IO base address for master PIC 
#define PIC2 0xA0 //IO base address for slave PIC 
#define PIC1_COMMAND    PIC1 //for sending commands
#define PIC1_DATA   (PIC1+1) //for sending & reseving data
#define PIC2_COMMAND    PIC2 //for sending commands
#define PIC2_DATA   (PIC2+1) //for sending & reseving data
#define PIC_EOI	0x20 //end of interrupt command code 

void PIC_sendEOI(uint8_t irq); //eoi- end of interrupt

#endif PIC_H