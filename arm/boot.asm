.global _start

_start:   
    //ldr- load register, x30- arm's link register. put stack_top address in x30 
    ldr x30, =stack_top //setup stack
    
    //sp- stack pointer                  
    mov sp, x30  
    
    //bl- branch with link. call kernel_main and save the return address in x30
    bl kernel_main  
    
    //infinite loop
    b .
