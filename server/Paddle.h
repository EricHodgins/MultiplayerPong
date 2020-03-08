#ifndef PADDLE_H
#define PADDLE_H

#include "SDL2/SDL.h"
#include "udp_server.h"
#include "../shared/Renderer.h"
#include <string>

enum Direction {
    UP, DOWN 
};


class UDPServer;
struct Player;

class Paddle {
    public:
        static const int PADDLE_WIDTH = 15;
        static const int PADDLE_HEIGHT = 120;
        static constexpr float PADDLE_VEL = 20.0f;

        Paddle();
        Paddle(Renderer &renderer, std::string pFlag, UDPServer &server);
        const SDL_Rect GetBody();
        void Update(char *dataIn);
        void Move(const Direction direction);
        void Render();

    private:
        void SendStateToClient(char *dataOut);
        char mFlag;
        SDL_Rect mBody;
        std::string mName;
        Renderer &mRenderer;
        UDPServer &mServer;
        Player *mPaddleClient;
};


#endif

