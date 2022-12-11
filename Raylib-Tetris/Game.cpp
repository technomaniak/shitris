#include "Game.h"
#include "raylibCpp.h"
#include "Settings.h"
#include <assert.h>

Game::Game(int width, int height, int fps, std::string title)
	:
	board(settings::boardPosition, settings::boardWidthHeight, settings::cellSize, settings::padding),
	tetromino(Tetromino::SelectRandomPiece(board)),
	counter(counter)
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
	DrawFPS(0, 0);
	EndDrawing();
}

int Game::GetScore()
{
	return score;
}

void Game::Draw()
{
	ClearBackground(BLACK);
	board.Draw();
	tetromino.Draw();
}

void Game::Update()
{
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
	if (IsKeyPressed(KEY_LEFT))
	{
		tetromino.MoveLeft();
		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		tetromino.MoveRight();
		if (tetromino.IsBottom())
		{
			counter = 0;
		}
	}
	if (IsKeyDown(KEY_DOWN))
	{
		counter += 20;
	}

	counter++;
	tetromino.DebugNum();

	if (counter >= 60)
	{
		tetromino.Fall();
		counter = 0;
	}
}