#include <stddef.h>
#include <sys/sbrk.h>

#include "allocator.h"

blockHeader_t* heapHead = NULL;
static blockHeader_t* heapTail = NULL;

static void splitBlock(blockHeader_t* block, size_t size) {
    if (block->size <= size + HEADER_SIZE + 8)
        return;
    
    blockHeader_t* newBlock = (blockHeader_t*)((char*)(block + 1) + size);

    newBlock->size = block->size - size - HEADER_SIZE;

    newBlock->free = 1;
    newBlock->next = block->next;

    block->size = size;
    block->next = newBlock;
}

static blockHeader_t* findFreeBlock(size_t size) {
    blockHeader_t* curr = heapHead;
    while (curr) {
        if (curr->free && curr->size >= size)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

static blockHeader_t* requestBlock(size_t size) {
    size_t allocSize = size > CHUNK_SIZE ? size : CHUNK_SIZE;

    blockHeader_t* block = (blockHeader_t*)sys_sbrk(HEADER_SIZE + allocSize);
    if (block == (void*)-1)
        return NULL;
    
    block->size = size;
    block->free = 0;
    block->next = NULL;

    if (heapTail)
        heapTail->next = block;
    
    heapTail = block;
    
    return block;
}

void *malloc(size_t size) {
    if (size == 0)
        return NULL;
    
    size = (size + 7) & ~7;

    blockHeader_t* block = findFreeBlock(size);

    if (block) {
        splitBlock(block, size);
        block->free = 0;
    } else {
        block = requestBlock(size);
        if (!block) return NULL;

        if (!heapHead) heapHead = block;
    }

    return (void*)(block + 1);
}
