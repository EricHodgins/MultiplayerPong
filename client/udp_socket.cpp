#include "udp_socket.h"

// Used on Client Side
UDPSocket::UDPSocket(std::string address, std::string port) {
    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_DGRAM;

    if (getaddrinfo(address.c_str(), port.c_str(), &hints, &mServer_address)) {
        std::cerr << "getaddrinfo() failed. " << GETSOCKETERRNO() << std::endl;
    }

    char address_buffer[100];
    char service_buffer[100];
    getnameinfo(mServer_address->ai_addr, mServer_address->ai_addrlen,
                address_buffer, sizeof(address_buffer),
                service_buffer, sizeof(service_buffer),
                NI_NUMERICHOST | NI_NUMERICSERV);

    mSocket = socket(mServer_address->ai_family, mServer_address->ai_socktype, mServer_address->ai_protocol);
    if (!ISVALIDSOCKET(mSocket)) {
        std::cerr << "socket() failed. " << GETSOCKETERRNO() << std::endl;
    }

    std::cout << "Server address is: " << std::string(address_buffer) << ":" << std::string(service_buffer)
    << std::endl;
}

UDPSocket::~UDPSocket() {
    freeaddrinfo(mServer_address);
    CLOSESOCKET(mSocket);
}

void UDPSocket::Receive() {
    std::cout << "Receiving. Socket ready to be read." << std::endl;

    struct sockaddr_storage client_address;
    socklen_t client_len = sizeof(client_address);

    char read[128];
    int bytes_received = recvfrom(mSocket, read, 128, 0,
                                 (struct sockaddr*)&client_address, &client_len);
    if (bytes_received < 1) {
        std::cout << "connection closed. " << GETSOCKETERRNO() << std::endl;
    }

    std::cout << "received data: ";
    for (int i = 0; i < bytes_received; i++) {        
        std::cout << read[i] << " ";
    }

    std::cout << std::endl;
}

struct addrinfo* UDPSocket::GetAddressInfo() {
    return mServer_address;
}
