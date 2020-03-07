#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include "Ball.h"
#include "udp_socket.h"
#include "../shared/cplatform.h"

class Ball;

class UDPClient {
    
    public:
        UDPClient(std::shared_ptr<UDPSocket> socket);
        void SendRDYToServer();
        void SendPaddlePositionToServer();
        void GetUpdates();
        void SetBall(Ball *ball);
        void GetObjectFlag();
        void UpdateBall(char *ballData);
        std::shared_ptr<UDPSocket> GetSocket() { return udp_socket; }

    private:
        std::shared_ptr<UDPSocket> udp_socket;
        Ball *mBall;
};

#endif
