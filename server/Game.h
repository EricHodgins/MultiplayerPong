#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "../shared/Renderer.h"
#include "udp_server.h"

class UDPServer;
class HUD;

class Game {
    public:
        void Update(Renderer &renderer, UDPServer &server);
        void Quit() { mQuit = true; }
        void NotifyClientsGameEnded(UDPServer &server);
    
    private:
        bool mQuit = false;
};

#endif
