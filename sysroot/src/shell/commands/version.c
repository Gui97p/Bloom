#include <stdio.h>
#include <bloom/version.h>

int cmdVersion(int argc, char** argv) {
    printf("%s-%s Userspace", BLOOM_NAME, BLOOM_VERSION);

    return 0;
}