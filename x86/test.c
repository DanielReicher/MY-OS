#include "stdint.h"
#include "stdlib.h"

#define VGA_ADDR ((unsigned char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define KERNEL_MSG "HELLO FROM THE KERNEL\nbios's memory map table size:\n"
#define CYAN_ON_BLACK 0x0B
#define WHITE_ON_BLACK 0x0f

#define MEM_TABLE_ADRRESS 0x504
#define MEM_TABLE_SIZE_ADRRESS 0x500

#define DECIMAL_BASE 10

void clear_screen();
void puts (const char *str);

__attribute__((noreturn))
void exception_handler(void);

uint32_t memory_map_table_size(void);

static unsigned int vga_index = 0;

void _start(void) 
{
    const char *str = KERNEL_MSG;

    clear_screen();
    puts(str);
    memory_map_table_size();

    while (1) {
        asm (
            "hlt"
        );
    }

    return;
}

void clear_screen()
{
    char *vga_addr = VGA_ADDR;
    unsigned int i = 0;

    while( i < VGA_WIDTH * VGA_HEIGHT * 2)
    {
        vga_addr[i] = 0;
        vga_addr[i+1] = WHITE_ON_BLACK;
        i = i+2;
    }
    vga_index = 0; //to print in the start of the screen
}

void puts(const char *str)
{
    char *vga_addr = VGA_ADDR;
    unsigned int j = 0;
    unsigned int row = 0;

    while(str[j] != '\0')
    {
        if(str[j] == '\n')
        {
            row = vga_index /(VGA_WIDTH * 2);
            vga_index = (row + 1) * VGA_WIDTH * 2;
            j++;
            continue;
        }
        
        vga_addr[vga_index] = str[j];
        vga_addr[vga_index+1] = CYAN_ON_BLACK;
        vga_index = vga_index+2;
        j++;
    }

}

void exception_handler()
{
    __asm__ volatile ("cli; hlt"); //hangs the computer
}

uint32_t memory_map_table_size()
{
    char buffer[50];
    
    // Read the first 16-bit value at the EBDA address (size in KiB)
    uint16_t size_bytes = *(volatile uint16_t*)MEM_TABLE_SIZE_ADRRESS;

    itoa(size_bytes, buffer, DECIMAL_BASE);
    puts(buffer);

    return size_bytes;

}
