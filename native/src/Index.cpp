#include <napi.h>
#include <Lib.h>

Napi::String _Hello(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    std::string result = Hello(info[0].ToString());

    return Napi::String::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
            Napi::String::New(env, "_Hello"),
            Napi::Function::New(env, _Hello)
            );

    return exports;
}

NODE_API_MODULE(flexcommander_gui_native, Init)
