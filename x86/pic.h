//----------PIC-----------------
//PIC- an interrupt controller that manages interrupt signals received from devices by combining multiple interrupts into a single interrupt output. 
//The PIC manages interrupt requests from peripheral devices, prioritizes them, and sends them to the CPU

#ifndef PIC_H
#define PIC_H

#include "stdint.h"

//pic1 & 2 data & command address
#define PIC1            0x20    //IO base address for master PIC 
#define PIC2            0xA0    //IO base address for slave PIC 
#define PIC1_COMMAND    PIC1    //for sending commands
#define PIC1_DATA       (PIC1+1) //for sending & reseving data
#define PIC2_COMMAND    PIC2    //for sending commands
#define PIC2_DATA       (PIC2+1) //for sending & reseving data
#define PIC_EOI	        0x20    //end of interrupt command code 

//icw- initialization command  word
//giving the PIC controllers specified vector offsets
#define ICW1_ICW4       0x01 //indicate that icw4 will be present
#define ICW1_SINGLE     0x02 //signal (cascate) mode
#define ICW1_INTERVAL4  0x04 //call address interval 4 (8)
#define ICW1_LEVEL      0x08 //level triggered (edge) mode
#define ICW1_INIT       0x10 //initialization required

#define ICW4_8086       0x01 //8086 mode
#define ICW4_AUTO       0x02 //auto (normal) eoi
#define ICW4_BUF_SLAVE  0x08 //buffered mode-slave
#define ICW4_BUF_MASTER 0x0C //buffered mode-master
#define ICW4_SFNM       0x10 //special fully nested (not)

#define CASCADE_IRQ 2

#define PIC_READ_ISR    0x0a //ocw3 (operation command word 3) irq ready next cmd read
#define PIC_READ_IRR    0x0b //ocw3 (operation command word 3) irq service next cmd read

/*
send the intrrupt
*/
void PIC_sendEOI(uint8_t irq); //eoi- end of interrupt

/*
offset1 - vector offset for master PIC
            vectors on the master become offset1..offset1+7
offset2 - same for slave PIC: offset2..offset2+7 
*/
void PIC_remap(int offset1, int offset2);

/*
disabling the pic intrrupts
*/
void PIC_disable(void);

/*
a function disable interrputs.
IMR- Interrupt Mask Register, 8 bits wide. 
This register is a bitmap of the request lines going into the PIC.
When a bit is set, the PIC ignores the request and continues normal operation. 
Masking IRQ2 will cause the Slave PIC to stop raising IRQs.
*/
void IRQ_set_mask(uint8_t IRQline);

/*
a function to enable interrupts
*/
void IRQ_clear_mask(uint8_t IRQline);

/*
healper function to get the irq register
*/
static uint16_t __pic_get_irq_reg(int ocw3);

/* 
a function that returns the combined value of the cascaded PICs irq request register 
*/
uint16_t pic_get_irr(void);

/* 
a function that returns the combined value of the cascaded PICs in-service register 
*/
uint16_t pic_get_isr(void);


#endif
