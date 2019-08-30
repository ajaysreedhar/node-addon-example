/**
 * Copyright (c) 2019 Ajay Sreedhar
 *
 * Distributed under MIT License. Please refer the LICENCE file.
 */
#include <stdexcept> /* Standard C++ exceptions */
#include <thread>    /* Standard threading library */

#include <uv.h> /* To manipulate Node.js event loop. */

#include "main_window.h"
#include "node_addon.h"

using namespace nsdl;

/**
 * Performs a surface blit and animates the
 * specified image on window surface.
 *
 * @param window the window object
 * @param attr window attributes struct
 */
void _tAnimateSurface (MainWindow* window, spec_t attr) {
    window->blinkImage(attr.image);
}

/* Polls SDL2 events on the event loop itself. */
void _watchSDLEvents (uv_timer_t* timer) {
    auto window = (MainWindow*) timer->data;

    /* If the window polling has stopped,
     * then clear the timeout function. */
    if ( !window->watch() ) {
        uv_timer_stop(timer);
    }
}

/**
 * This is the tricky part.
 *
 * SDL2 requires graphic events (including keypress, window close, mouse clicks etc.)
 * to be polled on the main loop. Polling on a dedicated thread would result in errors.
 *
 * As running an infinite while-loop to poll SDL2 events would block the event loop,
 * we schedule timer functions (similar to setInterval(cb, millis); in JS) directly
 * on the event loop. This would serve our purpose without blocking event loop.
 *
 * @param attr window attributes struct
 */
bool nsdl::inflate (spec_t attr) {

    /* Here we obtain a reference to Node.js' default event loop. */
    uv_loop_t* loop = uv_default_loop();

    auto timer  = new uv_timer_t();

    try {
        auto window = new MainWindow(attr.width, attr.height);

        /* This injects the window object
         * to the callback function for polling events. */
        timer->data = (void*) window;

        /* To demonstrate multi-threading capabilities with Node.js addon,
         * we run an expensive operation that involves CPU and GPU resources
         * on a separate thread without blocking the event loop. */
        auto tr = new std::thread(_tAnimateSurface, window, attr);
        tr->detach();

        uv_timer_init(loop, timer);

        /* Schedule _watchSDLEvents function to be executed directly on the event loop. */
        uv_timer_start(timer, (uv_timer_cb) &_watchSDLEvents, 0, 10);
        uv_run(loop, UV_RUN_DEFAULT);

    } catch (std::runtime_error &e) {
        return false;
    }

    return true;
}

/**
 * Implements the exported createWindow method.
 *
 * @param args V8 callback info
 */
void nsdl::Method (const v8::FunctionCallbackInfo<v8::Value> &args) {
    auto isolate = args.GetIsolate();
    auto context = isolate->GetCurrentContext();
    auto values = args[0]->ToObject(context).ToLocalChecked();
    auto attributes = values->GetOwnPropertyNames(context).ToLocalChecked();

    spec_t attr { .width=600, .height=800, .image = nullptr};

    /* Here we parse the JSON object passed to createWindow function from main.js file */
    for(int i = 0, l = attributes->Length(); i < l; i++) {
        auto localKey = attributes->Get(i);
        auto localVal = values->Get(context, localKey).ToLocalChecked();

        /* We get key-values as V8 String. So we cast it to standard C++ string. */
        std::string key = *v8::String::Utf8Value(isolate, localKey);
        std::string val = *v8::String::Utf8Value(isolate, localVal);

        if (key == "width")  {
            attr.width = std::stoi(val);
            continue;
        }

        if (key == "height") {
            attr.height = std::stoi(val);
            continue;
        }

        if (key == "image") {
            attr.image = new std::string(val);
            continue;
        }
    }

    /* Inflate window and return the status back to JavaScript */
    bool status = inflate(attr);
    args.GetReturnValue().Set(v8::Boolean::New(isolate, status));
}

/**
 * Exports nsdl::Method() as "createWindow". This can be used with require() module.
 *
 * @param exports injected exports param
 */
void nsdl::Initialize (v8::Local<v8::Object> exports) {
    NODE_SET_METHOD(exports, "createWindow", nsdl::Method);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, nsdl::Initialize)
