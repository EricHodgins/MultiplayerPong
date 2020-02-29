#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include "../shared/Renderer.h"

class Game {
    public:
        void Update(Renderer &renderer);
};

#endif
