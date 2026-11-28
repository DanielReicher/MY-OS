#include "stdlib.h"

#define CHAR_0_ASCII_DECIMAL 48 

char* itoa(int value, char *buffer, int base)
{
    int num = value;
    int digit = num;
    int index = 0;

    //in base 10 (decimeal), the number can be negative
    if(num < 0 && base == 10)
    {
        buffer[0] = "-";
        index++;
    }

    while(digit > 0)
    {
        digit = num % 10;
        buffer[index] = CHAR_0_ASCII_DECIMAL + digit;
        num = num / 10;
    }

    return buffer;
}