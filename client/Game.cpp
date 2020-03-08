#include "Game.h"
#include "controller.h"

void Game::Update(Renderer &renderer, UDPClient &udp_client, const std::string playerName) {
    std::size_t target_frame_duration = 60;
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start = 0;
    Uint32 frame_end = 0;
    Uint32 frame_duration = 0;
    int frame_count = 0;

    Uint32 current_time = SDL_GetTicks();
    Uint32 last_update_time = 0;
    Uint32 deltaTime = current_time - last_update_time;

    bool quit = false;
        
    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("../shared/dot.bmp");

    Ball ball(renderer, ballTexture);
    udp_client.SetBall(&ball);
    
    Paddle paddle(renderer, playerName, udp_client);
    Controller controller;
    while (!quit) {
        controller.HandleInput(quit, paddle);

        frame_start = SDL_GetTicks();
        deltaTime = current_time - last_update_time;

        if (deltaTime >= 1) {
            // Move Ball and check collision
            ball.move(paddle.GetBody(), deltaTime);
            last_update_time = current_time;
        }
 
        // Clear Screen
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.getRenderer());
       
        // Render Ball
        ball.render();

        // Render Paddles 
        paddle.Render();

        // Update Screen
        SDL_RenderPresent(renderer.getRenderer());

        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;
        
        if (frame_duration < target_frame_duration) {
            //SDL_Delay(target_frame_duration - frame_duration);
        }
        
        // Take a load off the CPU with a 1ms delay
        SDL_Delay(1);
        current_time = SDL_GetTicks();
    }

}
