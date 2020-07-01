#include <stddef.h>
#include <stdint.h>

#include <common/stdio.h>
#include <common/stdlib.h>
#include <kernel/uart.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    puts("Hello world!\r\n");
    while (1) {
        putc(getc());
        putc('\n');
    }
}
