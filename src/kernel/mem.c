#include <kernel/mem.h>
#include <kernel/atag.h>
#include <common/stdlib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct heap_segment {
    struct heap_segment * next;
    struct heap_segment * prev;
    uint32_t is_allocated;
    uint32_t segment_size;
} heap_segment_t;

void heap_init(uint32_t heap_start);

extern uint8_t __end;

static uint32_t num_pages;

DEFINE_LIST(page);
IMPLEMENT_LIST(page);

static page_t * page_array;
page_list_t free_pages;
static heap_segment_t * heap_segment_list_head;

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

    for(; i < kernel_pages + (KERNEL_HEAP_SIZE / PAGE_SIZE); i++){
        all_pages_array[i].vaddr_mapped = i * PAGE_SIZE; 
        all_pages_array[i].flags.allocated = 1;
        all_pages_array[i].flags.kernel_heap_page = 1;
    }

    // Free page flags 
    for (; i < num_pages; i++) {
        page_array[i].flags.allocated = 0;
        append_page_list(&free_pages, &page_array[i]);
    }

    // Initialize heap at end of page array
    heap_init((uint32_t)&__end + page_array_size)
}

void * alloc_page(void) {
    page_t * page;
    void * page_memory; 

    if (size_page_list(&free_pages) == 0) {
        // Out of free pages
        return 0;
    }

    page = pop_page_list(&free_pages);
    page->flags.kernel_page = 1;
    page->flags.allocated = 1;

    // Index * page size = physical page memory address
    page_memory = (void *)((page - page_array) * PAGE_SIZE);

    bzero(page_memory, PAGE_SIZE);

    return page_memory;
}

void free_page(void * ptr) {
    page_t * page;

    // Physical address / PAGE_SIZE + start of page_array = index 
    page = (page_t *)(((uint32_t)ptr / PAGE_SIZE) + page_array);

    page->flags.allocated = 0;
    bzero(ptr, PAGE_SIZE);

    append_page_list(&free_pages, page);
}

// void * kmalloc(uint32_t bytes) {

// }

// void free(void * ptr) {

// }

void heap_init(uint32_t heap_start) {
    heap_segment_list_head = (heap_segment_t *)heap_start;
    bzero(heap_segment_list_head, sizeof(heap_segment_t));
    heap_segment_list_head->segment_size = KERNEL_HEAP_SIZE;
}