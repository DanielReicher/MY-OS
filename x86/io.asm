global outb
outb:
    bits 32
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al ;out- transfers data from a CPU register (AL, AX, or EAX) to a specified hardware I/O port address
    ret 