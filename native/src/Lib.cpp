#include <napi.h>
#include <Flexcommander.h>

static FlexCommanderProbeInfo probeInfo;
static FlexCommanderFS fs;

Napi::Number FlexInit(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Init(&probeInfo));
}

Napi::Number FlexProbeDevices(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), ProbeDevices(&probeInfo));
}

Napi::Number FlexIterateDevices(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), IterateDevices(&probeInfo));
}

Napi::Number _FlexOpen(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), FlexOpen(info[0].ToString().Utf8Value().c_str(), &fs));
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
    return exports;
}

NODE_API_MODULE(flexcommander_gui_native, Init)

