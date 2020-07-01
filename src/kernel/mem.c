#include <kernel/mem.h>
#include <kernel/atag.h>
#include <common/stdlib.h>
#include <stdint.h>
#include <stddef.h>

extern uint8_t __end;

static uint32_t num_pages;

DEFINE_LIST(page);
IMPLEMENT_LIST(page);

static page_t * all_pages_array;
page_list_t free_pages;

void mem_init(atag_t * atags) {
    uint32_t mem_size, page_array_length;

    // Calculate # of pages    
    mem_size = get_mem_size(atags);
    num_pages = mem_size / PAGE_SIZE;

    // Allocate space for page metadata
    page_array_length = 
}