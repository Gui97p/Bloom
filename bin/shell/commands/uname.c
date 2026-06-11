#include <bin/terminal/terminal.h>
#include <bloom/version.h>
#include <glib/buffer.h>
#include <stdlib.h>

//       ____  __
//      / __ )/ /___  ____  ____ ___
//     / __  / / __ \/ __ \/ __ `__ \
//    / /_/ / / /_/ / /_/ / / / / / /
//   /_____/_/\____/\____/_/ /_/ /_/


int cmdUname(terminal_t* term, int argc, char** argv) {
    termWrite(term, "     ____  __\n");
    termWrite(term, "    / __ )/ /___  ____  ____ ___\n");
    termWrite(term, "   / __  / / __ \\/ __ \\/ __ `__ \\\n");
    termWrite(term, "  / /_/ / / /_/ / /_/ / / / / / /\n");
    termWrite(term, " /_____/_/\\____/\\____/_/ /_/ /_/\n\n");

    termPrintf(term, "%s %s v%s\nArch: x86_64\nKernel: %s\nBootloader: Limine\nFramebuffer: VBE\nCompiler: GCC %s\nBuild Date: %s %s\n",
        BLOOM_CODENAME,
        BLOOM_NAME,
        BLOOM_VERSION,
        BLOOM_CODENAME,
        __VERSION__,
        __DATE__,
        __TIME__
    );

    // termWrite(term, BLOOM_CODENAME);
    // termPutChar(term, ' ');
    // termWrite(term, BLOOM_NAME);
    // termWrite(term, " v");
    // termWrite(term, BLOOM_VERSION);
    // termWrite(term, "\nArch: x86_64\nKernel: ");
    // termWrite(term, BLOOM_CODENAME);
    // termWrite(term, "\nBootloader: Limine\nFramebuffer: VBE\nCompiler: GCC ");
    // termWrite(term, __VERSION__);
    // termWrite(term, "\nBuild Date: ");
    // termWrite(term, __DATE__);
    // termWrite(term, " ");
    // termWrite(term, __TIME__);

    return 0;
}
