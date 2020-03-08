#include "Paddle.h"

Paddle::Paddle(Renderer &renderer, std::string pFlag, UDPServer &server): mRenderer(renderer), mServer(server) {
    if (pFlag == "P1") {
        mBody.x = 30;
        mFlag = '1';
        mPaddleClient = server.getPlayer2();
    } else {
        mBody.x = 620;
        mFlag = '2';
        mPaddleClient = server.getPlayer1();
    }
    mName = pFlag;
    mBody.y = 100;
    mBody.w = PADDLE_WIDTH;
    mBody.h = PADDLE_HEIGHT;
}

void Paddle::Move(const Direction direction) {
    if (direction == UP) {
        mBody.y -= PADDLE_VEL;
    } else if (direction == DOWN) {
        mBody.y += PADDLE_VEL;
    }
};

const SDL_Rect Paddle::GetBody() {
    return mBody;
}

void Paddle::Render() {
    SDL_SetRenderDrawColor(mRenderer.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(mRenderer.getRenderer(), &mBody);
}

void Paddle::Update(char *dataIn) {
    mBody.y = *(int*)(dataIn + sizeof(char));
    std::cout << "Paddle::Update --> " << (*(int*)(dataIn + sizeof(char))) << std::endl;
    SendStateToClient(dataIn);
}

void Paddle::SendStateToClient(char *dataOut) {
    int dataSize = sizeof(char) + sizeof(float)*2;
    int bytes_sent = sendto(mServer.GetSocket()->GetSocketHandle(), dataOut, dataSize, 0,
                            (struct sockaddr*)&mPaddleClient->address, sizeof(mPaddleClient->address));
   
    std::cout << "Bytes to Paddle Client: " << bytes_sent << std::endl;
}

