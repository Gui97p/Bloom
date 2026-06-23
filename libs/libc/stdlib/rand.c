#include <stdint.h>

static unsigned long randSeed = 1;

void srand(unsigned int seed) {
    randSeed = seed ? seed : 1;
}

int rand() {
    uint32_t x = randSeed;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    randSeed = x;

    return (int)(x & 0x7FFFFFFF);
}
