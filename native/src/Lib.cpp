#include <napi.h>
#include <Flexcommander.h>
#include <Defines-Internal.h>
#include <Utils-Internal.h>
#include "../flexcommander-lib/src/include/List.h"
#include <string.h>

static FlexCommanderProbeInfo probeInfo;
static FlexCommanderFS fs;
static char *currentDir = NULL;
static char *str = NULL;
static bool isExit = false;

#define OUTPUT_BUFFER_SIZE 16384

Napi::String ConstructOutputString(PathListNode* listHead, const Napi::Env& env) {
    PathListNode * list = listHead;
    char* output = (char*) calloc(OUTPUT_BUFFER_SIZE, sizeof(char));

    while (list != NULL) {
        strncat(output, list->token, strlen(list->token));
        list = list->next;
    }
    Napi::String outputStr = Napi::String::New(env, output);
    free(output);
    return outputStr;
}

Napi::Number FlexInit(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), Init(&probeInfo));
}

Napi::Number FlexProbeDevices(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), ProbeDevices(&probeInfo));
}

Napi::String FlexIterateDevices(const Napi::CallbackInfo &info) {
    PathListNode* list = IterateDevices(&probeInfo);
    Napi::String outputStr = ConstructOutputString(list, info.Env());
    return outputStr;
}

Napi::Number _FlexOpen(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), FlexOpen(info[0].ToString().Utf8Value().c_str(), &fs));
}

Napi::Number FlexInitFs(const Napi::CallbackInfo &info) {
    currentDir = (char *) calloc(CURRENT_DIR_STRING_LENGTH, sizeof(char));
    str = (char *) calloc(COMMAND_MAX_LENGTH, sizeof(char));
    currentDir[0] = '/';
    return Napi::Number::New(info.Env(), 0);
}

void FlexClose(const Napi::CallbackInfo &info) {
    if (str) {
        free(str);
    }
    if (currentDir) {
        free(currentDir);
    }
}

void FlexPrintCurrentDir(const Napi::CallbackInfo &info) {
    StripString(currentDir);
    fputs(currentDir, stdout);
    fputs(">", stdout);
    fflush(stdout);
}

Napi::String FlexProcessInput(const Napi::CallbackInfo &info) {
    memset(str, 0, COMMAND_MAX_LENGTH);
    memcpy(str, info[0].ToString().Utf8Value().c_str(), info[0].ToString().Utf8Value().length());

    if (strcmp("exit", str) == 0) {
        return Napi::String::New(info.Env(), "Bye!\n");
    }

    if (str[0] == 'p' && str[1] == 'w' && str[2] == 'd') {
        return Napi::String::New(info.Env(), currentDir);
    }

    if (ParseRelativePath(str + 3, currentDir)) {
        return Napi::String::New(info.Env(), "Incorrect path!\n");
    }

    if (str[0] == 'l' && str[1] == 's') {
        FlexListDirContent(str + 3, &fs);
        Napi::String output = ConstructOutputString(fs.output, info.Env());
        return output;
    }
    else if (str[0] == 'c' && str[1] == 'd') {
        if (FlexSetCurrentDir(str + 3, &fs)) {
            return Napi::String::New(info.Env(), "Path doesn't exist!\n");
        } else {
            memset(currentDir, 0, CURRENT_DIR_STRING_LENGTH);
            memcpy(currentDir, str + 3, CURRENT_DIR_STRING_LENGTH - 3);
            return Napi::String::New(info.Env(), "");
        }
    } else if (str[0] == 'c' && str[1] == 'p') {
        FlexCopy(str + 3, currentDir, &fs);
        return Napi::String::New(info.Env(), "");
    } else {
        return Napi::String::New(info.Env(), "Unknown command!\n");
    }
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            Napi::String::New(env, "FlexInit"),
            Napi::Function::New(env, FlexInit)
    );

    exports.Set(
            Napi::String::New(env, "FlexProbeDevices"),
            Napi::Function::New(env, FlexProbeDevices)
    );

    exports.Set(
            Napi::String::New(env, "FlexIterateDevices"),
            Napi::Function::New(env, FlexIterateDevices)
    );

    exports.Set(
            Napi::String::New(env, "FlexOpen"),
            Napi::Function::New(env, _FlexOpen)
    );

    exports.Set(
            Napi::String::New(env, "FlexInitFs"),
            Napi::Function::New(env, FlexInitFs)
    );

    exports.Set(
            Napi::String::New(env, "FlexProcessInput"),
            Napi::Function::New(env, FlexProcessInput)
    );

    exports.Set(
            Napi::String::New(env, "FlexPrintCurrentDir"),
            Napi::Function::New(env, FlexPrintCurrentDir)
    );

    exports.Set(
            Napi::String::New(env, "FlexClose"),
            Napi::Function::New(env, FlexClose)
    );

    return exports;
}

NODE_API_MODULE(flexcommander_gui_native, Init)

