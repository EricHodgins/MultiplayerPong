#include "controller.h"

void Controller::HandleInput(bool &quit, Paddle &paddle) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    paddle.Move(UP);
                    break;
                case SDLK_DOWN:
                    paddle.Move(DOWN);
                    break;
                default:
                    break;
            }
        }
    }
}
