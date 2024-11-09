#include <stdlib.h>
#include <string.h>

char* getParentDirectoryPath(const char* path) {
    char *lastSlashPos = strrchr(path, '/');
    char *folderPath = (char*)malloc(256);

    strncpy(folderPath, path, lastSlashPos - path);

    return folderPath;
}