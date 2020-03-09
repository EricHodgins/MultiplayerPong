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

    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("../shared/dot.bmp");

    Ball ball(renderer, ballTexture);
    udp_client.SetBall(&ball);
    
    // Controlled by Player
    Paddle paddle(renderer, playerName, udp_client);
    // Updated From Server (opposition)
    std::string p2Name;
    if (paddle.isFirstPlayer()) {
        p2Name = "P2";
    } else {
        p2Name = "P1";
    }
    Paddle paddle2(renderer, p2Name, udp_client);
    udp_client.SetPaddle(&paddle2);

    Controller controller;
    while (!mQuit) {
        controller.HandleInput(paddle, udp_client);

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
        paddle2.Render();

        // Render Middle Line (Dotted)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0x00, 0x00, 0x00, 0x00);
        for (int i = 0; i < renderer.getScreenHeight(); i += 40) {
            SDL_Rect fillRect = { renderer.getScreenWidth() / 2 - 5, i, 10, 20 };
            SDL_RenderFillRect(renderer.getRenderer(), &fillRect);
        }

        // Update Screen
        SDL_RenderPresent(renderer.getRenderer());

        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;
        
        // Take a load off the CPU with a 1ms delay
        SDL_Delay(1);
        current_time = SDL_GetTicks();
    }

}
