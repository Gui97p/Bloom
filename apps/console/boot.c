#include <stdio.h>
#include <string.h>
#include <glib/gfx/context.h>
#include <bloom/version.h>

static void printBoxLine(const char* str) {
    putchar('|');

    int len = strlen(str);

    printf("%s", str);

    for (int i = len; i < 73; i++) {
        putchar(' ');
    }

    puts("|");
}

void consoleBoot(gfxContext_t* ctx) {
    char kernelLine[128];
    char buildLine[128];

    snprintf(
        kernelLine,
        sizeof(kernelLine),
        "              %s Kernel v0.1.0 'Genesis' -- x86_64",
        BLOOM_CODENAME
    );

    snprintf(
        buildLine,
        sizeof(buildLine),
        "              Built: %s -- %ux%u @ %ubpp",
        __DATE__,
        ctx->width,
        ctx->height,
        (ctx->pitch / ctx->width) * 8
    );

    printf(
        "\033[306m"
        "+-------------------------------------------------------------------------+\n"
        "|      ____  __                                                           |\n"
        "|     / __ )/ /___  ____  ____ ___                                        |\n"
        "|    / __  / / __ \\/ __ \\/ __ `__ \\                                       |\n"
        "|   / /_/ / / /_/ / /_/ / / / / / /                                       |\n"
        "|  /_____/_/\\____/\\____/_/ /_/ /_/                                        |\n"
        "|                                                                         |\n"
    );

    printBoxLine(kernelLine);
    printBoxLine(buildLine);

    printf(
        "|                                                                         |\n"
        "+-------------------------------------------------------------------------+\n"
        "\033[301mWelcome to "
        "\033[303mBloom "
        "\033[301m- type "
        "\033[305mhelp "
        "\033[301mto get started.\033[0m\n\n"
    );
}
