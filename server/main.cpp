#include "Game.h"
#include "Renderer.h"
#include "udp_server.h"

int main(int argc, char *argv[]) {
    
    std::shared_ptr<UDPSocket> socket(new UDPSocket("0", "8080"));
    UDPServer udp_server(socket);
    udp_server.WaitForPlayerConnections();
/*
    Renderer renderer = Renderer(640, 480);
    Game game;
    game.Update(renderer);
*/
    return 0;
}
