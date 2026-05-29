#ifndef STDIO_H
#define STDIO_H

#define EOF (-1)

int puts(const char* s);
int putchar(char c);
int printf(const char *fmt, ...);
char getchar();

#endif