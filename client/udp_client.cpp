#include "udp_client.h"

UDPClient::UDPClient(std::shared_ptr<UDPSocket> socket) : udp_socket(socket), mBall(NULL) {}

void UDPClient::SendRDYToServer() {
    char read[4] = {'R', 'D', 'Y', '\0'};
    int bytes_sent = sendto(udp_socket->GetSocketHandle(), read, strlen(read),0,
                            udp_socket->GetAddressInfo()->ai_addr, 
                            udp_socket->GetAddressInfo()->ai_addrlen);

    std::cout << "RDY sent: " << bytes_sent << " bytes" << std::endl;
}

void UDPClient::SetBall(Ball *ball) {
    mBall = ball;    
}

void UDPClient::SetPaddle(Paddle *paddle) {
    mPaddle = paddle;
}

void UDPClient::SetGame(Game *game) {
    mGame = game;
}

void UDPClient::UpdateBall(char *ballData) {
    float posX = *(float*)(ballData + sizeof(char));
    float posY = *(float*)(ballData + sizeof(char) + sizeof(float));
    float velX = *(float*)(ballData + sizeof(char) + sizeof(float)*2);
    float velY = *(float*)(ballData + sizeof(char) + sizeof(float)*3);
    
    //std::cout << "posX: " << posX << ", " << posY << ", " << velX << ", " << velY << std::endl;
    mBall->Update(posX, posY, velX, velY);
}

void UDPClient::UpdatePaddle(char *paddleData) {
    int posY = *(int*)(paddleData + sizeof(char));
    std::cout << "Paddle data received, posY: " << posY << std::endl;
    mPaddle->Update(posY);
}

std::string UDPClient::GetRDYResponse() {
    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket->GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket->GetSocketHandle();

    int maxPacketSize = sizeof(char)*2; 
    char readIn[maxPacketSize]; // Max Size of packet coming in
    std::string player = "";
    while (true) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
        }
    
        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            recv(udp_socket->GetSocketHandle(), readIn, maxPacketSize, 0);
            player = std::string(readIn, 2);
            break;
        }
    }

    return player;
}

void UDPClient::GetUpdates() {
    fd_set master;
    FD_ZERO(&master);
    FD_SET(udp_socket->GetSocketHandle(), &master);
    SOCKET max_socket = udp_socket->GetSocketHandle();

    int maxPacketSize = sizeof(char) + sizeof(float)*4;
    char readIn[maxPacketSize]; // Max Size of packet coming in

    while (true) {
        fd_set reads;
        reads = master;
        if (select(max_socket+1, &reads, 0, 0, 0) < 0) {
            std::cerr << "select() failed. " << GETSOCKETERRNO() << std::endl;
        }
        // Ball, Paddle, Quit Updates from server
        if (FD_ISSET(udp_socket->GetSocketHandle(), &reads)) {
            recv(udp_socket->GetSocketHandle(), readIn, maxPacketSize, 0);
            char object_flag = readIn[0];
            if (object_flag == 'B') {
                UpdateBall(readIn);                 
            } else if (object_flag == '1' || object_flag == '2') {
                UpdatePaddle(readIn);
            } else if (readIn[0] == 'Q') {
                std::cout << "Quit received from server..." << std::endl;
                mGame->Quit();
                break;
            }
        }
    }
}
