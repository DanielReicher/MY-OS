#include "irq.h"
#include "pic.h"

#define HANDLERS 16 //8 from slave pic + 8 from master pic = 16

static IRQHandler IRQHandlers[HANDLERS];

void IRQ_initialize(void)
{
    int i = 0;
    for( i = 0; i < HANDLERS; i++ )
    {
        IRQHandlers[i] = 0;
    }

    PIC_disable();
}

void IRQ_registerHandler(int irq, IRQHandler handler)
{
    if(irq < 0 || irq >= 16)
    {
        return;
    }

    IRQHandlers[irq] = handler;

    IRQ_set_mask(irq); //enable this irq

    if(irq >= 8)
    {
        IRQ_clear_mask(CASCADE_IRQ) //irq2
    }
}

void IRQ_handler(Registers* regs);