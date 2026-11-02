#ifndef IDT_H
#define IDT_H

#include "stdint.h"
#include "stdbool.h"

#define IDT_MAX_DESCRIPTORS 256

typedef struct idt_entry_t
{
    uint16_t isr_low; //the lower 16 bits of isr address
    uint16_t kernel_cs; //the GDT segment selector that the cpu will load into code segment before calling the ISR 
    uint8_t reserved; //set to zero
    uint8_t attributes; //type and attributes, see the IDT page
    uint16_t isr_high; //the higher 16 bits of the isr adderss
} __attribute__((packed)) idt_entry_t; //attribute is a compiler extension; no padding

typedef struct idtr_t //idtr (idt register) struct
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags); //a function to define the entries
void idt_init(void);

__attribute__((aligned(0x10)))
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance

static idtr_t idtr;

static bool vectors[IDT_MAX_DESCRIPTORS ]; //number of IDT's entries

extern void* isr_stub_table[]; //save the interrupts functions addresses


#endif