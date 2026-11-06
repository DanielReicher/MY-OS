#include "idt.h"

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags)
{
    idt_entry_t* descriptor = &idt[vector]; //get the IDT entry
    descriptor ->isr_low = (uint32_t)isr & 0xFFFF; //store the lower 16 bits of the ISR address
    descriptor -> kernel_cs = 0x08; //GDT offset, set the kernel code segment selector from the GDT
    descriptor -> attributes = flags; //set the gate type and access permissions
    descriptor -> isr_high = (uint32_t)isr >> 16; //store the upper 16 bits of the ISR address
    descriptor -> reserved = 0; //clear the reserved field
}

void idt_init()
{
    idtr.base = (uintptr_t)&idt[0]; //set the base address of the IDT
    idtr.limit = (uint16_t)sizeof(idt_entry_t)* IDT_MAX_DESCRIPTORS - 1; //set the IDT size 

    for(uint8_t vector = 0; vector < 32; vector++) //set up the first 32 CPU exception handler
    {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E); //assign the corresponding ISR stub to the IDT entry
        vectors[vector] = true; //mark this interrupt vector as configured
    }
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
}