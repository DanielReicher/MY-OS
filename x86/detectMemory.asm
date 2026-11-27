MEM_INT equ 0x15
MEM_INT_AX equ 0xE820
MEM_RECORD_SIZE equ 24
MEM_MAGIC_NUMBER equ 0x534D4150
MEM_EBDA_TABLE_ADDRESS_HIGH equ 0
MEM_EBDA_TABLE_ADDRESS_LOW equ 0x500 ;Extended BIOS Data Area

detectMemory:
    bits 16
    ; We need to use an interrupt to get information about all the storage
    ; devices (disk memory).
    ; We are using this interrupt, which must be called from real mode:
    ; https://wiki.osdev.org/Detecting_Memory_(x86)#BIOS_Function:_INT_0x15,_EAX_=_0xE820,
    ;https://wiki.osdev.org/Memory_Map_(x86)#Extended_BIOS_Data_Area_(EBDA)
    ; We are not going to use this information now, but later, when we go to
    ; protected mode. This let's us keep the bootloader small.
    ;
    ; Set the target address
    mov ax, MEM_EBDA_TABLE_ADDRESS_HIGH
    mov es, ax 
    lea di, [MEM_EBDA_TABLE_ADDRESS_LOW + 4]
    xor bx, bx 
    xor si, si

.loop:
    ; Set some parameters
    mov ax, MEM_INT_AX
    mov cx, MEM_RECORD_SIZE
    mov dx, MEM_MAGIC_NUMBER ;for APCI 
    int MEM_INT

    ; Are we done?
    ;if carry flag is set or bx = 0 we done

    lahf ;transfers the low byte of the flags word to AH. The bits, from MSB to LSB, are sign, zero, indeterminate, auxiliary, carry, indeterminate, parity, indeterminate, and carry.
    
    ;checking if bx = 0
    test bx, bx 
    jz .if_bx_zero

    ;checking if carry flag set
    test ah, ah
    jnz .if_carry_set

    ;if not done- increment the address, es:di by the record size
    add di, MEM_RECORD_SIZE ;the pointer wont overflow so we dont need to use es
    add si, MEM_RECORD_SIZE

    jnc .loop
    ret

.if_bx_zero:
    add si, MEM_RECORD_SIZE 
    ret

.if_carry_set:
    ret
