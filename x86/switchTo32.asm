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
    jz $

    stosw
    jmp .print

configure:
    ;configure and call read_sector to load sector 2 to 0
	mov ax, 0x0000
	mov es, ax ;dest segment
	mov bx, 0x0500 ;dest offsset
	mov dl, 0x00 ;floppy's drive 0
	mov ch, 0x00 ;cylinder 0
	mov cl, 0x02 ;sector 2
	mov dh, 0x00 ;head 0

read_sector:
    mov ah, 0x02 ;set the BIOS disk func to read sectors from drive
	mov al, 0x01 ;the number of the sector we want to read (1)
	int 0x13 ;calls BIOS disk services interrupt
	jc .failed_reading ;if the carry flag is set the reading failed

	; Jump to the kernel
    jmp 0x000:0x0500
    
    ret

.failed_reading:
	mov si, msg_reading_error
	call print
	jmp $ ;infinite loop
