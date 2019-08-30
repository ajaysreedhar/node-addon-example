# Node.js Native C++ Addon - Example

> Hardware accelarated image rendering using SDL2

Node.js, by nature is single threaded. Hence it is not adviced to write CPU intensive applications
in Javascript and run them with Node.js due to performance impacts. But it is possible to overcome this 
limitation to an extend, with the help of native _Node.js Addons_.

Node.js Addons are dynamically-linked shared objects, written in C++, that can be loaded into Node.js using
the require() function, and used just as if they were an ordinary Node.js module.

## Prerequisites

The addon uses _Simple DirectMedia Layer_ - a graphics library written in C that provides low level access to graphics hardware.

```bash
$ brew install sdl2
$ brew install sdl2_image
```

Additionally we need to install build tools and node-gyp, if not already installed.

```bash
$ brew install autoconf automake libtool
$ sudo npm install -g node-gyp
```

## Compiling running

Clone the repository

```bash
$ git clone https://github.com/ajaysreedhar/nodejs-sdl-example.git
```

Configure node-gyp and build the addon

```bash
$ cd nodejs-sdl-example
$ node-gyp configure
$ npm install
```

Finally, execute main.js

```bash
$ node main.js
```
