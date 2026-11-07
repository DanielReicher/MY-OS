#include "pic.h"

void PIC_sendEOI(uint8_t irq)
{
    if(irq >= 8) 
    {
        //if irq came from the slave pic
        outb(PIC2_COMMAND, PIC_EOI); //send the command to the slave pic 
    }
    outb(PIC1_COMMAND, PIC_EOI); //send the command to the master pic
}
