#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include "../shared/LTexture.h"
#include "../shared/Renderer.h"
#include "udp_server.h"

class Ball {
public:
    static const int BALL_WIDTH = 20;
    static const int BALL_HEIGHT = 20;
    static constexpr float BALL_VEL = 100.0f;
    
    Ball(Renderer &renderer, LTexture &ballTexture, UDPServer &server);
    void move(SDL_Rect &wall, Uint32 deltaTime);
    void render();
    void sendStateToClients();
    char* SerializeOut();

private:
    float mPosX, mPosY;
    float mVelX, mVelY;
    SDL_Rect mCollider;
    Renderer &mRenderer;
    LTexture mBallTexture;
    UDPServer &mServer;

    bool checkCollision(SDL_Rect a, SDL_Rect b);
};

#endif

