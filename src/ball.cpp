#include <iostream>
#include "ball.h"
#include "player.h"

Ball::Ball(int screenWidth, int screenHeight)
{
    Size = 10;

    XPosition = screenWidth / 2;
    YPosition = screenHeight / 2;

    YSpeed = rand() % 5 + 5;
    XSpeed = rand() % 5 + 5;

    GoesTop = rand() % 100 < 50;
    GoesLeft = rand() % 100 < 50;

    LimitLeft = 0;
    LimitRight = screenWidth;

    LimitTop = 0;
    LimitBottom = screenHeight;
}

int Ball::GetSize()
{
    return Size;
}

int Ball::GetXPosition()
{
    return XPosition;
}

int Ball::GetYPosition()
{
    return YPosition;
}

bool Ball::IsGoingLeft()
{
    return GoesLeft;
}

void Ball::Draw()
{
    DrawCircle(XPosition, YPosition, Size, WHITE);
}

void Ball::UpdatePosition()
{
    YPosition = GoesTop ? YPosition - YSpeed : YPosition + YSpeed;

    if (YPosition + YSpeed > LimitBottom || GoesTop)
    {
        GoesTop = true;
    }

    if (YPosition - YSpeed < LimitTop || !GoesTop)
    {
        GoesTop = false;
    }

    XPosition = GoesLeft ? XPosition - XSpeed : XPosition + XSpeed;
}

void Ball::UpdateDirection(bool goesLeft)
{
    GoesLeft = goesLeft;
}

int Ball::GetXSpeed()
{
    return XSpeed;
}

int Ball::GetYSpeed()
{
    return YSpeed;
}