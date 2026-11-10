#ifndef IRQ_H
#define IRQ_H

#include "isr.h"

typedef void (*IRQHandler)(Registers* regs);

void IRQ_initialize();
void IRQ_registerHandler(int irq, IRQHandler, handler)

#endif