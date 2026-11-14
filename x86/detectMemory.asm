MEM_INT equ 0x15
MEM_INT_AX equ 0xE820
MEM_RECORD_SIZE equ 24
MEM_MAGIC_NUMBER equ 0x534D4150
MEM_TABLE_ADDRESS_HIGH equ 0
MEM_TABLE_ADDRESS_LOW equ 0x6000

detectMemory:
    bits 16
    ; We need to use an interrupt to get information about all the storage
    ; devices (disk memory).
    ; We are using this interrupt, which must be called from real mode:
    ; https://wiki.osdev.org/Detecting_Memory_(x86)#BIOS_Function:_INT_0x15,_EAX_=_0xE820,
    ; We are not going to use this information now, but later, when we go to
    ; protected mode. This let's us keep the bootloader small.
    ;
    ; Set the target address
    mov ax, MEM_TABLE_ADDRESS_HIGH
    mov es, ax
    mov di, MEM_TABLE_ADDRESS_LOW
    ; Set some parameters
.loop:
    mov ax, MEM_INT_AX
    xor bx, bx
    mov cx, MEM_RECORD_SIZE
    mov dx, MEM_MAGIC_NUMBER
    int MEM_INT
    ; Are we done?
    ; TODO: increment the address, es:di by the record size
    jnc .loop
    ret
