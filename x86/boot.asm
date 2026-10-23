; The CPU loads the bootloader from the first sector in memory into location
; 0x7C00 at RAM. The `org` instruction tells `nasm` to expect this assembly code
; to run from that address in RAM.
org 0x7C00
bits 16 ;before booting, we are in real mode (16 bits)

start:
    jmp main

;function to print
print:
	push si ;save register
	push ax ;save register

.loop:
	lodsb ;load next char from si to al
	or al, al ; if both 0 returns 0 
	jz .done ;if zero, done printing bc we reach the end

	mov ah, 0x0E ;BIOS interrupt, ah = 0x0E print character
	mov bh, 0 ;bh = 0 is the first page of the BIOS's display pages
	int 0x10 ;call BIOS interrupt
	jmp .loop

.done:
	pop ax ;restore register
	pop si ;restore register
	ret ;return


main:
	xor ax, ax ;set ax to 0

	;set segments to 0
	mov ds, ax
	mov es, ax
	mov ss, ax

	;set stack pointer to the address the bios look for the bootloader
	mov sp, 0x7C00

	mov si, msg_hello
	call print

	call enter_protected_mode


	hlt ;privileged instruction, stop executing until interrupt

.halt: ;infinite loop
	jmp .halt

;Message string
;0x0D- Carriage Return, bring back to the start of the line
;0x0A- Line Feed, next line
;0- null, end of the line
msg_hello: db 'Hello, OS World!', 0x0D, 0x0A, 0 
msg_reading_error db "Disk Read Error" , 0

%include "switchTo32.asm"

msg_protected: db 'Protected Mode is active', 0

;Fills the rest of the 512-byte boot sector with zeros
;$- currtent position in file, $$- beginning of the file
times 510-($-$$) db 0 

;Boot signature (0xAA55)- must be present at the last two bytes
;The BIOS checks this signature to determine if the disk is bootable
dw 0xAA55 
