#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "Paddle.h"
#include "udp_client.h"

class Controller {
    public:
        void HandleInput(Paddle &paddle, UDPClient &client);

    private:
        void SendQuitToServer(UDPClient &client);
};

#endif
