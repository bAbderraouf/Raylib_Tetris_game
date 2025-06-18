#include "raylib.h"
#include "Grid.h"
#include <iostream>
#include <vector>
#include "Tetris.h"

int main()
{
	double	lastTime = 0, 
			currentTime = 0, 
			timeInterval = 0.25;
	Color orange = { 0, 102, 0, 255 };

	Tetris tetrisGame(450, 620, 60, 20, 10, 30); //grid 300x600

	while (WindowShouldClose() == false)
	{
		// check inputs 
		tetrisGame.Input();

		//update gameMusic
		UpdateMusicStream(tetrisGame.GetGameMusic());

		// update
		currentTime = GetTime();
		if (currentTime - lastTime > timeInterval)
		{
			lastTime = currentTime;
			tetrisGame.Update();
		}

		// draw
		BeginDrawing();
			ClearBackground(orange);
			tetrisGame.Draw();
		EndDrawing();

	}

	CloseWindow();
}