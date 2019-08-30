# Node.js Native C++ Addon - Example

>

Node.js runtime, by nature is single threaded. Hence it is not a good idea to write CPU intensive applications
in Javascript and run them with Node.js as it may result in critical performance issues.

But it is possible to overcome this limitation with the help of native _Node.js Addons_.

**Node.js Addons are dynamically-linked shared objects, written in C++, that can be loaded into Node.js using
the require() function**, and used just as if they were an ordinary Node.js module.
They are used primarily to provide an interface between JavaScript running in Node.js and C/C++ libraries.

## About this addon

Here in this project we are developing a Node.js Addon to perform hardware accelerated image drawing
(which uses GPU resources also) from withing a Javascript application, without putting much load on the event loop.

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
$ git clone https://bitbucket.org/ajay-drivezy/nodejs-sdl.git
```

Configure node-gyp and build the addon

```bash
$ cd nodejs-sdl
$ node-gyp configure
$ npm install
```

Finally, run node main.js

```bash
$ node main.js
```