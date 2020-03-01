#ifndef UDPServer_H
#define UDPServer_H

#include <iostream>
#include <string>
#include <thread>
#include "../shared/cplatform.h"
#include "../shared/udp_socket.h"

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

    private:
        std::shared_ptr<UDPSocket> udp_socket;
        Player *player1, *player2;        
};

#endif
