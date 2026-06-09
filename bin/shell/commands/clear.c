#include <stdio.h>

int cmdClear(int argc, char** argv) {
    (void)argc;
    (void)argv;

    for (int i = 0; i < 40; i++)
        putchar('\n');
    
    return 0;
}