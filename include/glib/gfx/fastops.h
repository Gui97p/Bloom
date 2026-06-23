#pragma once

#include <stdint.h>
#include <stddef.h>

static inline void fill32(uint32_t* dst, uint32_t value, size_t count) {
    asm volatile (
        "cld\n"
        "rep stosl"
        : "+D"(dst), "+c"(count)
        : "a"(value)
        : "memory"
    );
}
