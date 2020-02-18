#include "Game.h"

void Game::Update(Renderer &renderer) {
    bool quit = false;
    SDL_Event e;    

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Clear Screen
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.getRenderer());
        

        // Update Screen
        SDL_RenderPresent(renderer.getRenderer());
    }

}
