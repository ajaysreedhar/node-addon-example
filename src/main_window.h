/**
 * Copyright (c) 2019 Ajay Sreedhar
 *
 * Distributed under MIT License. Please refer the LICENCE file.
 */
#ifndef EXAMPLE_MAIN_WINDOW_H
#define EXAMPLE_MAIN_WINDOW_H

#include <string>
#include <stdexcept>

/* Simple Direct Media Layer to manipulate graphics. */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace nsdl {

/**
 * SDL2 members and methods under a hood.
 */
class MainWindow {

private:
    /**
     * Flag to determine animation is required or not.
     */
    bool shouldAnimate = true;

    /**
     * The window width.
     */
    int width;

    /**
     * THe window height.
     */
    int height;

    /**
     * Holds an instance of the SDL2 window created.
     */
    SDL_Window* window;

    /**
     * Holds the hardware accelerated window renderer.
     */
    SDL_Renderer* renderer;

    /**
     * Holds the loaded image texture.
     */
    SDL_Texture* image {};

    /**
     * Holds a plain black texture.
     */
    SDL_Texture* blank {};

public:
    /**
     * Creates a window of specified width and height.
     *
     * @param width the window width
     * @param height the window height
     * @throws std::runtime_error if window init fails
     */
    MainWindow (int width, int height);

    /**
     * Stops animation.
     */
    void stopAnimation ();

    /**
     * Performs a hardware accelerated rendering of the image texture
     * directly on the main window texture and blinks the image.
     *
     * @param file the absolute path to image file
     * @return 1 if blit succeeds, 0 otherwise
     */
    int blinkImage (const std::string* file);

    /**
     * Runs the window. Awaits events.
     */
    bool watch ();
};

} /* namespace nsdl */

#endif /* EXAMPLE_MAIN_WINDOW_H */
