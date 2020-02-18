#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Renderer {
    public: 
        Renderer(int screenWidth, int screenHeight);
        ~Renderer();
        SDL_Renderer* getRenderer() { return renderer; }

    private:
        int mScreenWidth;
        int mScreenHeight;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif
