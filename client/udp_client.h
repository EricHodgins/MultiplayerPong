#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include "Ball.h"
#include "Paddle.h"
#include "Game.h"
#include "udp_socket.h"
#include "../shared/cplatform.h"

class Ball;
class Paddle;
class Game;

class UDPClient {
    
    public:
        UDPClient(std::shared_ptr<UDPSocket> socket);
        void SendRDYToServer();
        void SendPaddlePositionToServer();
        void GetUpdates();
        std::string GetRDYResponse();
        void SetBall(Ball *ball);
        void SetPaddle(Paddle *paddle);
        void SetGame(Game *game);
        void GetObjectFlag();
        void UpdateBall(char *ballData);
        void UpdatePaddle(char *paddleData);
        std::shared_ptr<UDPSocket> GetSocket() { return udp_socket; }

    private:
        std::shared_ptr<UDPSocket> udp_socket;
        Ball *mBall;
        Paddle *mPaddle;
        Game *mGame;
};

#endif
