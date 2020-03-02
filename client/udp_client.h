#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <iostream>
#include <string>
#include <thread>
#include "udp_socket.h"
#include "../shared/cplatform.h"

class UDPClient {
    
    public:
        UDPClient(std::shared_ptr<UDPSocket> socket);
        void SendRDYToServer();
        void SendPaddlePositionToServer();
        void GetBallUpdates(); 
        std::shared_ptr<UDPSocket> GetSocket() { return udp_socket; }

    private:
        std::shared_ptr<UDPSocket> udp_socket;
};

#endif
