#include <stdio.h>
#include <string.h>
#include <dirent.h>

int cmdLs(int argc, char** argv) {
   char path[256];

    if (argc <= 1) {
        strcpy(path, "/");
    } else {
        if (argv[1][0] == '/') {
            strncpy(path, argv[1], sizeof(path) - 1);
            path[sizeof(path) - 1] = '\0';
        } else {
            snprintf(path, sizeof(path), "/%s", argv[1]);
        }
    }

    DIR* dir = opendir(path);

    if (!dir) {
        printf("ls: cannot open directory.");
        return -1;
    }

    DirEntry* entry;

    while ((entry = readdir(dir))) {
        printf("%s\n", entry->dName);
    }

    closedir(dir);

    return 0;
}
