#include <bin/terminal/terminal.h>
#include <bloom/version.h>

int cmdUname(terminal_t* term, int argc, char** argv) {
    terminalWriteString(term, BLOOM_CODENAME);
    terminalPutChar(term, ' ');
    terminalWriteString(term, BLOOM_NAME);
    terminalWriteString(term, " v");
    terminalWriteString(term, BLOOM_VERSION);
    terminalWriteString(term, "\nArch: x86_64\nKernel: ");
    terminalWriteString(term, BLOOM_CODENAME);
    terminalWriteString(term, "\nBootloader: Limine\nFramebuffer: VBE\nCompiler: GCC ");
    terminalWriteString(term, __VERSION__);
    terminalWriteString(term, "\nBuild Date: ");
    terminalWriteString(term, __DATE__);
    terminalWriteString(term, " ");
    terminalWriteString(term, __TIME__);

    return 0;
}
