#include <bin/terminal/terminal.h>
#include <bloom/version.h>

int cmdVersion(terminal_t* term, int argc, char** argv) {
    terminalWriteString(term, BLOOM_NAME);
    terminalWriteString(term, " Userspace\nVersion: ");
    terminalWriteString(term, BLOOM_VERSION);
    terminalWriteString(term, "\nBuild: ");
    terminalWriteString(term, __DATE__);
    terminalWriteString(term, " ");
    terminalWriteString(term, __TIME__);
    terminalWriteString(term, "\nCodename: ");
    terminalWriteString(term, BLOOM_CODENAME);

    return 0;
}
