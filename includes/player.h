#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <raylib.h>
#include <string>

#include "game.h"

using namespace std;

class Player
{
    friend class Game;

public:
    int GetXPosition();
    int GetYPosition();
    int GetPaddleHeight();
    int GetPaddleWidth();

    void Draw();
    void UpdatePosition();

private:
    Player(int screenWidth, int screenHeight, bool isPlayerOne);

    int PaddleHeight;
    int PaddleWidth;
    int PaddleSpeed;

    int MaxTopPosition;
    int MaxBottomPosition;

    KeyboardKey Up;
    KeyboardKey Down;

    int YPosition;
    int XPosition;
    bool IsPlayerOne;
};

#endif