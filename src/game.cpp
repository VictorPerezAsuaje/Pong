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
    Vector2 ballVector = Vector2{
        x : static_cast<float>(ball.GetXPosition()),
        y : static_cast<float>(ball.GetYPosition())
    };

    Rectangle playerOneRect = Rectangle{
        x : static_cast<float>(playerOne.GetXPosition()),
        y : static_cast<float>(playerOne.GetYPosition()),
        width : static_cast<float>(playerOne.GetPaddleWidth()),
        height : static_cast<float>(playerOne.GetPaddleHeight())
    };

    Rectangle playerTwoRect = Rectangle{
        x : static_cast<float>(playerTwo.GetXPosition()),
        y : static_cast<float>(playerTwo.GetYPosition()),
        width : static_cast<float>(playerTwo.GetPaddleWidth()),
        height : static_cast<float>(playerTwo.GetPaddleHeight())
    };

    if (CheckCollisionCircleRec(ballVector, ball.GetSize(), playerOneRect))
    {
        ball.UpdateDirection(false);
        return;
    }

    if (CheckCollisionCircleRec(ballVector, ball.GetSize(), playerTwoRect))
    {
        ball.UpdateDirection(true);
        return;
    }

    // Ball just moving through the space
    if (ball.GetXPosition() > 0 && ball.GetXPosition() < ScreenWidth)
    {
        return;
    }

    if (CurrentGameEnded)
    {
        return;
    }

    CurrentGameEnded = true;

    if (ball.IsGoingLeft())
    {
        NumberOfP2Wins += 1;
        CurrentGameWinner = "Player Two";
        return;
    }

    NumberOfP1Wins += 1;
    CurrentGameWinner = "Player One";
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