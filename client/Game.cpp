#include "Game.h"
#include "controller.h"

void Game::Update(Renderer &renderer, UDPClient &udp_client, const std::string playerName) {
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
    mPaddle1 = &paddle;
    // Updated From Server (opposition)
    std::string p2Name;
    if (paddle.isFirstPlayer()) {
        p2Name = "P2";
    } else {
        p2Name = "P1";
    }
    Paddle paddle2(renderer, p2Name, udp_client);
    mPaddle2 = &paddle2;
    udp_client.SetPaddle(&paddle2);

    Controller controller;
    HUD hud(renderer);

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

        // Render Scores
        hud.RenderScore(paddle, paddle2);

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

void Game::UpdateHUD(char *dataIn) {
    // P1 = Player 1, P2 = Player 2
    int p1Point = *(int*)(dataIn + sizeof(char));
    int p2Point = *(int*)(dataIn + sizeof(char) + sizeof(int));

    std::cout << "P1 score is now: " << p1Point << std::endl;
    mPaddle1->SetScore(p1Point);
    std::cout << "P2 score is now: " << p2Point << std::endl;
    mPaddle2->SetScore(p2Point);    
}
