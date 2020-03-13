#ifndef UDP_SOCKET_H
#define UDP_SOCKET_H

#include <iostream>
#include <string>
#include "../shared/cplatform.h"
#include <ctype.h>

class UDPSocket {
    public:
        // Configure socket at init
        UDPSocket(std::string address, std::string port);
        ~UDPSocket();
        SOCKET GetSocketHandle() { return mSocket; }
        struct addrinfo* GetAddressInfo();

    private:
        struct addrinfo *mServer_address;
        SOCKET mSocket;
};

#endif
