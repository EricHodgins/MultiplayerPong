#include "Game.h"
#include "Renderer.h"

int main(int argc, char *argv[]) {
    Renderer renderer = Renderer(640, 480);
    Game game;
    game.Update(renderer);

    return 0;
}
