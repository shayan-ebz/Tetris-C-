#include <raylib.h>
#include "Game.h"
#include "Colors.h"
#include <iostream>

double lastUpdateTime = 0;

// this function is called 60 times per second to check if it's time to move the blocks
bool IsRequiredTimePassed(double interval)
{
	double currentTime = GetTime(); // in seconds

	// compare currentTime with lastUpdateTime to calculate how much has passed since the last update
	if (currentTime - lastUpdateTime >= interval)
	{
		// interval has passed
		lastUpdateTime = currentTime;
		return true;
	}

	return false;
}

int main()
{
	///////////////////////////////////////////////// Variable section
	// window's background color
	Color BackgroundColor{ 37, 74, 168, 255 };
	Game game{};

	// font is loaded in gpu memory
	Font font = LoadFontEx("fonts/Rajdhani.ttf", 60, 0, 0);


	///////////////////////////////////////////////// Variable section 


	// creating a window for the game
	InitWindow(500, 620, "Tetris C++"); // 300 pixels width, 600 pixels height [10 * 30, 20 * 30]

	// how fast the game should run? 60pfs 
	SetTargetFPS(60);

	// game loop
	// while the window is NOT closed
	while (WindowShouldClose() == false)
	{
		// getting inputs from the player
		game.HandleInput();
		if (IsRequiredTimePassed(0.1))
		{
			// time to move the block down 
			game.MoveBlockDown();
		}


		// create a blank canvas so we can draw on it
		BeginDrawing();
		ClearBackground(BackgroundColor);
		DrawTextEx(font, "Score", { 365, 15 }, 30, 2, WHITE); 
		DrawTextEx(font, "Next", { 370, 175 }, 30, 2, WHITE);

		if (game.bGameOver)
		{
			DrawTextEx(font, "Game Over", { 320, 450 }, 30, 2, WHITE);
		}
		
		DrawRectangleRounded({ 320, 55, 170, 60 }, 0.4, 8, lightblue);

		char scoreText[10];
		sprintf_s(scoreText, "%d", game.m_Score);
		Vector2 textSize = MeasureTextEx(font, scoreText, 30, 2);

		DrawTextEx(font, scoreText, { 320 + (170 - textSize.x)/2, 65}, 30, 2, WHITE);
		DrawRectangleRounded({ 320, 215, 170, 180 }, 0.4, 8, lightblue);
		game.Draw();

		EndDrawing();
	}

	// closing the game window
	CloseWindow();
	return 0;
}