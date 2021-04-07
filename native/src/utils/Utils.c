#include <Utils-Internal.h>
#include <stdint.h>
#include <memory.h>
#include <stdlib.h>
#include <Defines-Internal.h>

int ParseRelativePath(char* path, char* currentDir) {
    if (path[0] != '.' && path[0] != '/') {
        return -1;
    }
    StripString(path);
    const size_t currentDirLength = strlen(currentDir);
    const size_t pathLength = strlen(path);

    if (path[0] == '.') {
        char* currentPathBuffer = calloc(COMMAND_MAX_LENGTH, 1);

        if (pathLength > 1 && currentDirLength < 2) {
            memcpy(currentPathBuffer, path + 1, pathLength + 1);
            memset(path, 0, COMMAND_MAX_LENGTH);
            memcpy(path, currentDir + 1, currentDirLength - 1);
            memcpy(path + currentDirLength - 1, currentPathBuffer, pathLength);
        }
        else {
            memcpy(currentPathBuffer, path + 1, pathLength + 1);
            memset(path, 0, COMMAND_MAX_LENGTH);
            memcpy(path, currentDir, currentDirLength);
            memcpy(path + currentDirLength, currentPathBuffer, pathLength);
        }
        free(currentPathBuffer);
    }
    return 0;
}

void StripString(char *string) {
    uint64_t index = 0;
    while (string[index] != '\0') {
        if (string[index] == '\n') {
            string[index] = '\0';
        }
        index++;
    }
}