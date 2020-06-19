#include <kernel/uart.h>

void putc(unsigned char c)
{
    uart_putc(c);
}

unsigned char getc()
{
    return uart_getc();
}

void puts(const char * str) 
{
    uart_puts(str);
}