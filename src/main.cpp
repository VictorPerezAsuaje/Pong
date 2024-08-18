#include <iostream>
#include <cstring>
#include <raylib.h>
#include <string.h>

#include "ball.h"
#include "player.h"

using namespace std;

const int screenWidth = 1208;
const int screenHeight = 720;

int limitLeft = 0;
int limitRight = screenWidth;
int limitTop = 0;
int limitBottom = screenHeight;

GameOverDTO Status = GameOverDTO(false, "");
Player playerOne = Player(screenHeight, screenWidth, KEY_W, KEY_S, limitTop, limitBottom, true);
Player playerTwo = Player(screenHeight, screenWidth, KEY_UP, KEY_DOWN, limitTop, limitBottom, false);

void BallController(Ball &ball)
{
    // Y POSITION
    ball.CalculateYPosition();

    // // X POSITION
    Status = ball.IsGameOver(playerOne.GetXPosition(), playerOne.GetYPosition(), playerTwo.GetXPosition(), playerTwo.GetYPosition(), playerOne.GetPaddleWidth(), playerOne.GetPaddleHeight());
}

Ball StartGame()
{
    Ball ball = Ball(screenWidth, screenHeight);
    playerOne = Player(screenHeight, screenWidth, KEY_W, KEY_S, limitTop, limitBottom, true);
    playerTwo = Player(screenHeight, screenWidth, KEY_UP, KEY_DOWN, limitTop, limitBottom, false);

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

        DrawRectangle(playerOne.GetXPosition(), playerOne.GetYPosition(), playerOne.GetPaddleWidth(), playerOne.GetPaddleHeight(), RED);
        DrawRectangle(playerTwo.GetXPosition(), playerTwo.GetYPosition(), playerTwo.GetPaddleWidth(), playerTwo.GetPaddleHeight(), BLUE);
        DrawCircle(ball.GetXPosition(), ball.GetYPosition(), ball.GetSize(), WHITE);
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, Color{255, 255, 255, 75});

        if (Status.Endgame)
        {
            string winnerText = "Winner: " + Status.Winner;
            char arrBuffer[sizeof(winnerText)];
            DrawText(strcpy(arrBuffer, winnerText.c_str()), screenWidth / 2 - 130, screenHeight / 2, 25, WHITE);
            DrawText("Press ENTER to play again", screenWidth / 2 - 125, screenHeight / 2 + 50, 16, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                ball = StartGame();
            }

            EndDrawing();
            continue;
        }

        playerOne.UpdatePosition();
        playerTwo.UpdatePosition();
        BallController(ball);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}