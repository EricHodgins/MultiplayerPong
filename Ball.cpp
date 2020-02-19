#include "Ball.h"

Ball::Ball(Renderer &renderer, LTexture &ballTexture) : mRenderer(renderer), mBallTexture(ballTexture) {
    mPosX = 0;
    mPosY = 0;

    mCollider.w = BALL_WIDTH;
    mCollider.h = BALL_HEIGHT;

    mVelX = 0;
    mVelY = 0;
}

void Ball::move(SDL_Rect &wall) {
    //Move the dot left or right
    mPosX += mVelX;
	mCollider.x = mPosX;

    //If the dot collided or went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + BALL_WIDTH > mRenderer.getScreenWidth()) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosX -= mVelX;
		mCollider.x = mPosX;
    }

    //Move the dot up or down
    mPosY += mVelY;
	mCollider.y = mPosY;

    //If the dot collided or went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BALL_HEIGHT > mRenderer.getScreenHeight()) || checkCollision( mCollider, wall ) )
    {
        //Move back
        mPosY -= mVelY;
		mCollider.y = mPosY;
    }
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

