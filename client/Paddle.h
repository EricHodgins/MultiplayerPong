#ifndef PADDLE_H
#define PADDLE_H

#include "SDL2/SDL.h"
#include "udp_client.h"
#include "../shared/Renderer.h"
#include <string>

class UDPClient;

enum Direction {
    UP, DOWN 
};


class Paddle {
    public:
        static const int PADDLE_WIDTH = 15;
        static const int PADDLE_HEIGHT = 120;
        static constexpr float PADDLE_VEL = 20.0f;

        Paddle(Renderer &renderer, const std::string pFlag, UDPClient &client);
        bool isFirstPlayer();
        const SDL_Rect GetBody();
        void Move(const Direction direction);
        void Render();
        void Update(int posY);
        void SetScore(int newScore) { mScore = newScore; }
        int GetScore() { return mScore; }

    private:
        void SendStateToServer();
        char* SerializeOut();
        char mFlag;
        SDL_Rect mBody;
        Renderer &mRenderer;
        UDPClient &mClient;
        float mPosX, mPosY;
        int mScore;
};


#endif

