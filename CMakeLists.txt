cmake_minimum_required(VERSION 3.12)

project(nodejs-sdl-example)

add_library(libnsdl_ui src/main_window.h src/main_window.cpp)
add_library(libnsdl src/node_addon.h src/node_addon.cpp)

target_include_directories(libnsdl
        PRIVATE ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api
        PRIVATE ${CMAKE_JS_INC})