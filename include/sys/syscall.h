#pragma once

long syscall(long num,
             long arg1,
             long arg2,
             long arg3,
             long arg4,
             long arg5,
             long arg6);

long syscall0(long n);
long syscall1(long n, long a1);
long syscall2(long n, long a1, long a2);
long syscall3(long n, long a1, long a2, long a3);
long syscall4(long n, long a1, long a2, long a3, long a4);
long syscall5(long n, long a1, long a2, long a3, long a4, long a5);
long syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6);

enum {
    FD_STDIN       = 0,
    FD_STDOUT      = 1,
    FD_STDERR      = 2,
    FD_SERIAL      = 3
};

enum {
    SYSCALL_READ    = 0,
    SYSCALL_WRITE   = 1,
    SYSCALL_OPEN    = 2,
    SYSCALL_CLOSE   = 3,
    SYSCALL_IOCTL   = 4,
    SYSCALL_MALLOC  = 5,
    SYSCALL_FREE    = 6,
    SYSCALL_SPAWN   = 7,
    SYSCALL_SEEK    = 8,
    SYSCALL_READDIR = 9,
    SYSCALL_REBOOT  = 10,
    SYSCALL_SLEEP   = 11,
};
