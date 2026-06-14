#include <dirent.h>
#include <stdlib.h>

int closedir(DIR* dir) {
    free(dir);
    return 0;
}
