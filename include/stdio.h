#ifndef STDIO_H
#define STDIO_H

typedef struct {
    int fd;

    char* buffer;
    int bufferSize;
    int bufferPos;

    int mode;
} FILE;

#define EOF (-1)

#define _IONBF 0
#define _IOLBF 1
#define _IOFBF 2

#define BUFSIZ 1024

extern FILE* stdout;
extern FILE* stderr;

int puts(const char* s);
int putchar(char c);
int printf(const char *fmt, ...);
int getchar();
char* gets(char* buf, int size);
char* readline(char* buf, int size);

int fflush(FILE* stream);

#endif