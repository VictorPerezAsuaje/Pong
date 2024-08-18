#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <raylib.h>
#include <string>

using namespace std;

class Player
{
public:
    Player(int screenHeight, int screenWidth, KeyboardKey up, KeyboardKey down, int maxTopPosition, int maxBottomPosition, bool isPlayerOne);

    int GetXPosition();
    int GetYPosition();
    int GetPaddleHeight();
    int GetPaddleWidth();

    void UpdatePosition();

private:
    int PaddleHeight;
    int PaddleWidth;
    int PaddleSpeed;

    int MaxTopPosition;
    int MaxBottomPosition;

    KeyboardKey Up;
    KeyboardKey Down;

    int YPosition;
    int XPosition;
};

#endif