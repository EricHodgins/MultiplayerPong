#ifndef UDPServer_H
#define UDPServer_H

#include <iostream>
#include <string>
#include <thread>
#include "cplatform.h"
#include "udp_socket.h"

struct Player {
    struct sockaddr_storage address;
    std::string name;
};

class UDPServer {
    public:
        UDPServer(std::shared_ptr<UDPSocket> &socket);
        ~UDPServer();
        SOCKET GetSocket() { return udp_socket->GetSocketHandle(); }
        void WaitForPlayerConnections();

    private:
        std::shared_ptr<UDPSocket> udp_socket;
        Player *player1, *player2;        
};

#endif
