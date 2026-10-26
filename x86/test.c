#define VGA_ADDR ((unsigned char*)0xB8000)
#define VGA_WIDTH 80
#define VGA_HEIGHT 25

#define KERNEL_MSG "HELLO FROM THE KERNEL"
#define CYAN_ON_BLACK 0x0B
#define WHITE_ON_BLACK 0x0f

void clear_screen()
{
    char *vga_addr = VGA_ADDR;
    unsigned int i = 0;

    while( i < VGA_WIDTH * VGA_WIDTH * 2)
    {
        vga_addr[i] = 0;
        vga_addr[i+1] = WHITE_ON_BLACK;
        i = i+2;
    }
}

void puts(const char *str)
{
    char *vga_addr = VGA_ADDR;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int row = 0;

    while(str[j] != '\0')
    {
        if(str[j] == '\0')
        {
            row = i /(VGA_WIDTH * 2);
            i = (row + 1) * VGA_HEIGHT * 2;
            j++;
            continue;
        }
        
        vga_addr[i] = str[j];
        vga_addr[i+1] = CYAN_ON_BLACK;
        i = i+2;
        j++;
    }
}

void _start(void) 
{
    //*VGA_ADDR = '#';
    //*(VGA_ADDR+1) = CYAN_ON_BLACK;

    const char *str = KERNEL_MSG;

    clear_screen();
    puts(str);

    while (1) {
        asm (
            "hlt"
        );
    }

    return;
}
