#include <napi.h>
#include <Flexcommander.h>
#include <Defines-Internal.h>
#include <Utils-Internal.h>

static FlexCommanderProbeInfo probeInfo;
static FlexCommanderFS fs;
static char *currentDir = NULL;
static char *str = NULL;
static bool isExit = false;

Napi::Number FlexInit(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), Init(&probeInfo));
}

Napi::Number FlexProbeDevices(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), ProbeDevices(&probeInfo));
}

Napi::Number FlexIterateDevices(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), IterateDevices(&probeInfo));
}

Napi::Number _FlexOpen(const Napi::CallbackInfo &info) {
    return Napi::Number::New(info.Env(), FlexOpen(info[0].ToString().Utf8Value().c_str(), &fs));
}

Napi::Number FlexInitFs(const Napi::CallbackInfo &info) {
    currentDir = (char *) calloc(CURRENT_DIR_STRING_LENGTH, sizeof(char));
    str = (char*) calloc(COMMAND_MAX_LENGTH, sizeof(char));
    currentDir[0] = '/';
    return Napi::Number::New(info.Env(), 0);
}

void FlexClose(const Napi::CallbackInfo &info) {
    free(currentDir);
    free(str);
}

void FlexPrintCurrentDir(const Napi::CallbackInfo &info) {
    StripString(currentDir);
    fputs(currentDir, stdout);
    fputs(">", stdout);
    fflush(stdout);
}

Napi::Number FlexProcessInput(const Napi::CallbackInfo &info) {
    memset(str, 0, COMMAND_MAX_LENGTH);
    memcpy(str, info[0].ToString().Utf8Value().c_str(), info[0].ToString().Utf8Value().length());

    if (strcmp("exit", str) == 0) {
        printf("Bye!\n");
        return Napi::Number::New(info.Env(), 2);
    }

    if (ParseRelativePath(str + 3, currentDir)) {
        fputs("Incorrect path\n", stderr);
        return Napi::Number::New(info.Env(), 1);
    }

    if (str[0] == 'l' && str[1] == 's') {
        FlexListDirContent(str + 3, &fs);
        return Napi::Number::New(info.Env(), 0);
    } else if (str[0] == 'c' && str[1] == 'd') {
        if (FlexSetCurrentDir(str + 3, &fs)) {
            fprintf(stderr, "Path doesn't exist!\n");
            return Napi::Number::New(info.Env(), 1);
        } else {
            memset(currentDir, 0, CURRENT_DIR_STRING_LENGTH);
            memcpy(currentDir, str + 3, CURRENT_DIR_STRING_LENGTH - 3);
            return Napi::Number::New(info.Env(), 0);
        }
    } else if (str[0] == 'c' && str[1] == 'p') {
        FlexCopy(str + 3, currentDir, &fs);
        return Napi::Number::New(info.Env(), 0);
    }
    else {
        printf("Unknown command!\n");
        return Napi::Number::New(info.Env(), 1);
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

