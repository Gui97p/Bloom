#pragma once

typedef struct {
    int handle;
    int index;
} DIR;

typedef enum {
    DT_UNKNOWN = 0,
    DT_FILE,
    DT_DIR
} dirType_t;

typedef struct {
    char dName[256];
    dirType_t dType;
} DirEntry;

DIR* opendir(const char* path);
DirEntry* readdir(DIR* dir);
int closedir(DIR* dir);
int mkdir(const char* path);
