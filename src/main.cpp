#include <iostream>
#include <cstring>
#include <raylib.h>
#include <string.h>

#include "game.h"
#include "ball.h"
#include "player.h"

using namespace std;

// const int screenWidth = 1208;
// const int screenHeight = 720;

// int limitLeft = 0;
// int limitRight = screenWidth;
// int limitTop = 0;
// int limitBottom = screenHeight;

Game game = Game(1208, 720);
Ball ball = game.CreateBall();
Player playerOne = game.CreatePlayerOne();
Player playerTwo = game.CreatePlayerTwo();

void StartGame()
{
    game.ResetGame();
    ball = game.CreateBall();
    playerOne = game.CreatePlayerOne();
    playerTwo = game.CreatePlayerTwo();
}

int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(game.GetScreenWidth(), game.GetScreenHeight(), "Pong!");
    SetTargetFPS(60);

    StartGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // You need to clear background, otherwise it keeps "drawing" the circle each iteration without removing the last
        ClearBackground(BLACK);

        // Scores
        DrawText(to_string(game.GetPlayerOneWins()).c_str(), 50, 50, 16, WHITE);
        DrawText(to_string(game.GetPlayerTwoWins()).c_str(), game.GetScreenWidth() - 50, 50, 16, WHITE);

        playerOne.Draw();
        playerTwo.Draw();
        ball.Draw();

        DrawLine(game.GetScreenWidth() / 2, 0, game.GetScreenWidth() / 2, game.GetScreenHeight(), Color{255, 255, 255, 75});

        game.UpdateGameStatus(ball, playerOne, playerTwo);

        if (game.IsGameOver())
        {
            DrawText(("Winner: " + game.GetWinner()).c_str(), game.GetScreenWidth() / 2 - 130, game.GetScreenHeight() / 2, 25, WHITE);
            DrawText("Press ENTER to play again", game.GetScreenWidth() / 2 - 125, game.GetScreenHeight() / 2 + 50, 16, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                StartGame();
            }

            EndDrawing();
            continue;
        }

        playerOne.UpdatePosition();
        playerTwo.UpdatePosition();
        ball.UpdatePosition();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}