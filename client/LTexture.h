#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <string>
#include "Renderer.h"

class LTexture {
    public: 
        LTexture(Renderer &renderer);
        ~LTexture();
        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

        int getWidth();
        int getHeight();

    private:
        SDL_Texture *mTexture;
        Renderer &mRenderer;
        int mWidth;
        int mHeight;
};

#endif

