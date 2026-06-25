#include "allocator.h"

extern blockHeader_t* heapHead;

static void coalesce(void) {
    blockHeader_t* curr = heapHead;

    while (curr && curr->next) {
        if (curr->free && curr->next->free) {
            curr->size += HEADER_SIZE + curr->next->size;
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }
}

void free(void *ptr) {
    if (!ptr) return;

    blockHeader_t* block = (blockHeader_t*)ptr - 1;
    block->free = 1;

    coalesce();
}
