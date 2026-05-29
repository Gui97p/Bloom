.global syscall

syscall:
    mov %rdi, %rax
    mov %rsi, %rdi
    mov %rdx, %rsi
    mov %rcx, %rdx
    mov %r8,  %r10
    mov %r9,  %r8
    mov 8(%rsp), %r9

    push %rcx
    push %r11

    syscall

    pop %r11
    pop %rcx

    ret
