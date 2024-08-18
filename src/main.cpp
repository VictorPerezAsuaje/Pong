#include <iostream>
#include <cstring>
#include <raylib.h>
#include <string.h>

#include "ball.h"

using namespace std;

const int screenWidth = 1208;
const int screenHeight = 720;

int limitLeft = 0;
int limitRight = screenWidth;
int limitTop = 0;
int limitBottom = screenHeight;

int paddleHeight = screenHeight / 5;
int paddleWidth = 10;
int paddleSpeed = 5;

int playerOneYPosition;
int playerOneXPosition;
int playerOneBottomLimit;

int playerTwoYPosition;
int playerTwoXPosition;
int playerTwoBottomLimit;

bool metadata = false;

GameOverDTO Status = GameOverDTO(false, "");

void ToggleMetadata()
{
    metadata = !metadata;
}

void PlayerOneController()
{
    if (IsKeyDown(KEY_W))
    {
        if (playerOneYPosition - paddleSpeed > limitTop)
        {
            playerOneYPosition -= paddleSpeed;
        }
        else
        {
            playerOneYPosition = limitTop;
        }
    }

    if (IsKeyDown(KEY_S))
    {
        if (playerOneYPosition + paddleSpeed < playerOneBottomLimit)
        {
            playerOneYPosition += paddleSpeed;
        }
        else
        {
            playerOneYPosition = playerOneBottomLimit;
        }
    }
}

void PlayerTwoController()
{
    if (IsKeyDown(KEY_UP))
    {
        if (playerTwoYPosition - paddleSpeed > limitTop)
        {
            playerTwoYPosition -= paddleSpeed;
        }
        else
        {
            playerTwoYPosition = limitTop;
        }
    }

    if (IsKeyDown(KEY_DOWN))
    {
        if (playerTwoYPosition + paddleSpeed < playerTwoBottomLimit)
        {
            playerTwoYPosition += paddleSpeed;
        }
        else
        {
            playerTwoYPosition = playerTwoBottomLimit;
        }
    }
}

void BallController(Ball &ball)
{
    if (metadata)
    {
        cout << "Ball X: " + to_string(ball.GetXPosition()) << endl;
        cout << "Ball Y: " + to_string(ball.GetYPosition()) << endl;
        cout << "Player 1 X: " + to_string(playerOneXPosition) << endl;
        cout << "Player 1 Y: " + to_string(playerOneYPosition) << endl;
        cout << "Player 2 X: " + to_string(playerTwoXPosition) << endl;
        cout << "Player 2 Y: " + to_string(playerTwoYPosition) << endl;
        cout << "PaddleSize: " + to_string(paddleHeight / 2) << endl;

        if (ball.IsGoingLeft())
        {
            cout << "Ball going left" << endl;
        }
        else
        {
            cout << "Ball going right" << endl;
        }
    }

    // Y POSITION
    ball.CalculateYPosition();

    // // X POSITION
    Status = ball.IsGameOver(playerOneXPosition, playerOneYPosition, playerTwoXPosition, playerTwoYPosition, paddleWidth, paddleHeight, metadata);
}

Ball StartGame()
{
    Ball ball = Ball(screenWidth, screenHeight);

    playerOneYPosition = screenHeight / 2;
    playerOneXPosition = limitLeft + (ball.GetSize() + paddleWidth);
    playerOneBottomLimit = limitBottom - paddleHeight;

    playerTwoYPosition = screenHeight / 2;
    playerTwoXPosition = limitRight - (ball.GetSize() * 2 + paddleWidth);
    playerTwoBottomLimit = limitBottom - paddleHeight;

    Status = GameOverDTO(false, "");
    return ball;
}

int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(screenWidth, screenHeight, "Pong!");
    SetTargetFPS(60);

    Ball ball = StartGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // You need to clear background, otherwise it keeps "drawing" the circle each iteration without removing the last
        ClearBackground(BLACK);

        DrawRectangle(playerOneXPosition, playerOneYPosition, paddleWidth, paddleHeight, RED);
        DrawRectangle(playerTwoXPosition, playerTwoYPosition, paddleWidth, paddleHeight, BLUE);
        DrawCircle(ball.GetXPosition(), ball.GetYPosition(), ball.GetSize(), WHITE);

        if (IsKeyPressed(KEY_F2))
        {
            ToggleMetadata();
        }

        if (Status.Endgame)
        {
            string winnerText = "Winner: " + Status.Winner;
            char arrBuffer[sizeof(winnerText)];
            DrawText(strcpy(arrBuffer, winnerText.c_str()), screenWidth / 2 - 150, screenHeight / 2, 25, WHITE);
            DrawText("Press ENTER to play again", screenWidth / 2 - 145, screenHeight / 2 + 50, 16, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                ball = StartGame();
            }

            EndDrawing();
            continue;
        }

        PlayerOneController();
        PlayerTwoController();
        BallController(ball);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}