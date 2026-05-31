#include <stdio.h>
#include <bloom/version.h>

int cmdUname(int argc, char** argv) {
    printf("%s %s-%s", BLOOM_CODENAME, BLOOM_NAME, BLOOM_VERSION);

    return 0;
}