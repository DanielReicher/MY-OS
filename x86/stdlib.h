#ifndef STDLIB_H
#define STDLIB_H
/*
a function to onverts an integer into a null-terminated string. It can convert negative numbers too
arguments- an integer value, a pointer to the destination character array- buffer, numerical base for conversion  
returns- pointer to a string
*/
char* itoa(int value, char *buffer, int base);

#endif 