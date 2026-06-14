#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/readdir.h>

DirEntry* readdir(DIR* dir) {
    static DirEntry entry;

    // memset(&entry, 0, sizeof(entry));

    if (sys_readdir(dir->index, &entry) < 0)
        return NULL;
    
    dir->index++;

    return &entry;
}
