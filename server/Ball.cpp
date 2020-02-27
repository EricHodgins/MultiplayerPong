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

void Ball::sendStateToClients() {
    std::cout << "Sending Ball position..." << std::endl;

    std::string x = std::to_string(mPosX); 
    sendto(mServer.GetSocket()->GetSocketHandle(), x.c_str(), strlen(x.c_str()), 0,
           (struct sockaddr*)&mServer.getPlayer1()->address,
           sizeof(mServer.getPlayer1()->address));

}
