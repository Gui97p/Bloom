#include <dirent.h>
#include <stdlib.h>
#include <sys/closedir.h>

int closedir(DIR* dir) {
    int ret = sys_closedir(dir->handle);

    free(dir);

    return ret;
}
