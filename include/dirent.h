#pragma once

typedef struct {
    int index;
} DIR;

typedef struct {
    char dName[256];
} DirEntry;

DIR* opendir(const char* path);
DirEntry* readdir(DIR* dir);
int closedir(DIR* dir);
