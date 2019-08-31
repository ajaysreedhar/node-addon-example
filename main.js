#!/usr/bin/env node

'use strict';

const SDLAddon = require('./build/Release/sdladdon');
const image = __dirname + '/nodejs-logo.png';

/* Every 2 seconds we print to show that event loop is not blocked. */
setInterval(function () {
    console.log('Event loop tick...');
}, 2000);

SDLAddon.createWindow({ image: image, width: 800, height: 600 });
