#include <stdio.h>
#include <bloom/version.h>

int cmdUname(int argc, char** argv) {
    printf("%s OS v%s\n%s Kernel\nArch: x86_64", BLOOM_NAME, BLOOM_VERSION, BLOOM_CODENAME);

    return 0;
}