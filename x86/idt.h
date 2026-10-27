#ifndef IDT_H
#define IDT_H

#include "stdint.h"
typedef struct 
{
    uint16_t isr_low; //the lower 16 bits of isr address
    uint16_t kernel_cs; //the GDT segment selector that the cpu will load into code segment before calling the ISR 
    uint8_t reserved; //set to zero
    uint8_t attributes; //type and attributes, see the IDT page
    uint16_t isr_high; //the higher 16 bits of the isr adderss
};



#endif