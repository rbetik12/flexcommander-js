#pragma once

#ifdef __cplusplus
extern "C" {
#endif
void StripString(char *string);
int ParseRelativePath(char* path, char* currentDir);
#ifdef __cplusplus
}
#endif