#include <kernel/atag.h>

uint32_t get_mem_size(atag_t * t) {
    // Iterate over atags
    while (tag->tag != NONE) {
        if (tag->tag == MEM) {
            return tag->mem.size;
        }
        tag = ((uint32_t *) tag) + tag->tag_size;
}