bits 16

enter_protected_mode:
    cli ;stops interrupts
    lgdt [gdt_descriptor] ;load the Global Descriptor Table

    ;enable Protected Mode
    mov eax, cr0 ;cr0- control register
    or eax, 0x00000001
    mov cr0, eax

    ; Far jump to a 32-bit code segment
    jmp CODE_SEG:protected_mode_entry


; Global Descriptor Table
gdt_start:

gdt_null:
    dq 0x0000000000000000

gdt_code:
    dq 0x00CF9A000000FFFF

gdt_data:
    dq 0x00CF92000000FFFF

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ 0x08
DATA_SEG equ 0x10


bits 32

protected_mode_entry:
    ;initialize data segment registers
    mov ax, DATA_SEG
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ;initialize the stack
    mov esp, 0x90000

    ;write directly to VGA text memory
    mov edi, 0xB8000 ;the start address for VGA text memory
    mov esi, msg_protected
    mov ah, 0x0A ;set color to green on black

    .print:
        lodsb
        test al, al ;like or but doesnt change al. if al=0 zf is on
        jz .halt

        stosw
        jmp .print

    ret

.halt:
    jmp .halt