# Node.js C++ Addon - Example

> Hardware accelarated image rendering using SDL2

Node.js follows a single threaded, event-driven approach. Hence it is not advised to write CPU intensive applications in 
JavaScript and run them with Node.js as it may obstruct the event loop. 
One of the ways to overcome this limitation is leveraging multi-threading capabilities with the help of _Node.js Addons_.

Node.js Addons are dynamically-linked shared libraries, written in C++, that can be loaded into Node.js runtime using
the `require()` function, and used just as if they were an ordinary JavaScript module.

This example demonstrates a Node.js Addon which performs hardware accelarated image rendering without interfering the event loop. Though events are captured on the main thread, image rendering is performed on a dedicated thread.


## Prerequisites

The addon uses [Simple DirectMedia Layer](https://www.libsdl.org) - a library that provides low level access to graphics hardware.

```bash
# Debian/Ubuntu Linux
$ sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-doc

# Mac OS
$ brew install sdl2
$ brew install sdl2_image
```

Additionally we need to install build tools and node-gyp, if not already installed.

```bash
# Debian/Ubuntu Linux
$ sudo apt-get install autoconf automake libtool

# Mac OS
$ brew install autoconf automake libtool

# Install node-gyp
$ sudo npm install -g node-gyp
```


## Compiling and running

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
