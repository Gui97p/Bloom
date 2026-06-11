#include <bin/terminal/terminal.h>
#include <bloom/version.h>

int cmdVersion(terminal_t* term, int argc, char** argv) {
    termPrintf(term, "%s Userspace\nVersion: %s\nBuild: %s %s\nCodename: %s",
        BLOOM_NAME,
        BLOOM_VERSION,
        __DATE__,
        __TIME__,
        BLOOM_CODENAME
    );

    // termWrite(term, BLOOM_NAME);
    // termWrite(term, " Userspace\nVersion: ");
    // termWrite(term, BLOOM_VERSION);
    // termWrite(term, "\nBuild: ");
    // termWrite(term, __DATE__);
    // termWrite(term, " ");
    // termWrite(term, __TIME__);
    // termWrite(term, "\nCodename: ");
    // termWrite(term, BLOOM_CODENAME);

    return 0;
}
