#include <iostream>
#include "player.h"

Player::Player(int screenHeight, int screenWidth, KeyboardKey up, KeyboardKey down, int maxTopPosition, int maxBottomPosition, bool isPlayerOne)
{
    PaddleHeight = screenHeight / 5;
    PaddleWidth = 10;
    PaddleSpeed = 5;

    Up = up;
    Down = down;

    MaxTopPosition = maxTopPosition;
    MaxBottomPosition = maxBottomPosition - PaddleHeight;

    YPosition = screenHeight / 2;
    XPosition = isPlayerOne ? 0 : screenWidth - PaddleWidth;
}

void Player::UpdatePosition()
{
    if (IsKeyDown(Up))
    {
        YPosition = YPosition - PaddleSpeed > MaxTopPosition ? YPosition - PaddleSpeed : MaxTopPosition;
    }

    if (IsKeyDown(Down))
    {
        YPosition = YPosition + PaddleSpeed < MaxBottomPosition ? YPosition + PaddleSpeed : MaxBottomPosition;
    }
}

int Player::GetXPosition()
{
    return XPosition;
}

int Player::GetYPosition()
{
    return YPosition;
}

int Player::GetPaddleHeight()
{
    return PaddleHeight;
}

int Player::GetPaddleWidth()
{
    return PaddleWidth;
}