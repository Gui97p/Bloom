#include <stdio.h>
#include <bloom/version.h>

int cmdVersion(int argc, char** argv) {
    printf("%s Userspace\nVersion: %s\nBuild: %s %s\nCodename: %s",
        BLOOM_NAME,
        BLOOM_VERSION,
        __DATE__,
        __TIME__,
        BLOOM_CODENAME
    );

    return 0;
}
