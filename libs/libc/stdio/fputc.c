#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
int fputc(int c, FILE* stream) {
    char ch = (char)c;

    return fwrite(&ch, 1, 1, stream) == 1 ? c : EOF;
}
