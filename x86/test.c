#define VGA_ADDR ((unsigned char*)0xB8000)

void _start(void) {
    *VGA_ADDR = 'D';
    //*(VGA_ADDR+1) = 0x0B;
}
