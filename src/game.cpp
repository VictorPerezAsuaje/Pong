#include <iostream>

#include "game.h"
#include "ball.h"
#include "player.h"

using namespace std;

class Ball;   // Forward declaration of Ball
class Player; // Forward declaration of Player

Game::Game(int screenWidth, int screenHeight)
{
    ScreenWidth = screenWidth;
    ScreenHeight = screenHeight;

    LimitLeft = 0;
    LimitRight = screenWidth;
    LimitTop = 0;
    LimitBottom = screenHeight;

    NumberOfP1Wins = 0;
    NumberOfP2Wins = 0;

    CurrentGameEnded = false;
    CurrentGameWinner = "";
}

Ball Game::CreateBall()
{
    return Ball(ScreenWidth, ScreenHeight);
}

Player Game::CreatePlayerOne()
{
    return Player(ScreenWidth, ScreenHeight, true);
}

Player Game::CreatePlayerTwo()
{
    return Player(ScreenWidth, ScreenHeight, false);
}

int Game::GetScreenHeight()
{
    return ScreenHeight;
}

int Game::GetScreenWidth()
{
    return ScreenWidth;
}

int Game::GetLimitBottom()
{
    return LimitBottom;
}

int Game::GetLimitLeft()
{
    return LimitLeft;
}

int Game::GetLimitTop()
{
    return LimitTop;
}

int Game::GetLimitRight()
{
    return LimitRight;
}

int Game::GetPlayerOneWins()
{
    return NumberOfP1Wins;
}

int Game::GetPlayerTwoWins()
{
    return NumberOfP2Wins;
}

void Game::UpdateGameStatus(Ball &ball, Player &playerOne, Player &playerTwo)
{
    int paddleWidth = playerOne.GetPaddleWidth();
    int paddleHeight = playerOne.GetPaddleHeight();

    // Check if crashes with paddle P1
    if (ball.GetXPosition() - ball.GetXSpeed() <= playerOne.GetXPosition() + paddleWidth && ball.IsGoingLeft())
    {
        if (ball.GetYPosition() > playerOne.GetYPosition() && ball.GetYPosition() < playerOne.GetYPosition() + paddleHeight)
        {
            ball.UpdateDirection(false);
            return;
        }

        if (!CurrentGameEnded)
        {
            NumberOfP2Wins += 1;
            CurrentGameEnded = true;
            CurrentGameWinner = "Player Two";
        }
    }

    // Check if crashes with paddle two
    if (ball.GetXPosition() + ball.GetXSpeed() >= playerTwo.GetXPosition() && !ball.IsGoingLeft())
    {
        if (ball.GetYPosition() > playerTwo.GetYPosition() && ball.GetYPosition() < playerTwo.GetYPosition() + paddleHeight)
        {
            ball.UpdateDirection(true);
            return;
        }

        if (!CurrentGameEnded)
        {
            NumberOfP1Wins += 1;
            CurrentGameEnded = true;
            CurrentGameWinner = "Player One";
        }
    }
}

bool Game::IsGameOver()
{
    return CurrentGameEnded;
}

string Game::GetWinner()
{
    return CurrentGameWinner;
}

void Game::ResetGame()
{
    CurrentGameEnded = false;
    CurrentGameWinner = "";
}