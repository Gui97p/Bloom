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
    // file descriptors
    SYSCALL_OPEN      = 0,
    SYSCALL_CLOSE     = 1,
    SYSCALL_READ      = 2,
    SYSCALL_WRITE     = 3,
    SYSCALL_SEEK      = 4,
    SYSCALL_IOCTL     = 5,

    // directories
    SYSCALL_OPENDIR   = 6,
    SYSCALL_CLOSEDIR  = 7,
    SYSCALL_READDIR   = 8,
    SYSCALL_MKDIR     = 9,

    // memory
    SYSCALL_SBRK      = 10,
    SYSCALL_MALLOC    = 11,
    SYSCALL_FREE      = 12,

    // process management
    SYSCALL_SPAWN     = 13,
    SYSCALL_EXIT      = 14,
    SYSCALL_SLEEP     = 15,

    // system
    SYSCALL_REBOOT    = 16
};