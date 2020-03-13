#include "HUD.h"

HUD::HUD(Renderer &renderer) : mRenderer(renderer) {
    mFont = TTF_OpenFont("FreeMono.ttf", 26);
    mColor = {0, 0, 0, 1};
    mRect.x = renderer.getScreenWidth() / 2 - 50;
    mRect.y = 25;
    mRect.w = 25;
    mRect.h = 25;
}

void HUD::RenderScore(Paddle &paddle1, Paddle &paddle2) {
    mRect.x = mRenderer.getScreenWidth() / 2 - 50;
    RenderScore(paddle1);
    mRect.x = mRenderer.getScreenWidth() / 2 + 25;
    RenderScore(paddle2);
}

void HUD::RenderScore(Paddle &paddle) {

    SDL_Surface *surface;
    SDL_Texture *texture;
    
    int score = paddle.GetScore();

    surface = TTF_RenderText_Solid(mFont, std::to_string(score).c_str(), mColor);
    texture = SDL_CreateTextureFromSurface(mRenderer.getRenderer(), surface);

    SDL_FreeSurface(surface);
    SDL_RenderCopy(mRenderer.getRenderer(), texture, NULL, &mRect);
    SDL_DestroyTexture(texture);
}
