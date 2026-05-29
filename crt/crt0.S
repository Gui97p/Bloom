.section .entry

.global _start
.extern main
.extern exit

_start:
    mov (%rsp), %rdi
    lea 8(%rsp), %rsi

    call main

.hang:
    jmp .hang