#include "Game.h"
#include "raylibCpp.h"
#include "Settings.h"
#include <assert.h>
#include <iostream>

Game::Game(int width, int height, int fps, std::string title)
	:
	board(settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding),
	tetromino(Tetromino::SelectRandomPiece(board)),
	counter(0),
	counterDos(0),
	counterTres(0),
	moved(false)
{
	assert(!IsWindowReady()); // if triggered game is already open.
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);
}

Game::~Game() noexcept 
{
	assert(GetWindowHandle()); // if triggered game window isn't open 
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	Update();
	Draw();
	EndDrawing();
}


void Game::Draw()
{
	ClearBackground(BLACK);
	board.Draw();
	tetromino.Draw();
	DrawFPS(0, 0);
}

void Game::Update()
{
	if (IsKeyDown(KEY_LEFT))
	{
		counterDos++;

		if (counterDos > 10)
		{
			counterTres++;
			if (counterTres > 1)
			{
				tetromino.MoveLeft();
				counterTres = 0;

				if (tetromino.IsBottom())
				{
					counter = 0;
				}
			}
		}
	}
	if (IsKeyReleased(KEY_LEFT))
	{
		counterDos = 0, counterTres = 0;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		tetromino.MoveLeft();

		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		counterDos++;

		if (counterDos > 10)
		{
			counterTres++;
			if (counterTres > 1)
			{
				tetromino.MoveRight();
				counterTres = 0;

				if (tetromino.IsBottom())
				{
					counter = 0;
				}
			}
		}
	}
	if (IsKeyReleased(KEY_RIGHT))
	{
		counterDos = 0, counterTres = 0;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		tetromino.MoveRight();

		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}

	if (IsKeyPressed(KEY_X))
	{
		tetromino.RotateClockwise();
		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}
	if (IsKeyPressed(KEY_Z))
	{
		tetromino.RotateCounterClockwise();
		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}
	if (IsKeyPressed(KEY_C))
	{
		tetromino.RotateFull();
		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		if (!tetromino.IsBottom())
		{
			counter += 15;
		}
		counter += 5;
	}

	board.ClearLines();
	counter++;
	tetromino.DebugNum();

	if (counter >= 60)
	{
		tetromino.Fall();
		counter = 0;
	}
}
