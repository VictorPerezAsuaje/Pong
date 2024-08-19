#include <iostream>

#include "player.h"
#include "game.h"

Player::Player(int screenWidth, int screenHeight, bool isPlayerOne)
{
    PaddleHeight = screenHeight / 5;
    PaddleWidth = 10;
    PaddleSpeed = 5;

    IsPlayerOne = isPlayerOne;
    Up = isPlayerOne ? KEY_W : KEY_UP;
    Down = isPlayerOne ? KEY_S : KEY_DOWN;

    MaxTopPosition = 0;
    MaxBottomPosition = screenHeight - PaddleHeight;

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

void Player::Draw()
{
    DrawRectangle(XPosition, YPosition, PaddleWidth, PaddleHeight, IsPlayerOne ? RED : BLUE);
}