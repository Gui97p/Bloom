#include <dirent.h>
#include <stdlib.h>

DIR* opendir(const char* path) {
    (void)path;

    DIR* dir = malloc(sizeof(DIR));

    if (!dir)
        return NULL;
    
    dir->index = 0;

    return dir;
}
