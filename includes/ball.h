#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include <string>

#include "player.h"

using namespace std;

class Ball
{
    friend class Game;

public:
    int GetSize();
    int GetXPosition();
    int GetYPosition();

    int GetXSpeed();
    int GetYSpeed();

    bool IsGoingLeft();

    void UpdatePosition();
    void UpdateDirection(bool goesLeft);
    void Draw();

private:
    Ball(int screenWidth, int screenHeight);

    int XPosition;
    int YPosition;
    int Size;

    int YSpeed;
    int XSpeed;
    bool GoesTop;
    bool GoesLeft;

    int LimitLeft = 0;
    int LimitRight;
    int LimitTop = 0;
    int LimitBottom;
};

#endif