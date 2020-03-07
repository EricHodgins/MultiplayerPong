#include "Ball.h"

Ball::Ball(Renderer &renderer, LTexture &ballTexture, 
           UDPServer &server) : mRenderer(renderer), 
                                mBallTexture(ballTexture),
                                mServer(server) {
    mPosX = 0;
    mPosY = 0;

    mCollider.w = BALL_WIDTH;
    mCollider.h = BALL_HEIGHT;

    mVelX = BALL_VEL;
    mVelY = BALL_VEL;
}

void Ball::move(SDL_Rect &wall, Uint32 deltaTime) {
    //Move the dot left or right
    mPosX += mVelX * ((float)deltaTime / 1000.0);
	mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + BALL_WIDTH > mRenderer.getScreenWidth()) || checkCollision( mCollider, wall ) )
    {
        mVelX = -mVelX;
    }

    //Move the dot up or down
    mPosY += mVelY * ((float)deltaTime / 1000.0);
	mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BALL_HEIGHT > mRenderer.getScreenHeight()) || checkCollision( mCollider, wall ) )
    {
        mVelY = -mVelY;
    }
}

void Ball::render() {
    mBallTexture.render(mPosX, mPosY);
}

bool Ball::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

char* Ball::SerializeOut() {
    char flag = 'B';
    char *buffer = 0;
    buffer = static_cast<char*>(std::realloc(buffer, sizeof(float)*4 + sizeof(char)));
    memcpy(buffer, &flag, sizeof(char));
    memcpy(buffer + sizeof(char), &mPosX, sizeof(float));
    memcpy(buffer + sizeof(char) + sizeof(float), &mPosY, sizeof(float));
    memcpy(buffer + sizeof(char) + sizeof(float)*2, &mVelX, sizeof(float));
    memcpy(buffer + sizeof(char) + sizeof(float)*3, &mVelY, sizeof(float));

    return buffer;
}

void Ball::sendStateToClients() {

    std::cout << mServer.GetSocket()->GetSocketHandle() << std::endl;

    std::string x = std::to_string(mPosX); 
    char *ballData = SerializeOut();
    int dataSize = sizeof(char) + sizeof(float)*4;
    int bytes_sent1 = sendto(mServer.GetSocket()->GetSocketHandle(), ballData, dataSize, 0,
           (struct sockaddr*)&mServer.getPlayer1()->address,
           sizeof(mServer.getPlayer1()->address));

    int bytes_sent2 = sendto(mServer.GetSocket()->GetSocketHandle(), ballData, dataSize, 0,
           (struct sockaddr*)&mServer.getPlayer2()->address,
           sizeof(mServer.getPlayer2()->address));

    std::cout << "Bytes to Player 1: " << bytes_sent1 << std::endl;
    std::cout << "Bytes to Player 2: " << bytes_sent2 << std::endl;

}
