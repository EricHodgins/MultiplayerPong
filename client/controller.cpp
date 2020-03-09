#include "controller.h"

void Controller::HandleInput(Paddle &paddle, UDPClient &client) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            SendQuitToServer(client);
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                    paddle.Move(UP);
                    break;
                case SDLK_DOWN:
                    paddle.Move(DOWN);
                    break;
                default:
                    break;
            }
        }
    }
}

void Controller::SendQuitToServer(UDPClient &client) {
    char quitFlag = 'Q';
    int dataSize = sizeof(char);

    int bytes_sent = sendto(client.GetSocket()->GetSocketHandle(), &quitFlag, dataSize, 0,
                            client.GetSocket()->GetAddressInfo()->ai_addr,
                            client.GetSocket()->GetAddressInfo()->ai_addrlen);

    if (bytes_sent < 0) {
        std::cout << "Controller::SendQuitToServer failed." << std::endl;
    }
}
