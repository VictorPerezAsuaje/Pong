#include "ball.h"
#include <iostream>

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

void Ball::CalculateYPosition()
{
    cout << "I'm in" << endl;
    YPosition = GoesTop ? YPosition - YSpeed : YPosition + YSpeed;

    if (YPosition + YSpeed > LimitBottom || GoesTop)
    {
        GoesTop = true;
    }

    if (YPosition - YSpeed < LimitTop || !GoesTop)
    {
        GoesTop = false;
    }
}

GameOverDTO Ball::IsGameOver(int playerOneXPosition, int playerOneYPosition, int playerTwoXPosition, int playerTwoYPosition, int paddleWidth, int paddleHeight, bool metadata)
{
    XPosition = GoesLeft ? XPosition - XSpeed : XPosition + XSpeed;

    // Check if crashes with paddle P1
    if (XPosition - XSpeed <= playerOneXPosition + paddleWidth && GoesLeft)
    {
        if (YPosition > playerOneYPosition - paddleHeight / 2 && YPosition < playerOneYPosition + paddleHeight)
        {
            if (metadata)
            {
                cout << "Player one touches ball" << endl;
            }

            GoesLeft = false;
            return GameOverDTO(false, "");
        }

        return GameOverDTO(true, "Player Two");
    }

    if (XPosition + XSpeed >= playerTwoXPosition - paddleWidth && !GoesLeft)
    {
        if (YPosition > playerTwoYPosition - paddleHeight / 2 && YPosition < playerTwoYPosition + paddleHeight)
        {
            if (metadata)
            {
                cout << "Player two touches ball" << endl;
            }

            GoesLeft = true;
            return GameOverDTO(false, "");
        }

        return GameOverDTO(true, "Player One");
    }

    return GameOverDTO(false, "");
}