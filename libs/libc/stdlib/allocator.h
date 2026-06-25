#pragma once
#include <stddef.h>

typedef struct blockHeader {
    size_t size;
    int free;
    struct blockHeader* next;
} blockHeader_t;

#define HEADER_SIZE sizeof(blockHeader_t)
#define CHUNK_SIZE 4096
