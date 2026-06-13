#pragma once

#include <stddef.h>
#include <stdarg.h>

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

int fflush(FILE* stream);

int putchar(char c);
int fputc(int c, FILE* stream);

int puts(const char* s);
int fputs(const char* str, FILE* stream);

int getchar();
int fgetc(FILE* stream);

char* gets(char* buf, int size);
char* fgets(char* buf, int size, FILE* stream);

int printf(const char *fmt, ...);
int vprintf(const char *fmt, va_list args);

int sprintf(char *str, const char *fmt, ...);
int vsprintf(char *str, const char *fmt, va_list args);

int snprintf(char *str, size_t size, const char *fmt, ...);
int vsnprintf(char *str, size_t size, const char *fmt, va_list args);

int vfprintf(FILE *stream, const char *fmt, va_list args);
int fprintf(FILE *stream, const char *fmt, ...);

FILE* fopen(const char* path, const char* mode);
int fclose(FILE* stream);
size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);
