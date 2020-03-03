#include "udp_server.h"
#include <unistd.h>

UDPServer::UDPServer(std::shared_ptr<UDPSocket> &socket) : player1(nullptr), player2(nullptr) {
    udp_socket = socket;
    udp_socket->Bind();
}

UDPServer::~UDPServer() {
    delete player1;
    delete player2;
}

void UDPServer::WaitForPlayerConnections() {
    std::cout << "Waiting For Players To Connect..." << std::endl;
    
    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket->GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket->GetSocketHandle();

    while (true) {
        fd_set reads;
        reads = master;

        // select is non-blocking on multiple incoming connections but waits until ready
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
        }

        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            struct sockaddr_storage playerAddress;
            socklen_t player_len = sizeof(playerAddress);

            char read[128];
            int bytes = recvfrom(udp_socket->GetSocketHandle(), read, 3, 0,
                                 (struct sockaddr*)&playerAddress, &player_len);

            if (bytes < 1) {
                std::cerr << "connection closed." << GETSOCKETERRNO() << std::endl;
            }
            
            if (read[0] == 'R' && read[1] == 'D' && read[2] == 'Y') {
                std::cout << "Player RDY" << std::endl;
                
                
                // Maybe a data race here potentially...
                if (player1 == nullptr) {
                    char conn1[7] = {'P','1','C','O','N','N', '\0'};
                    player1 = new Player{playerAddress, "P1"};
                    sendto(udp_socket->GetSocketHandle(), conn1, strlen(conn1),0, 
                          (struct sockaddr*)&player1->address, sizeof(player1->address));
                } else {
                    char conn2[7] = {'P','2','C','O','N','N', '\0'};
                    player2 = new Player{playerAddress, "P2"};
                    sendto(udp_socket->GetSocketHandle(), conn2, strlen(conn2),0, 
                          (struct sockaddr*)&player1->address, sizeof(player1->address));
                    usleep(3000000);
                    break;
                }
                
            }
        }
    }

    std::cout << "Players Connected (2). " << std::endl;        

}

void UDPServer::GetClientPaddleUpdates() {
    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket->GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket->GetSocketHandle();

    while (true) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
        }
        // Paddle Update from a Client
        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            udp_socket->Receive();
        }
    }
}
