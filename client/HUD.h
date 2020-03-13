#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Paddle.h"
#include "../shared/Renderer.h"

class Paddle;

class HUD {
    public:
        HUD(Renderer &renderer);
        void RenderScore(Paddle &paddle1, Paddle &paddle2);

    private:
        void RenderScore(Paddle &paddle);

        Renderer &mRenderer;
        TTF_Font *mFont;
        SDL_Color mColor;
        SDL_Rect mRect;
};

#endif
