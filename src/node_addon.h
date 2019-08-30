/**
 * Copyright (c) 2019 Ajay Sreedhar
 *
 * Distributed under MIT License. Please refer the LICENCE file.
 */
#ifndef EXAMPLE_NODE_ADDON_H
#define EXAMPLE_NODE_ADDON_H

#include <iostream>
#include <string>

#include <node.h> /* Node.js API implementations */
#include <v8.h>   /* V8 Javascript engine helpers. */

namespace nsdl {

/**
 * A traditional C structure to hold window specifications.
 *
 * Declares window width, window height and
 * the path to the image to be displayed.
 */
typedef struct {
    int width = 600, height = 800;
    std::string* image {};
} spec_t;

/**
 * Inflates the entire process. Schedules events on
 * event loop and dedicated thread.
 *
 * @param attr window attributes
 * @return true or false
 */
bool inflate (spec_t attr);

/**
 * Implements the exported createWindow method.
 *
 * @param args V8 callback info
 */
void Method (const v8::FunctionCallbackInfo<v8::Value> &args);

/**
 * Exports nsdl::Method() as "createWindow". This can be used with require() module.
 *
 * @param exports injected exports param
 */
void Initialize (v8::Local<v8::Object> exports);

} /* namespace nsdl */

#endif /* EXAMPLE_NODE_ADDON_H */
