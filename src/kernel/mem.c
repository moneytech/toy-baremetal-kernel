#include <kernel/mem.h>
#include <kernel/atag.h>
#include <common/stdlib.h>
#include <stdint.h>
#include <stddef.h>

extern uint8_t __end;

static uint32_t num_pages;

DEFINE_LIST(page);
IMPLEMENT_LIST(page);

static page_t * page_array;
page_list_t free_pages;

void mem_init(atag_t * atags) {
    uint32_t mem_size, page_array_size, kernel_pages, i;

    // Calculate # of pages    
    mem_size = get_mem_size(atags);
    num_pages = mem_size / PAGE_SIZE;

    // # of bytes needed for page metadata
    page_array_size = num_pages * sizeof(page_t);

    // Pointer to end of image / beginning of page array
    page_array = (page_t *)&__end;
    bzero(page_array, page_array_size);

    // Number of pages used for kernel
    kernel_pages = ((uint32_t)&__end) / PAGE_SIZE;

    // Kernel pages flags
    for (i = 0; i < kernel_pages; i++) {
        page_array[i].vaddr_mapped = i * PAGE_SIZE;
        page_array[i].flags.allocated = 1;
        page_array[i].flags.kernel_page = 1;
    }

    // Free page flags 
    for (; i < num_pages; i++) {
        page_array[i].flags.allocated = 0;
        append_page_list(&free_pages, &page_array[i]);
    }
}