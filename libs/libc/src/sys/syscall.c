#include <sys/syscall.h>

long syscall0(long n) {
    return syscall(n, 0, 0, 0, 0, 0, 0);
}

long syscall1(long n, long a1) {
    return syscall(n, a1, 0, 0, 0, 0, 0);
}

long syscall2(long n, long a1, long a2) {
    return syscall(n, a1, a2, 0, 0, 0, 0);
}

long syscall3(long n, long a1, long a2, long a3) {
    return syscall(n, a1, a2, a3, 0, 0, 0);
}

long syscall4(long n, long a1, long a2, long a3, long a4) {
    return syscall(n, a1, a2, a3, a4, 0, 0);
}

long syscall5(long n, long a1, long a2, long a3, long a4, long a5) {
    return syscall(n, a1, a2, a3, a4, a5, 0);
}

long syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    return syscall(n, a1, a2, a3, a4, a5, a6);
}
