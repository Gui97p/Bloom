#include <dirent.h>
#include <stdlib.h>
#include <sys/opendir.h>
#include <sys/closedir.h>

DIR* opendir(const char* path) {
    int handle = sys_opendir(path);

    if (handle < 0)
        return NULL;

    DIR* dir = malloc(sizeof(DIR));

    if (!dir) {
        sys_closedir(handle);
        return NULL;
    }
    
    dir->handle = handle;
    dir->index = 0;

    return dir;
}
