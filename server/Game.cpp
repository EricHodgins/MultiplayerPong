#include <iostream>
#include <thread>
#include "Game.h"
#include "Paddle.h"
#include "../shared/LTexture.h"
#include "Ball.h"
#include "udp_socket.h"
#include "HUD.h"

void Game::Update(Renderer &renderer, UDPServer &server) {
    Uint32 frame_start = 0;
    Uint32 frame_end = 0;
    Uint32 frame_duration = 0;
    int frame_count = 0;

    Uint32 current_time = SDL_GetTicks();
    Uint32 last_update_time = 0;
    Uint32 deltaTime = current_time - last_update_time;
        
    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("../shared/dot.bmp");

    Ball ball(renderer, ballTexture, server);
    Paddle paddle1(renderer, server.getPlayer1()->name, server);
    Paddle paddle2(renderer, server.getPlayer2()->name, server);
    
    server.SetPaddle1(&paddle1);
    server.SetPaddle2(&paddle2);

    HUD hud(renderer);

    while (!mQuit) {
        
        frame_start = SDL_GetTicks();
        deltaTime = current_time - last_update_time;

        if (deltaTime >= 1) {
            // Move Ball and check collision
            ball.move(paddle1, paddle2, deltaTime);
            last_update_time = current_time;
            ball.sendStateToClients();
            if (ball.HasScored(paddle1, paddle2)) {
                std::cout << "Score!" << std::endl;
                hud.SendScoreToClients(paddle1, paddle2, server);
            }
        }
 
        // Clear Screen
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer.getRenderer());
       
        // Render Ball
        ball.render();

        // Render Paddles
        paddle1.Render();
        paddle2.Render();

        // Render Middle Line (Dotted)
        SDL_SetRenderDrawColor(renderer.getRenderer(), 0x00, 0x00, 0x00, 0x00);
        for (int i = 0; i < renderer.getScreenHeight(); i += 40) {
            SDL_Rect fillRect = { renderer.getScreenWidth() / 2 - 5, i, 10, 20 };
            SDL_RenderFillRect(renderer.getRenderer(), &fillRect);
        }

        // Render Scores (HUD)
        hud.RenderScore(paddle1, paddle2);

        // Update Screen        
        SDL_RenderPresent(renderer.getRenderer());

        frame_end = SDL_GetTicks();
        frame_count++;
        frame_duration = frame_end - frame_start;
        
        // Take a load off the CPU with a 1ms delay
        SDL_Delay(1);
        current_time = SDL_GetTicks();
    }

    NotifyClientsGameEnded(server);
    SDL_Delay(1000);
}

void Game::NotifyClientsGameEnded(UDPServer &server) {
    char quitFlag = 'Q';
    int dataSize = sizeof(char);
    
    int bytes_sent1 = sendto(server.GetSocket()->GetSocketHandle(), &quitFlag, dataSize, 0,
                            (struct sockaddr*)&server.getPlayer1()->address,
                            sizeof(server.getPlayer1()->address));

    int bytes_sent2 = sendto(server.GetSocket()->GetSocketHandle(), &quitFlag, dataSize, 0,
                            (struct sockaddr*)&server.getPlayer2()->address,
                            sizeof(server.getPlayer2()->address));

    if (bytes_sent1 < 0 || bytes_sent2 < 0) {
        std::cout << "Game::NotifyClientsGameEnded failed." << std::endl;
    }

    std::cout << "Quit: " << bytes_sent1 << ", " << bytes_sent2 << std::endl;

}
