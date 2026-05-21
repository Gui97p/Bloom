.global _start

.section .bss
buffer: .skip 32

.section .text
_start:
    mov $12345, %rax

    lea buffer(%rip), %rsi
    add $31, %rsi
    movb $0, (%rsi)

convert_loop:
    xor %rdx, %rdx
    mov $10, %rbx
    div %rbx

    add $'0', %dl
    dec %rsi
    mov %dl, (%rsi)

    cmp $0, %rax
    jne convert_loop

    lea buffer (%rip), %rdx
    add $31, %rdx
    sub %rsi, %rdx

    mov $1, %rax
    mov $1, %rdi
    syscall

    mov $60, %rax
    xor %rdi, %rdi
    syscall