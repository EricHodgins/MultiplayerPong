#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Paddle.h"
#include "udp_server.h"
#include "../shared/Renderer.h"

class HUD {
    public:
        HUD(Renderer &renderer);
        void RenderScore(Paddle &paddle1, Paddle &paddle2);
        void SendScoreToClients(const Paddle &p1, const Paddle &p2, UDPServer &server);

    private:
        void RenderScore(Paddle &paddle);
        char* SerializeScores(const Paddle &p1, const Paddle &p2) const;

        Renderer &mRenderer;
        TTF_Font *mFont;
        SDL_Color mColor;
        SDL_Rect mRect;
};

#endif
