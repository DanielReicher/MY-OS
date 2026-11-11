#ifndef IO_H
#define IO_H

#include "stdint.h"

#define UNUSED_PORT 0x80

/*
a function to output the val in the port :)
*/
void  __attribute__((cdecl)) outb(uint16_t port, uint8_t val);

/* 
Hello!! This function is meant to wait a small enough time to let a
previous IO operation (ports) finish 
*/
void io_wait();

/*
a function to get the interrupt into the cpu
*/
uint8_t __attribute__((cdecl)) inb(uint16_t port);

#endif
