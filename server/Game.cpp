#include <iostream>
#include <thread>
#include "Game.h"
#include "LTexture.h"
#include "Ball.h"
#include "udp_socket.h"

bool quit = false;
std::shared_ptr<UDPSocket> udp_socket(new UDPSocket("0", "8080"));

void tmpSelect() {
    std::cout << "Configuring local address..." << std::endl;

    udp_socket->Bind();

    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket->GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket->GetSocketHandle();

    while (!quit) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
        }

        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            char q[1] = {'\0'};
            udp_socket->Receive(q);
            if (q[0] == 'Q') {
                break;
            }
        }

        std::cout << "select() loop" << std::endl;
    }
}

void Game::Update(Renderer &renderer) {
    std::size_t target_frame_duration = 60;
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start = 0;
    Uint32 frame_end = 0;
    Uint32 frame_duration = 0;
    int frame_count = 0;

    Uint32 current_time = SDL_GetTicks();
    Uint32 last_update_time = 0;
    Uint32 deltaTime = current_time - last_update_time;

    quit = false;
    SDL_Event e;
        
    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("dot.bmp");

    Ball ball(renderer, ballTexture);

    SDL_Rect paddle;
    paddle.x = 30;
    paddle.y = 100;
    paddle.w = 30;
    paddle.h = 125;
    
    std::thread t1(tmpSelect);

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                char read[1];
                read[0] = 'Q';
                sendto(udp_socket->GetSocketHandle(), read, strlen(read), 0,
                       udp_socket->GetAddressInfo()->ai_addr, udp_socket->GetAddressInfo()->ai_addrlen);
            }
        }
        
        frame_start = SDL_GetTicks();
        deltaTime = current_time - last_update_time;

        if (deltaTime >= 1) {
            // Move Ball and check collision
            ball.move(paddle, deltaTime);
            last_update_time = current_time;
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
    
    t1.join();
}
