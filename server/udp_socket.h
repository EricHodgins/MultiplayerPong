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
        void Receive(char *q);
        SOCKET GetSocketHandle() { return mSocket; }
        struct addrinfo* GetAddressInfo();

    private:
        struct addrinfo *bind_address;
        SOCKET mSocket;
};

#endif
