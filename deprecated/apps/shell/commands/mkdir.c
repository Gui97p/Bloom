#include <stdio.h>
#include <string.h>
#include <dirent.h>

int cmdMkdir(int argc, char** argv) {
   char path[256];

    if (argc <= 1) {
        printf("mkdir: cannot create directory.");
        return -1;
    } else {
        if (argv[1][0] == '/') {
            strncpy(path, argv[1], sizeof(path) - 1);
            path[sizeof(path) - 1] = '\0';
        } else {
            snprintf(path, sizeof(path), "/%s", argv[1]);
        }
    }
    
    return mkdir(path);
}
