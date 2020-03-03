#include <thread>
#include <future>
#include "Game.h"
#include "../shared/Renderer.h"
#include "udp_server.h"
#include "Ball.h"

int main(int argc, char *argv[]) {
    
    std::shared_ptr<UDPSocket> socket(new UDPSocket("0", "8080"));
    UDPServer udp_server(socket);
    udp_server.WaitForPlayerConnections();

    //std::thread network_thread = std::thread(&UDPServer::GetClientPaddleUpdates, udp_server);
    std::cout << "Simulating Game..." << std::endl;

    Renderer renderer = Renderer(640, 480);

    LTexture ballTexture(renderer);
    ballTexture.loadFromFile("../shared/dot.bmp");
    Ball ball(renderer, ballTexture, udp_server);

    std::future<void> fut = std::async(std::launch::async, &UDPServer::GetClientPaddleUpdates, &udp_server);

    Game game;
    game.Update(renderer, udp_server);
    
    fut.get(); 
    return 0;
}
