{
    'targets': [
        {
            'target_name': 'sdladdon',
            'cflags': ['-fexceptions', '-lSDL2', '-pthread'],
            'cflags_cc': ['-fexceptions', '-lSDL2', '-pthread'],
            'sources': ['src/main_window.h', 'src/main_window.cpp', 'src/node_addon.h', 'src/node_addon.cpp'],
            'include_dirs': ['<!@(node -p \'require("node-addon-api").include\')'],
            'libraries': [],
            'dependencies': [
                '<!(node -p \'require("node-addon-api").gyp\')'
            ],
            'defines': [
                'NAPI_CPP_EXCEPTIONS'
            ],
            'conditions': [
                ['OS=="mac"', {
                    'xcode_settings': {
                        'GCC_ENABLE_CPP_EXCEPTIONS': 'YES'
                    },
                    'libraries': [
                        '/usr/local/lib/libSDL2.dylib',
                        '/usr/local/lib/libSDL2_image.dylib'
                    ],
                    'include_dirs': [
                        '/usr/local/include/SDL2'
                    ]
                }],

                ['OS=="linux" and target_arch=="x64"', {
                    'libraries': [
                        '/usr/lib/x86_64-linux-gnu/libSDL2-2.0.so',
                        '/usr/lib/x86_64-linux-gnu/libSDL2_image-2.0.so'
                    ],
                    'include_dirs': [
                        '/usr/include/SDL2'
                    ]
                }],

                ['OS=="linux" and target_arch=="ia32"', {
                    'libraries': [
                        '/usr/lib/libSDL2-2.0.so',
                        '/usr/lib/libSDL2_image-2.0.so'
                    ],
                    'include_dirs': [
                        '/usr/include/SDL2'
                    ]
                }]
            ]
        }
    ]
}