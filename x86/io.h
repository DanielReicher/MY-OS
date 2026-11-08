#ifndef IO_H
#define IO_H

#include "stdint.h"

#define UNUSED_PORT 0x80

void outb(uint16_t port, uint8_t val);
/* Hello!! This function is meant to wait a small enough time to let a
   previous IO operation (ports) finish */
void io_wait();

#endif
