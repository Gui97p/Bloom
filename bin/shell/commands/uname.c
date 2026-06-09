#include <bin/terminal/terminal.h>
#include <bloom/version.h>

int cmdUname(terminal_t* term, int argc, char** argv) {
    terminalWriteString(term, BLOOM_NAME);
    terminalWriteString(term, " OS v");
    terminalWriteString(term, BLOOM_VERSION);
    terminalPutChar(term, '\n');
    terminalWriteString(term, BLOOM_NAME);
    terminalWriteString(term, " Kernel\nArch: x86_64");
    // printf("%s OS v%s\n%s Kernel\nArch: x86_64", BLOOM_NAME, BLOOM_VERSION, BLOOM_CODENAME);

    return 0;
}