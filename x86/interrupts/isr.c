#include "isr.h"
#include "idt.h"
#include "io.h"

ISRHandler g_ISRHandlers[256]; //256 interrupt vectors
