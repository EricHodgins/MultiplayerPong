#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "udp_client.h"
#include "Ball.h"
#include "Paddle.h"
#include "HUD.h"
#include "../shared/LTexture.h"
#include "../shared/Renderer.h"

class UDPClient;
class Paddle;

class Game {
    public:
        void Update(Renderer &renderer, UDPClient &udp_client, const std::string playerName);
        void Quit() { mQuit = true; }
        void UpdateHUD(char *dataIn);

    private:
        bool mQuit = false;
        Paddle *mPaddle1, *mPaddle2;
};

#endif
