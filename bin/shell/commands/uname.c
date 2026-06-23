#include <stdio.h>
#include <stdlib.h>
#include <bloom/version.h>
#include <glib/buffer.h>

//       ____  __
//      / __ )/ /___  ____  ____ ___
//     / __  / / __ \/ __ \/ __ `__ \
//    / /_/ / / /_/ / /_/ / / / / / /
//   /_____/_/\____/\____/_/ /_/ /_/


int cmdUname(int argc, char** argv) {
    printf("     ____  __\n    / __ )/ /___  ____  ____ ___\n   / __  / / __ \\/ __ \\/ __ `__ \\\n  / /_/ / / /_/ / /_/ / / / / / /\n /_____/_/\\____/\\____/_/ /_/ /_/\n\n");

    printf("%s %s v%s\nArch: x86_64\nKernel: %s\nBootloader: Limine\nFramebuffer: VBE\nCompiler: GCC %s\nBuild Date: %s %s\n",
        BLOOM_CODENAME,
        BLOOM_NAME,
        BLOOM_VERSION,
        BLOOM_CODENAME,
        __VERSION__,
        __DATE__,
        __TIME__
    );

    return 0;
}
