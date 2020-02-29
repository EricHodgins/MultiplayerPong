#include <thread>
#include <future>
#include "Game.h"
#include "../shared/Renderer.h"
#include "udp_server.h"

int main(int argc, char *argv[]) {
    
    std::shared_ptr<UDPSocket> socket(new UDPSocket("0", "8080"));
    UDPServer udp_server(socket);
    udp_server.WaitForPlayerConnections();
    
    std::thread network_thread = std::thread(&UDPServer::GetClientPaddleUpdates, udp_server);
    std::cout << "Simulating Game..." << std::endl;

    Renderer renderer = Renderer(640, 480);
    Game game;
    game.Update(renderer, udp_server);
    
    network_thread.join();
    return 0;
}
