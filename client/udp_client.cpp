#include "udp_client.h"

void UDPClient::ConnectToServer() {
    std::cout << "Connecting to server..." << std::endl;
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;
    struct addrinfo *peer_address;

    if (getaddrinfo("127.0.0.1", "8080", &hints, &peer_address)) {
        std::cerr << "getaddrinfo() failed. " << GETSOCKETERRNO() << std::endl;
    }

    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(peer_address->ai_addr, peer_address->ai_addrlen,
                address_buffer, sizeof(address_buffer),
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST | NI_NUMERICSERV);

    std::cout << "Server address is: " << std::string(address_buffer) << ":" << std::string(service_buffer)
    << std::endl;


}
