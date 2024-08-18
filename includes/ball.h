#ifndef BALL_H
#define BALL_H

#include <stdlib.h>
#include <string>

using namespace std;

class GameOverDTO
{
public:
    GameOverDTO(bool endgame, string winner)
    {
        Endgame = endgame;
        Winner = winner;
    }

    bool Endgame;
    string Winner;
};

class Ball
{
public:
    Ball(int screenWidth, int screenHeight);
    int GetSize();
    int GetXPosition();
    int GetYPosition();

    bool IsGoingLeft();

    void CalculateYPosition();
    GameOverDTO IsGameOver(int playerOneXPosition, int playerOneYPosition, int playerTwoXPosition, int playerTwoYPosition, int paddleWidth, int paddleHeight);

private:
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