#include "stdlib.h"

#define CHAR_0_ASCII_DECIMAL 48 
#define DECIMAL_BASE 10

char* itoa(int value, char *buffer, int base)
{
    int index = 0;
    int isNegative = 0; //flag
    unsigned int num = 0;
    int digit =0;

    if(value == 0)
    {
        buffer[index++] = CHAR_0_ASCII_DECIMAL;
        buffer[index] = '\0'; 
        return buffer;
    }

    if(value < 0 && base == DECIMAL_BASE)
    {
        isNegative =  1;
        num = -(unsigned int)value;
    }
    else
    {
        num = (unsigned int) value;
    }

    while(num != 0)
    {
        digit = num % base;
        buffer[index++] = (digit > 9) ? (digit - 10) + 'a' : CHAR_0_ASCII_DECIMAL + digit;
        num = num / base;
    }

    if(isNegative == 1)
    {
        buffer[index++] = '-';
    }

    buffer[index] = '\0';

    return (reverseStr(buffer));
}

char* reverseStr(char *buffer) 
{
    int len = 0;
    int start = 0;
    int end = 0;
    char temp =' ';

    while (buffer[len] != '\0') 
    {
        len++;
    }

    end = len - 1;

    while (start < end) 
    {
        temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }

    return buffer;
}
