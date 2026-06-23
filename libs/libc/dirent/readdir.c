#include <string.h>
#include <dirent.h>
#include <stddef.h>
#include <sys/readdir.h>

DirEntry* readdir(DIR* dir) {
    static DirEntry entry;

    if (sys_readdir(dir->handle, &entry) < 0)
        return NULL;
    
    dir->index++;

    return &entry;
}
