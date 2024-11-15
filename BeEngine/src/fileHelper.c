#include <stdlib.h>
#include <string.h>

void getParentDirectoryPath(const char *path, char *resultPath) {
    char *lastSlashPos = strrchr(path, '/');

    strncpy(resultPath, path, lastSlashPos - path);
}