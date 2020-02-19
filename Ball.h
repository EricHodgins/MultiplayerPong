#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "LTexture.h"
#include "Renderer.h"

class Ball {
public:
    static const int BALL_WIDTH = 20;
    static const int BALL_HEIGHT = 20;
    static const int DOT_VEL = 10;

    Ball(Renderer &renderer, LTexture &ballTexture);
    void move(SDL_Rect &wall);
    void render();

private:
    int mPosX, mPosY;
    int mVelX, mVelY;
    SDL_Rect mCollider;
    Renderer &mRenderer;
    LTexture mBallTexture;

    bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif

