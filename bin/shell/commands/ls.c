#include <dirent.h>
#include <bin/terminal/terminal.h>

int cmdLs(terminal_t* term, int argc, char** argv) {
    DIR* dir = opendir("/");

    if (!dir) {
        termWrite(term, "ls: cannot open directory");
        return -1;
    }

    DirEntry* entry;

    while ((entry = readdir(dir))) {
        termPrintf(term, "%s\n", entry->dName);
    }

    closedir(dir);

    return 0;
}
