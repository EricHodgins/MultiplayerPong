#ifndef UDPServer_H
#define UDPServer_H

#include <iostream>
#include <string>
#include <thread>
#include "../shared/cplatform.h"
#include "udp_socket.h"
#include "Paddle.h"

class Paddle;

struct Player {
    struct sockaddr_storage address;
    std::string name;
};

class UDPServer {
    public:
        UDPServer(std::shared_ptr<UDPSocket> &socket);
        ~UDPServer();
        std::shared_ptr<UDPSocket> GetSocket() { return udp_socket; }
        void WaitForPlayerConnections();
        void GetClientPaddleUpdates();
        Player* getPlayer1() { return player1; }
        Player* getPlayer2() { return player2; }
        void SetPaddle1(Paddle *paddle);
        void SetPaddle2(Paddle *paddle);
        
    private:
        std::shared_ptr<UDPSocket> udp_socket;
        Player *player1, *player2;
        Paddle *mPaddle1, *mPaddle2;
};

#endif
