#include <thread>
#include <future>
#include "Game.h"
#include "../shared/Renderer.h"
#include "udp_client.h"

int main(int argc, char *argv[]) {
    std::shared_ptr<UDPSocket> socket(new UDPSocket("127.0.0.1", "8080"));
    UDPClient udp_client(socket);
    udp_client.SendRDYToServer();
    std::future<std::string> srvResp = std::async(std::launch::async, &UDPClient::GetRDYResponse, &udp_client);
    std::string playerName = srvResp.get(); 
    std::cout << "Player Name: " << playerName << std::endl;

    //std::thread network_thread = std::thread(&UDPClient::GetUpdates, &udp_client);
    std::future<void> network_thread = std::async(std::launch::async, &UDPClient::GetUpdates, &udp_client);

    Renderer renderer = Renderer(640, 480);
    std::string windowTitle = "Multiplayer Pong (CLIENT): " + playerName;
    renderer.setWindowTitle(windowTitle);
    Game game;
    udp_client.SetGame(&game);
    game.Update(renderer, udp_client, playerName);

    //network_thread.join();
    network_thread.get();

    return 0;
}
