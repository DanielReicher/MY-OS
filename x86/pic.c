#include "pic.h"

void PIC_sendEOI(uint8_t irq)
{
    /*
    interrupt numbers 0-7 are for the master pic
    interrupt numbers 8-15 are for the slave pic
    */
    if(irq >= 8)  
    {
        //if irq came from the slave pic
        outb(PIC2_COMMAND, PIC_EOI); //send the command to the slave pic 
    }
    outb(PIC1_COMMAND, PIC_EOI); //send the command to the master pic
}

void PIC_remap(int offset1, int offset2)
{   /*
    Starts the initializtion sequnece (in cascade mode).
    The or operation indicates that we are also using icw4.
    We need to send this information both slave and master PIC 
    */
    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4); 
    io_wait();
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC1_DATA, offset1); //icw2- master pic vector offset
    io_wait();
    outb(PIC2_DATA, offset2);  //icw2- slave pic vector offset
    io_wait();
    /*
    icw3- tells the master pic that there is a slave pic at irq2.
    The shift left operation returns 4 
    */
    outb(PIC1_DATA, 1 << CASCADE_IRQ);
    io_wait();
    outb(PIC2_DATA, CASCADE_IRQ); //icw3- tells the slave pic its cascade identity
    io_wait();

    //icw4- tells both pics to use 8086 mode and not 8080 mode
    outb(PIC1_DATA, ICW4_8086); 
    io_wait();
    outb(PIC2_DATA, ICW4_8086); 
    io_wait();

    //unmask both pics
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 0);
}

void PIC_disable(void)
{
    /* 
    0xff equal to 11111111.
    pic turns off intrrupts when he get 1, turn on when he gets 0 
    */
    outb(PIC1_DATA, 0xff);
    outb(PIC2_DATA, 0xff);
}

void IRQ_set_mask(uint8_t IRQline)
{
    uint8_t value;
    uint8_t port;
    
    if(IRQline < 8 ) //interrupt numbers 0-7 are for the master pic
    {
        port = PIC1_DATA;
    }
    else //interrupt numbers 8-15 are for the slave pic
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = inb(port) | (1 << IRQline); //the or operation forces the IRQline bit to turn ON (1) while preserving all other original bits unchanged

    outb(port, value);
}

void PIC_clear_mask(uint8_t IRQline)
{
    uint8_t port;
    uint8_t value;

    if(IRQline < 8 ) //interrupt numbers 0-7 are for the master pic
    {
        port = PIC1_DATA;
    }
    else //interrupt numbers 8-15 are for the slave pic
    {
        port = PIC2_DATA;
        IRQline -= 8;
    }

    value = inb(port) & ~ (1 << IRQline); //the and not operations clears the IRQline bit to 0 while keeping all other bits exactly the same
    outb(port, value);
}

static uint16_t __pic_get_irq_reg(int ocw3)
{
    /* 
    OCW3 to PIC CMD to get the register values.
    PIC2 is chained, and represents IRQs 8-15.  
    PIC1 is IRQs 0-7, with 2 being the chain 
    */
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8 | inb(PIC1_COMMAND)); //status of both pics and returning them together to a 16 bit
}
