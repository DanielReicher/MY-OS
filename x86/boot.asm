org 0x7C00 ;tells the program to start in the address the bios look for the bootloader
bits 16 ;before booting, we are in real mode (16 bits)

start:
    jmp main


main:
	hlt ;privileged instruction, stop executing until interrupt

.halt: ;infinite loop
	jmp .halt

;Fills the rest of the 512-byte boot sector with zeros
;$- currtent position in file, $$- beginning of the file
times 510-($-$$) db 0 

;Boot signature (0xAA55)- must be present at the last two bytes
;The BIOS checks this signature to determine if the disk is bootable
dw 0xAA55 
