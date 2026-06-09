# Bloom Userland

Bloom is the userland component of a hobbyist microkernel OS built from scratch. It runs on top of [Sekura](https://github.com/mistvxd/sekura), a custom x86-64 microkernel, and provides a minimal C runtime, a partial libc, a keyboard driver, and an interactive shell.

This project was built as a learning experience in low-level systems programming — no Linux, no glibc, no OS abstractions. Everything from the syscall wrapper to `printf` was written by hand.

## **NOTE** - this README is outdated and will be updated later.

---

## Features

- **Custom libc** — partial implementation of `stdio`, `stdlib`, `string`, `unistd`, and `sys` with direct Linux-compatible syscall wrappers
- **Freestanding C runtime** — custom `crt0.S` entry point and x86-64 syscall wrapper in assembly
- **Keyboard driver** — PS/2 scancode parser with keycode mapping, shift state, extended key support, and an event queue
- **Interactive shell** — command parser, command dispatcher, and `readline` with command history (↑/↓ navigation)

---

## Project Structure

```
userland/
├── arch/x86_64/       # syscall wrapper (assembly)
├── crt/               # crt0.S — entry point
├── drivers/keyboard/  # PS/2 keyboard driver
├── libc/              # custom libc
│   └── src/
│       ├── stdio/     # printf, putchar, puts, fflush
│       ├── stdlib/    # itoa, atoi
│       ├── string/    # memcpy, strlen, strcmp, strncpy
│       ├── sys/       # sys_write, sys_read, sys_exit
│       └── unistd/
└── sysroot/
    └── src/
        ├── main.c
        └── shell/
            ├── shell.c
            ├── readline.c   # input with history
            ├── parser.c
            └── commands/
```

---

## Building

Requires `gcc`, `make`, `binutils` targeting `x86_64-linux`.

```bash
cd userland
make
```

This produces:
- `bin/start` — ELF binary
- `../rootfs/sysinit/userspace.elf` — output consumed by the Sekura kernel

To clean:
```bash
make clean
```

---

## How It Works

### Boot flow

```
Sekura kernel
  └── loads userspace.elf into virtual address 0x400000
  └── maps stack at 0x500000–0x501000
  └── iretq → _start (ring 3)
        └── call main
              └── shell loop
```

### Syscalls

The userland communicates with the kernel via a custom syscall wrapper that follows the x86-64 Linux syscall ABI (`rax` = number, `rdi/rsi/rdx/...` = args, `syscall` instruction):

```asm
syscall:
    mov %rdi, %rax
    mov %rsi, %rdi
    ...
    push %rcx
    push %r11
    syscall
    pop %r11
    pop %rcx
    ret
```

### Keyboard

The keyboard driver receives raw PS/2 scancodes from the kernel via `sys_read` on `FD_STDIN`, decodes them into `keyEvent_t` structs (keycode + pressed/released + shift state), and exposes a `keyboardReadEvent` API to the shell.

---

## Kernel

The kernel side (Sekura) is maintained separately by [@mistvxd](https://github.com/mistvxd).
