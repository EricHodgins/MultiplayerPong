#include <iostream>
#include <thread>
#include "Game.h"
#include "../shared/LTexture.h"
#include "Ball.h"
#include "udp_socket.h"

void Game::Update(Renderer &renderer, UDPServer &server) {
    std::size_t target_frame_duration = 60;
    Uint32 frame_start = 0;
    Uint32 frame_end = 0;
    Uint32 frame_duration = 0;
    int frame_count = 0;

    Uint32 current_time = SDL_GetTicks();
    Uint32 last_update_time = 0;
    Uint32 deltaTime = current_time - last_update_time;

    bool quit = false;
    SDL_Event e;
        
    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("../shared/dot.bmp");

    Ball ball(renderer, ballTexture, server);

    SDL_Rect paddle;
    paddle.x = 30;
    paddle.y = 100;
    paddle.w = 15;
    paddle.h = 120;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                char read[1];
                read[0] = 'Q';
                //sendto(udp_socket->GetSocketHandle(), read, strlen(read), 0,
                //       udp_socket->GetAddressInfo()->ai_addr, udp_socket->GetAddressInfo()->ai_addrlen);
            }
        }
        
        frame_start = SDL_GetTicks();
        deltaTime = current_time - last_update_time;

        if (deltaTime >= 1) {
            // Move Ball and check collision
            ball.move(paddle, deltaTime);
            last_update_time = current_time;
            ball.sendStateToClients();
        }
 
        // Clear Screen
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.getRenderer());
       
        // Render Ball
        ball.render();

        // Render Paddl 1
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer.getRenderer(), &paddle);

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
    
    //t1.join();
}
