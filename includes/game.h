#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "player.h"
#include "ball.h"

using namespace std;

class Ball;   // Forward declaration of Ball
class Player; // Forward declaration of Player

class Game
{
public:
    Game(int screenWidth, int screenHeight);

    int GetScreenWidth();
    int GetScreenHeight();

    int GetLimitLeft();
    int GetLimitRight();
    int GetLimitTop();
    int GetLimitBottom();

    int GetPlayerOneWins();
    int GetPlayerTwoWins();

    Ball CreateBall();
    Player CreatePlayerOne();
    Player CreatePlayerTwo();

    void UpdateGameStatus(Ball &ball, Player &playerOne, Player &playerTwo);
    bool IsGameOver();
    string GetWinner();
    void ResetGame();

private:
    int ScreenWidth;
    int ScreenHeight;

    int LimitLeft;
    int LimitRight;
    int LimitTop;
    int LimitBottom;

    bool CurrentGameEnded;
    string CurrentGameWinner;

    int NumberOfP1Wins;
    int NumberOfP2Wins;
};

#endif
