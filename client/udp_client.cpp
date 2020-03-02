#include "udp_client.h"

UDPClient::UDPClient(std::shared_ptr<UDPSocket> socket) : udp_socket(socket) {}

void UDPClient::SendRDYToServer() {
    char read[4] = {'R', 'D', 'Y', '\0'};
    int bytes_sent = sendto(udp_socket->GetSocketHandle(), read, strlen(read),0,
                            udp_socket->GetAddressInfo()->ai_addr, 
                            udp_socket->GetAddressInfo()->ai_addrlen);

    std::cout << "RDY sent: " << bytes_sent << " bytes" << std::endl;
}

void UDPClient::GetBallUpdates() {
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
        // Ball Update from server
        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            udp_socket->Receive();
        }
    }

}
