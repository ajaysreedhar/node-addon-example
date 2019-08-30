{
    "targets": [
        {
            "target_name": "sdladdon",
            "cflags!": ["-fno-exceptions", "-lSDL2", "-pthread"],
            "cflags_cc": ["-fno-exceptions", "-lSDL2", "-pthread"],
            "sources": ["src/main_window.h", "src/main_window.cpp", "src/node_addon.h", "src/node_addon.cpp"],
            "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")"],
            "libraries": [],
            "dependencies": [
                "<!(node -p \"require('node-addon-api').gyp\")"
            ],
            "defines": [
                "NAPI_CPP_EXCEPTIONS"
            ],
            "conditions": [
                [
                    "OS=='mac'",
                    {
                        "xcode_settings": {
                            "GCC_ENABLE_CPP_EXCEPTIONS": "YES"
                        },
                        "libraries": [
                            "/usr/local/lib/libSDL2.dylib",
                            "/usr/local/lib/libSDL2_image.dylib"
                        ],
                        "include_dirs": [
                            "/usr/local/include/SDL2"
                        ]
                    }
                ]
            ]
        }
    ]
}