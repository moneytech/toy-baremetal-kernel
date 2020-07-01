#include <kernel/atag.h>

uint32_t get_mem_size(atag_t * tag) {
    // Iterate over atags to find memory size
    while (tag->tag != NONE) {
        if (tag->tag == MEM) {
            return tag->mem.size;
        }
        tag = tag + tag->tag_size;
    }
    return 0;
}