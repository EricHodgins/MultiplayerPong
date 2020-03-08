#include "Paddle.h"

Paddle::Paddle(Renderer &renderer, const std::string pFlag, UDPClient &client): mRenderer(renderer), mClient(client) {
    if (pFlag == "P1") {
        mBody.x = 30;
        mFlag = '1';
    } else {
        mBody.x = 620;
        mFlag = '2';
    }

    mBody.y = 100;
    mBody.w = PADDLE_WIDTH;
    mBody.h = PADDLE_HEIGHT;
}

bool Paddle::isFirstPlayer() {
    return mFlag == '1';
}

void Paddle::Move(const Direction direction) {
    if (direction == UP) {
        mBody.y -= PADDLE_VEL;
    } else if (direction == DOWN) {
        mBody.y += PADDLE_VEL;
    }

    SendStateToServer();
};

const SDL_Rect Paddle::GetBody() {
    return mBody;
}

void Paddle::Update(int posY) {
    mBody.y = posY;
}

void Paddle::Render() {
    SDL_SetRenderDrawColor(mRenderer.getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(mRenderer.getRenderer(), &mBody);
}

char* Paddle::SerializeOut() {
    char *buffer = 0;
    buffer = static_cast<char*>(std::realloc(buffer, sizeof(int)*2 + sizeof(char)));
    memcpy(buffer, &mFlag, sizeof(char));
    memcpy(buffer + sizeof(char), &mBody.y, sizeof(int));
    memcpy(buffer + sizeof(char) + sizeof(int), &PADDLE_VEL, sizeof(int));
    
    return buffer;
}

void Paddle::SendStateToServer() {
   char *paddleData = SerializeOut(); 
   int dataSize = sizeof(char) + sizeof(float)*2;

   int bytes_sent = sendto(mClient.GetSocket()->GetSocketHandle(), paddleData, dataSize, 0,
                           mClient.GetSocket()->GetAddressInfo()->ai_addr,
                           mClient.GetSocket()->GetAddressInfo()->ai_addrlen);
    
   std::cout << "Paddle Bytes Sent: " << bytes_sent << std::endl;
}
