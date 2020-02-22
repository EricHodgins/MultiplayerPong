#include <iostream>
#include "cplatform.h"
#include "udp_socket.h"
#include <ctype.h>

int main(int argc, char *argv[]) {
    std::cout << "Configuring local address..." << std::endl;
    
    UDPSocket udp_socket("0", "8080");
    udp_socket.Bind();
    
    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket.GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket.GetSocketHandle();

    std::cout << "waiting for connections..." << std::endl;
    while (true) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
            return 1;
        }

        if (FD_ISSET(udp_socket.GetSocketHandle(), &reads)) {
            udp_socket.Receive();
        }
    }

    return 0;
}
