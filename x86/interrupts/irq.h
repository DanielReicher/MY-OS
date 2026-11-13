#ifndef IRQ_H
#define IRQ_H

#include "isr.h"

typedef void (*IRQHandler)(Registers* regs);

/*
function to initalize the request
*/
void IRQ_initialize(void);

/*
a function to indictate the irq type & enable it
*/
void IRQ_registerHandler(int irq, IRQHandler handler);

/*

*/
void IRQ_handler(Registers* regs);

#endif