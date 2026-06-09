#include <bin/terminal/terminal.h>
#include <bloom/version.h>

int cmdVersion(terminal_t* term, int argc, char** argv) {
    terminalWriteString(term, BLOOM_NAME);
    terminalPutChar(term, '-');
    terminalWriteString(term, BLOOM_VERSION);
    terminalWriteString(term, " Userspace");
    // printf("%s-%s Userspace", BLOOM_NAME, BLOOM_VERSION);

    return 0;
}