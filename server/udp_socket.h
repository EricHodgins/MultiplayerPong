#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <iostream>
#include "cplatform.h"
#include <ctype.h>

class UDPSocket {
    public:
        // Configure socket at init
        UDPSocket(const std::string address, const std::string port);
        ~UDPSocket();
        void Bind();
        void Receive();
        SOCKET GetSocketHandle() { return mSocket; }

    private:
        struct addrinfo *bind_address;
        SOCKET mSocket;
};

#endif
