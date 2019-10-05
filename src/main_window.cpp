/**
 * Copyright (c) 2019 Ajay Sreedhar
 *
 * Distributed under MIT License. Please refer the LICENCE file.
 */
#include <cstdlib>
#include "main_window.h"

using namespace nsdl;

/**
 * Creates a window of specified width and height.
 *
 * @param width the window width
 * @param height the window height
 * @throws std::runtime_error if window init fails
 */
MainWindow::MainWindow (int width, int height) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        throw std::runtime_error ("Failed to initialize the SDL2 library");
    }

    this->width = width;
    this->height = height;

    this->window = SDL_CreateWindow("Picture Frame",
                                    SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width, height,0); // NOLINT(hicpp-signed-bitwise)

    if ( !this->window ) {
        throw std::runtime_error ("Failed to create window");
    }

    /* Use hardware accelerated rendering. */
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

/**
 * Stops animation.
 */
void MainWindow::stopAnimation () {
    this->shouldAnimate = false;
}

/**
 * Performs a hardware accelerated rendering of the image texture
 * directly on the main window renderer and blinks the image.
 *
 * Blinking is achieved by repeatedly performing fast blit of
 * the actual image and the _blank texture.
 *
 * @param file the absolute path to image file
 * @return 1 if blit succeeds, 0 otherwise
 */
int MainWindow::blinkImage (const std::string* file) {
    /* Loads image from file. Ideally, PNG images. */
    SDL_Surface* _image = IMG_Load(file->c_str());

    if ( !_image ) {
        return 0;
    }

    this->image = SDL_CreateTextureFromSurface(this->renderer, _image);

    /* Creating texture from  black surface of the same size as that of image. */
    SDL_Surface* _blank = SDL_CreateRGBSurface(0, _image->w, _image->h, 32, 0, 0, 0, 1);
    this->blank = SDL_CreateTextureFromSurface(this->renderer, _blank);

    /* These are rectangular clipping information for the image
     * and the main window onto which the image is to be rendered. */
    SDL_Rect clipSource {0, 0, _image->w, _image->h};
    SDL_Rect clipDest { (this->width - _image->w) / 2, (this->height - _image->h) / 2, _image->w, _image->h };

    /* Prepare max allowed width cap and height cap. */
    int wCap = (this->width - _image->w), hCap = (this->height - _image->h);

    SDL_FreeSurface(_image);
    SDL_FreeSurface(_blank);

    /* Until shouldAnimate flag is set to true, blink the image. */
    while (this->shouldAnimate) {
        int xPos = (int) random() % wCap;
        int yPos = (int) random() % hCap;

        clipDest.x = xPos;
        clipDest.y = yPos;

        SDL_RenderCopy(this->renderer, this->image, &clipSource, &clipDest);
        SDL_RenderPresent(this->renderer);

        SDL_Delay(500);

        SDL_RenderCopy(this->renderer, this->blank, &clipSource, &clipDest);
        SDL_RenderPresent(this->renderer);

        SDL_Delay(500);

        SDL_RenderClear(this->renderer);
    }

    SDL_DestroyTexture(this->image);
    SDL_DestroyTexture(this->blank);

    return 1;
}

/**
 * Runs the window. Polls SDL events.
 */
bool MainWindow::watch () {
    auto event = new SDL_Event();

    SDL_PollEvent(event);

    if (event->type == SDL_QUIT) {
        this->stopAnimation();

        SDL_DestroyWindow(this->window);
        SDL_Quit();

        return false;
    }

    return true;
}
