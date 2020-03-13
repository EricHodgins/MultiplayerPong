#include "HUD.h"

HUD::HUD(Renderer &renderer) : mRenderer(renderer) {
    mFont = TTF_OpenFont("FreeMono.ttf", 26);
    mColor = {0, 0, 0, 1};
    mRect.x = renderer.getScreenWidth() / 2 - 50;
    mRect.y = 25;
    mRect.w = 25;
    mRect.h = 25;
}

void HUD::RenderScore(Paddle &paddle1, Paddle &paddle2) {
    mRect.x = mRenderer.getScreenWidth() / 2 - 50;
    RenderScore(paddle1);
    mRect.x = mRenderer.getScreenWidth() / 2 + 25;
    RenderScore(paddle2);
}

void HUD::RenderScore(Paddle &paddle) {

    SDL_Surface *surface;
    SDL_Texture *texture;
    
    int score = paddle.GetScore();

    surface = TTF_RenderText_Solid(mFont, std::to_string(score).c_str(), mColor);
    texture = SDL_CreateTextureFromSurface(mRenderer.getRenderer(), surface);

    SDL_FreeSurface(surface);
    SDL_RenderCopy(mRenderer.getRenderer(), texture, NULL, &mRect);
    SDL_DestroyTexture(texture);
}

char* HUD::SerializeScores(const Paddle &p1, const Paddle &p2) const {
    char flag = 'S';
    char *buffer = 0;
    int s1 = p1.GetScore();
    int s2 = p2.GetScore();
    buffer = static_cast<char*>(std::realloc(buffer, sizeof(char) + sizeof(int)*2));
    memcpy(buffer, &flag, sizeof(char));
    memcpy(buffer + sizeof(char), &s1, sizeof(int));
    memcpy(buffer + sizeof(char) + sizeof(int), &s2, sizeof(int));

    return buffer;
}

void HUD::SendScoreToClients(const Paddle &p1, const Paddle &p2, UDPServer &server) {
    char *scoreData = SerializeScores(p1, p2);
    int dataSize = sizeof(char) + sizeof(int)*2;

    int bytes_sent1 = sendto(server.GetSocket()->GetSocketHandle(), scoreData, dataSize, 0,
                           (struct sockaddr*)&server.getPlayer1()->address,
                           sizeof(server.getPlayer1()->address));

    int bytes_sent2 = sendto(server.GetSocket()->GetSocketHandle(), scoreData, dataSize, 0,
                           (struct sockaddr*)&server.getPlayer2()->address,
                           sizeof(server.getPlayer2()->address));

    std::cout << "Score bytes to player 1: " << bytes_sent1 << std::endl;
    std::cout << "Score bytes to player 2: " << bytes_sent2 << std::endl;
}
