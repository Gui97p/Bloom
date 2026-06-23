#include <sys/reboot.h>

int cmdReboot(int argc, char** argv) {
    sys_reboot();
}
