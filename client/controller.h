#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "SDL2/SDL.h"
#include "Paddle.h"

class Controller {
    public:
        void HandleInput(bool &quit, Paddle &paddle);
};

#endif
