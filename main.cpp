#include <iostream>
#include <cstring>
#include <raylib.h>
#include <string.h>

using namespace std;

const int screenWidth = 1208;
const int screenHeight = 720;

int ballXPosition = screenWidth / 2;
int ballYPosition = screenHeight / 2;
int ballSize = 10;
int ballYSpeed = 5;
int ballXSpeed = 5;

int limitLeft = 0;
int limitRight = screenWidth;
int limitTop = 0;
int limitBottom = screenHeight;

int paddleHeight = screenHeight / 5;
int paddleWidth = 10;
int paddleSpeed = 5;

int playerOneYPosition = screenHeight / 2;
int playerOneXPosition = limitLeft + (ballSize + paddleWidth);
int playerOneBottomLimit = limitBottom - paddleHeight;

int playerTwoYPosition = screenHeight / 2;
int playerTwoXPosition = limitRight - (ballSize * 2 + paddleWidth);
int playerTwoBottomLimit = limitBottom - paddleHeight;

bool ballGoesTop = false;
bool ballGoesLeft = false;

bool metadata = false;

bool endGame = false;
string winner = "";

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

void BallController()
{
    // Y POSITION
    ballYPosition = ballGoesTop ? ballYPosition - ballYSpeed : ballYPosition + ballYSpeed;

    if (ballYPosition + ballYSpeed > limitBottom || ballGoesTop)
    {
        ballGoesTop = true;
    }

    if (ballYPosition - ballYSpeed < limitTop || !ballGoesTop)
    {
        ballGoesTop = false;
    }

    // X POSITION
    ballXPosition = ballGoesLeft ? ballXPosition - ballXSpeed : ballXPosition + ballXSpeed;

    if (metadata)
    {
        cout << "Ball X: " + to_string(ballXPosition) << endl;
        cout << "Ball Y: " + to_string(ballYPosition) << endl;
        cout << "Player 1 X: " + to_string(playerOneXPosition) << endl;
        cout << "Player 1 Y: " + to_string(playerOneYPosition) << endl;
        cout << "Player 2 X: " + to_string(playerTwoXPosition) << endl;
        cout << "Player 2 Y: " + to_string(playerTwoYPosition) << endl;
        cout << "PaddleSize: " + to_string(paddleHeight / 2) << endl;

        if (ballGoesLeft)
        {
            cout << "Ball going left" << endl;
        }
        else
        {
            cout << "Ball going right" << endl;
        }
    }

    // Check if crashes with paddle P1
    if (ballXPosition - ballXSpeed <= playerOneXPosition + paddleWidth && ballGoesLeft)
    {
        if (ballYPosition > playerOneYPosition - paddleHeight / 2 && ballYPosition < playerOneYPosition + paddleHeight)
        {
            if (metadata)
            {
                cout << "Player one touches ball" << endl;
            }

            ballGoesLeft = false;
            return;
        }

        endGame = true;
        winner = "Player Two";
    }
    else if (ballXPosition + ballXSpeed >= playerTwoXPosition - paddleWidth && !ballGoesLeft)
    {
        if (ballYPosition > playerTwoYPosition - paddleHeight / 2 && ballYPosition < playerTwoYPosition + paddleHeight)
        {
            if (metadata)
            {
                cout << "Player two touches ball" << endl;
            }

            ballGoesLeft = true;
            return;
        }

        endGame = true;
        winner = "Player One";
    }
}

void StartGame()
{
    ballXPosition = screenWidth / 2;
    ballYPosition = screenHeight / 2;

    playerOneYPosition = screenHeight / 2;
    playerOneXPosition = limitLeft + (ballSize + paddleWidth);
    playerOneBottomLimit = limitBottom - paddleHeight;

    playerTwoYPosition = screenHeight / 2;
    playerTwoXPosition = limitRight - (ballSize * 2 + paddleWidth);
    playerTwoBottomLimit = limitBottom - paddleHeight;

    endGame = false;
    winner = "";

    int randomTop = rand() % 100;
    ballGoesTop = randomTop < 50;

    int randomBottom = rand() % 100;
    ballGoesLeft = randomBottom < 50;

    ballYSpeed = rand() % 5 + 5;
    ballXSpeed = rand() % 5 + 5;
}

int main()
{
    cout << "Starting the game..." << endl;
    InitWindow(screenWidth, screenHeight, "Pong!");
    SetTargetFPS(60);

    StartGame();

    while (!WindowShouldClose())
    {
        BeginDrawing();

        // You need to clear background, otherwise it keeps "drawing" the circle each iteration without removing the last
        ClearBackground(BLACK);

        DrawRectangle(playerOneXPosition, playerOneYPosition, paddleWidth, paddleHeight, RED);
        DrawRectangle(playerTwoXPosition, playerTwoYPosition, paddleWidth, paddleHeight, BLUE);
        DrawCircle(ballXPosition, ballYPosition, ballSize, WHITE);

        if (IsKeyPressed(KEY_F2))
        {
            ToggleMetadata();
        }

        if (endGame)
        {
            string winnerText = "Winner: " + winner;
            char arrBuffer[sizeof(winnerText)];
            DrawText(strcpy(arrBuffer, winnerText.c_str()), screenWidth / 2 - 150, screenHeight / 2, 25, WHITE);
            DrawText("Press ENTER to play again", screenWidth / 2 - 145, screenHeight / 2 + 50, 16, WHITE);

            if (IsKeyPressed(KEY_ENTER))
            {
                StartGame();
            }

            EndDrawing();
            continue;
        }

        PlayerOneController();
        PlayerTwoController();
        BallController();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}