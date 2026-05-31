#ifndef STDIO_H
#define STDIO_H

#define EOF (-1)

int puts(const char* s);
int putchar(char c);
int printf(const char *fmt, ...);
int getchar();
char* gets(char* buf, int size);
char* readline(char* buf, int size);

#endif