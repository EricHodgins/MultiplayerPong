#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "udp_client.h"
#include "Ball.h"
#include "../shared/LTexture.h"
#include "../shared/Renderer.h"

class Game {
    public:
        void Update(Renderer &renderer, UDPClient &udp_client);
};

#endif
