#include "udp_socket.h"

// Used on server side
UDPSocket::UDPSocket(const std::string address, const std::string port) {
    std::cout << "Configuring UDP Socket at address: " << address <<
                 " and port: " << port << std::endl;

    struct addrinfo hints;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(address.c_str(), port.c_str(), &hints, &bind_address);

    std::cout << "Creating UDP socket..." << std::endl;
    mSocket = socket(bind_address->ai_family, bind_address->ai_socktype, bind_address->ai_protocol);
    
    if (!ISVALIDSOCKET(mSocket)) {
        std::cerr << "socket() failed. (" << GETSOCKETERRNO() << ")";
    }
}

UDPSocket::~UDPSocket() {
    freeaddrinfo(bind_address);
    CLOSESOCKET(mSocket);
}

void UDPSocket::Bind() {
    std::cout << "Binding socket..." << std::endl;
    
    if (bind(mSocket, bind_address->ai_addr, bind_address->ai_addrlen)) {
        std::cerr << "bind() failed. (" << GETSOCKETERRNO() << ")" << std::endl;
    }
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
    return bind_address;
}
