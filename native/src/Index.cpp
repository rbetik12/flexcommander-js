#include <node/node_api.h>
#include <napi.h>
#include <Flexcommander.h>

static FlexCommanderProbeInfo probeInfo;

Napi::Number FlexInit(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), Init(&probeInfo));
}

Napi::Number FlexProbeDevices(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), ProbeDevices(&probeInfo));
}

Napi::Number FlexIterateDevices(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), IterateDevices(&probeInfo));
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

    return exports;
}

NODE_API_MODULE(flexcommander_gui_native, Init)