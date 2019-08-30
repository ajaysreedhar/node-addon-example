cmake_minimum_required(VERSION 3.12)

project(nodejs-sdl-example)

if (UNIX AND NOT APPLE)
    include_directories($ENV{HOME}/.cache/node-gyp/10.16.3/include/node)
endif()

if (UNIX AND APPLE)
    include_directories($ENV{HOME}/Library/Caches/node-gyp/10.16.3/include/node/)
endif()

add_library(libnsdl-ui SHARED src/main_window.h src/main_window.cpp)
add_library(libnsdl-addon SHARED src/node_addon.h src/node_addon.cpp)

target_link_libraries(libnsdl-ui ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

target_include_directories(libnsdl-addon
        PRIVATE ${CMAKE_SOURCE_DIR}/node_modules/node-addon-api
        PRIVATE ${CMAKE_JS_INC}
        PRIVATE ${NODEJS_INCLUDE_DIRS})