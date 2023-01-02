#include "Game.h"
#include "raylibCpp.h"
#include "Settings.h"
#include "Board.h"
#include <assert.h>
#include <iostream>
#include "InputManager.h"

Game::Game(int width, int height, int fps, std::string title)
	:
	board(settings::boardPosition, settings::cellSize, settings::padding),
	tetromino(Tetromino(board)),
	futureMino(Tetromino(board)),
	heldMino(Tetromino(board)),
	drawMino(Tetromino(board)),
	counterFall(1),
	counterMove(0),
	counterKeepMoving(0),
	counterDrop(1),
	holdPiece(-1),
	inputManager(InputManager()),
	moved(false),
	lastAction(0),
	gameShouldEnd(false),
	cogwheelImage(LoadImage("Cogwheel.png")),
	cogwheel(LoadTextureFromImage(cogwheelImage)),
	soundManager(SoundManager()),
	mainMenu(MainMenu(soundManager, cogwheel)),
	boardName("Default"),
	newBest(false),
	mouseOverRestartButton(false),
	mouseOverMainMenuButton(false),
	mouseOverOptionsButton(false),
	restartButtonCounter(0),
	mainMenuButtonCounter(0),
	gameOverCounter(0),
	optionsButtonCounter(0),
	gamePaused(false),
	texturesLoaded(false),
	darkOverlayImage(GenImageColor(settings::screenWidth, settings::screenHeight, Color{ 0, 0, 0, 100 })),
	darkOverlay(LoadTextureFromImage(darkOverlayImage)),
	resetTimer(1)
{
	assert(!IsWindowReady()); // if triggered game is already open.
	std::cout << "\nLoading Board " << sizeof(int);
	inputManager.LoadBoard(boardName, board);
	std::cout << "\nBoard Loaded";
	tetrominoesList.resize(inputManager.GetTetrominoPreviewAmount());
	for (int i = 0; i < inputManager.GetTetrominoPreviewAmount(); i++)
	{
		tetrominoesList[i] = SelectRandomPiece();
	}
	std::cout << "\nTetromino Loaded";
	srand((int)time(NULL));

	//SetConfigFlags(FLAG_FULLSCREEN_MODE);
	InitWindow(width, height, title.c_str());
	SetTargetFPS(fps);
}

Game::~Game() noexcept 
{
	assert(GetWindowHandle()); // if triggered game window isn't open 
	soundManager.CloseSound();
	CloseAudioDevice();
	CloseWindow();
}

bool Game::GameShouldClose() const
{
	return WindowShouldClose();
}

void Game::Tick()
{
	BeginDrawing();
	UpdateMusic();
	if (!texturesLoaded)
	{
		texturesLoaded = true;
		LoadTextures();
		mainMenu.UpdateTextures(cogwheel);
	}
	if (mainMenu.GetGameRunning())
	{
		if (mainMenu.GetGameReset())
		{
			ResetGame();
			gamePaused = false;
			mainMenu.SetGameReset(false);
		}
		else
			{
			if (gamePaused)
			{
				if (mainMenu.GetOptionsLoaded())
				{
					mainMenu.Tick();
				}
				else
				{
					Draw(255);
					PauseMenu();
					if (IsKeyPressed(KEY_ESCAPE))
					{
						gamePaused = !gamePaused;
					}
				}
			}
			else
			{
				if (gameShouldEnd)
				{
					GameOver();
				}
				else
				{
					Update();
					Draw();
				}
			}
		}
	}
	else
	{
		if (mainMenu.GetMenuLoaded())
		{
			mainMenu.Tick();
		}
		else
		{
			mainMenu.LoadMenu();
		}
	}
	EndDrawing();
}

void Game::Draw()
{	
	Draw(105);
}

void Game::Draw(int power)
{
	DrawRectangleGradientV(0, 0, (settings::screenWidth / 5) * 3, settings::screenHeight, Color{ 33,1,0,255 }, Color{ 14,42,1,static_cast<unsigned char>(power) });
	DrawRectangleGradientV((settings::screenWidth / 5) * 3, 0, settings::screenWidth, settings::screenHeight, Color{ 33,1,0,255 }, Color{ 14,42,1, 255 });
	board.Draw();
	tetromino.Draw();
	DrawDrawMino();
	board.DrawTimerLine(counterDrop);
	if (inputManager.GetTetrominoPreviewAmount() != 0)
	{
		DrawFuturePieces();
	}
	if (resetTimer != 1)
	{
		board.DrawRestartLine(resetTimer);
	}
	DrawFPS(0, 0);
}

void Game::Update()
{

	if (tetromino.GetFallen())
	{
		board.ClearLines(tetromino.GetCurrentPieceId(), lastAction, tetromino.GetAlias(), tetromino.GetPos());
		tetromino.SetCurrentPiece(tetrominoesList[0]);
		inputManager.LoadTetromino(tetrominoesList[0], tetromino);
		tetrominoesList.erase(tetrominoesList.begin());
		tetrominoesList.push_back(SelectRandomPiece());
		std::cout << "\nrandom piece selected ";
		tetromino.SetPos({ board.GetWidth() / 2 - tetromino.GetDimension() / 2, 0 });
		while (!tetromino.IsBottomButTop())
		{
			tetromino.SetPos({ tetromino.GetPos().GetX(), tetromino.GetPos().GetY() - 1 });
		}
		tetromino.SetFallen(false);
		tetromino.SetIsAnythingSetToHeld(false);
		tetromino.SetRotation(Tetromino::Rotation::UP);}

	if (IsKeyPressed(KEY_X))
	{
		tetromino.RotateClockwise();
		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 1;
	}
	if (IsKeyPressed(KEY_Z))
	{
		tetromino.RotateCounterClockwise();
		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 1;
	}
	if (IsKeyPressed(KEY_W))
	{
		tetromino.RotateFull();
		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 1;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		counterMove++;
		if (counterMove > 10)
		{
			counterKeepMoving++;
			if (counterKeepMoving > 1)
			{
				tetromino.MoveLeft();
				counterKeepMoving = 0;

				if (tetromino.IsBottom())
				{
					counterDrop = 40;
					counterFall = 1;
				}
			}
		}
		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 2;
	}
	if (IsKeyReleased(KEY_LEFT))
	{
		counterMove = 0, counterKeepMoving = 0;
	}
	if (IsKeyPressed(KEY_LEFT))
	{
		tetromino.MoveLeft();

		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 2;
	}

	if (IsKeyDown(KEY_RIGHT))
	{
		counterMove++;

		if (counterMove > 10)
		{
			counterKeepMoving++;
			if (counterKeepMoving > 1)
			{
				tetromino.MoveRight();
				counterKeepMoving = 0;

				if (tetromino.IsBottom())
				{
					counterDrop = 40;
					counterFall = 1;
				}
			}
		}
		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 2;
	}
	if (IsKeyReleased(KEY_RIGHT))
	{
		counterMove = 0, counterKeepMoving = 0;
	}
	if (IsKeyPressed(KEY_RIGHT))
	{
		tetromino.MoveRight();

		if (tetromino.IsBottom())
		{
			counterDrop = 40;
			counterFall = 1;
		}
		lastAction = 2;
	}

	if (IsKeyDown(KEY_DOWN))
	{
		if (!tetromino.IsBottom())
		{
			counterFall += 15 + board.GetSpeed();
		}
		counterFall += 5 + board.GetSpeed();
	}

	if (IsKeyPressed(KEY_C))
	{
		if (!tetromino.getIsAnythingHeld())
		{
			if (inputManager.GetHeld() != -1)
			{
				int current = tetromino.GetCurrentPieceId();
				inputManager.LoadTetromino(inputManager.GetHeld(), tetromino);
				inputManager.SetHeld(current);
				tetromino.SetPos({ board.GetWidth() / 2 - tetromino.GetDimension() / 2, 0 });
				tetromino.SetRotation(Tetromino::Rotation::UP);
				while (!tetromino.IsBottomButTop())
				{
					tetromino.SetPos({ tetromino.GetPos().GetX(), tetromino.GetPos().GetY() - 1 });
				}
			}
			else
			{
				inputManager.SetHeld(tetromino.GetCurrentPieceId()); tetromino.SetCurrentPiece(tetrominoesList[0]);
				inputManager.LoadTetromino(tetrominoesList[0], tetromino);
				tetrominoesList.erase(tetrominoesList.begin());
				tetrominoesList.push_back(SelectRandomPiece());
				std::cout << "\nrandom piece selected ";
				tetromino.SetPos({ board.GetWidth() / 2 - tetromino.GetDimension() / 2, 0 });
				tetromino.SetRotation(Tetromino::Rotation::UP);
			}
			tetromino.SetIsAnythingSetToHeld(true);
			counterDrop = 40;
			counterFall = 1;
		}
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		tetromino.HardDrop();
		counterDrop = -1;
	}

	counterFall += board.GetSpeed() + 1;

	if (tetromino.IsBottom())
	{
		counterDrop--;
		if (counterDrop <= 0)
		{
			tetromino.PlaceTetromino(gameShouldEnd);
			soundManager.PlaySoundFromName("placeSound");
			
			counterDrop = 40;
			counterFall = 1;
		}
	}
	else
	{
		counterDrop = 40;
		if (counterFall >= 61)
		{
			tetromino.Fall();
			board.IncreaseScore((int)((1 + board.GetLevel()) * 1.5));
			counterDrop = 40;
			counterFall = 1;
			lastAction = 0;
		}
	}

	if (IsKeyPressed(KEY_ESCAPE)) 
	{
		gamePaused = !gamePaused;
	}

	if (IsKeyDown(KEY_R))
	{
		resetTimer++;
		if (resetTimer > 61)
		{
			ResetGame();
			resetTimer = 1;
		}
	}
	if (IsKeyReleased(KEY_R))
	{
		resetTimer = 1;
	}
}

void Game::UpdateMusic()
{
	if (!soundManager.CheckMusicPlaying())
	{
		soundManager.PlayRandomMusic();
	}
	else
	{
		soundManager.UpdateCurrentMusic();
	}
}

void Game::LoadTextures()
{
	darkOverlay = LoadTextureFromImage(darkOverlayImage);
	cogwheel = LoadTextureFromImage(cogwheelImage);
	UnloadImage(cogwheelImage);
	UnloadImage(darkOverlayImage);
}

int Game::SelectRandomPiece() const
{
	return rand() % inputManager.GetTetrominoAmount();
}

void Game::DrawFuturePieces()
{
	for (int z = 0; z < inputManager.GetTetrominoPreviewAmount(); z++)
	{
		inputManager.LoadTetromino(tetrominoesList[z], futureMino);
		std::vector<bool> shape(futureMino.GetDimension() * futureMino.GetDimension());
		Vec2<int> pos = { settings::boardWidthHeight.GetX() + 3, (z * (inputManager.GetMaxDimension())) };
		for (int y = 0; y < futureMino.GetDimension(); y++)
		{
			for (int x = 0; x < futureMino.GetDimension(); x++)
			{
				bool cell = false;

				shape = futureMino.GetShape();
				cell = shape[y * futureMino.GetDimension() + x];

				if (cell)
				{
					if (futureMino.GetDimension() < inputManager.GetMaxDimension())
					{
						board.DrawFutureCell(pos + Vec2<int>{x - ((futureMino.GetDimension() - inputManager.GetMaxDimension()) / 2),
							y - ((futureMino.GetDimension() - inputManager.GetMaxDimension()) / 2)}, futureMino.GetColor());
					}
					else
					{
						board.DrawFutureCell(pos + Vec2<int>{x, y}, futureMino.GetColor());
					}
				}
			}
		}

	}

	if (inputManager.GetHeld() != -1)
	{
		inputManager.LoadTetromino(inputManager.GetHeld(), heldMino);
		for (int y = 0; y < heldMino.GetDimension(); y++)
		{
			std::vector<bool> shape(heldMino.GetDimension() * heldMino.GetDimension());
			Vec2<int> pos = { -4 , 0};
			for (int x = 0; x < heldMino.GetDimension(); x++)
			{
				bool cell = false;

				shape = heldMino.GetShape();
				cell = shape[y * heldMino.GetDimension() + x];

				if (cell)
				{
					if (tetromino.getIsAnythingHeld())
					{
						board.DrawHeldCell(pos + Vec2<int>{x, y}, LIGHTGRAY);
					}
					else 
					{
						board.DrawHeldCell(pos + Vec2<int>{x, y}, heldMino.GetColor());
					}
				}
			}
		}
	}

	board.DrawFutureBoard({ ((settings::boardWidthHeight.GetX() + 8) * board.GetCellSize()), board.GetScreenPos().GetY() - 26 },
		{ (5 * board.GetCellSize()) + board.GetCellSize() - 6, (inputManager.GetTetrominoPreviewAmount() * board.GetCellSize() * inputManager.GetMaxDimension()) - 5 + (board.GetCellSize()) * 2 });
	board.DrawFutureBorder({ ((settings::boardWidthHeight.GetX() + 8) * board.GetCellSize()), board.GetScreenPos().GetY() - 26 },
		{ (5 * board.GetCellSize()) + board.GetCellSize() - 6, (inputManager.GetTetrominoPreviewAmount() * board.GetCellSize() * inputManager.GetMaxDimension()) - 5 + (board.GetCellSize() * 2) });
	board.DrawFutureBoardGrid({ ((settings::boardWidthHeight.GetX() + 8) * board.GetCellSize()), board.GetScreenPos().GetY() - 20 }, inputManager.GetTetrominoPreviewAmount(), inputManager.GetMaxDimension());
}

void Game::DrawDrawMino()
{
	drawMino.AlignPos(tetromino);
	drawMino.Draw(1);
}

void Game::GameOver()
{
	if (mainMenu.GetOptionsLoaded())
	{
		mainMenu.Tick();
	}
	else
	{
		if (gameOverCounter < 50)
		{
			raycpp::DrawRectangle({ 0, 0 }, { settings::screenWidth, settings::screenHeight }, Color{ 0, 0, 0, 60 });
			gameOverCounter++;
		}
		else
		{
			raycpp::DrawRectangle({ 0, 0 }, { settings::screenWidth, settings::screenHeight }, Color{ 0, 0, 0, 255 });
			board.SaveScore(boardName, newBest);

			if (newBest)
			{
				raycpp::DrawText("GAME\nOVER", settings::gameOverTextPosition, settings::gameOverAllRegularTextsSize, Color{ 255, 0, 0, 255 });
				raycpp::DrawText("NEW BEST", settings::newBestTextPosition, settings::gameOverAllRegularTextsSize - 20, Color{ 255, 69, 0, 255 });
			}
			else
			{
				raycpp::DrawText("GAME\nOVER", settings::gameOverTextPosition, settings::gameOverAllRegularTextsSize, Color{ 255, 25, 13, 255 });
			}

			RestartButton(newBest);
			MainMenuButton(newBest);
			OptionsButton(newBest);
		}
		board.Draw();
		tetromino.Draw();
	}
}

void Game::PauseMenu()
{
	DrawTextureV(darkOverlay, { 0, 0 }, RAYWHITE);
	RestartButton(false);
	MainMenuButton(false);
	OptionsButton(false);
}

void Game::MainMenuButton(bool isNewBest)
{
	Vec2<int> extraOffset;
	if (isNewBest)
	{
		extraOffset = { 0, 150 };
	}
	else
	{
		extraOffset = { 0, 0 };
	}
	if (raycpp::GetMousePos() - Vec2<int>{ 0, -20 } - extraOffset > settings::mainMenuButtonPos
		&& raycpp::GetMousePos() < settings::mainMenuButtonPos + settings::mainMenuButtonSize - Vec2<int>{ 0, 20 } + extraOffset)
	{
		if (mouseOverMainMenuButton != true)
		{
			soundManager.PlaySoundFromName("menuSound");
			mouseOverMainMenuButton = true;
		}
	}
	else
	{
		if (settings::mainMenuButtonTextSize <= settings::maxMainMenuButtonTextSize)
		{
			mainMenuButtonCounter++;
			if (mainMenuButtonCounter > 0)
			{
				settings::mainMenuButtonTextSize += 1;
				mainMenuButtonCounter = 0;
			}
		}
		mouseOverMainMenuButton = false;
	}
	if (mouseOverMainMenuButton)
	{
		if (settings::mainMenuButtonTextSize >= settings::minMainMenuButtonTextSize)
		{
			mainMenuButtonCounter++;
			if (mainMenuButtonCounter > 0)
			{
				settings::mainMenuButtonTextSize -= 1;
				restartButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ResetGame();
			board.EraseBoard();
			mainMenu.SetGameRunning(false);
			mainMenu.SetMenuLoaded(false);
			soundManager.PlaySoundFromName("menuSound");
		}
	}
	DrawRestartButton(isNewBest);
	DrawMainMenuButton(isNewBest);
}

void Game::DrawMainMenuButton(bool isNewBest)
{
	if (isNewBest)
	{
		Vec2<int> extraOffset{ 0, 150 };
		raycpp::DrawRectangleLinesEx(settings::mainMenuButtonPos + extraOffset, settings::mainMenuButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::mainMenuButtonSize.GetX() - ((int)MeasureText("MAIN MENU", settings::mainMenuButtonTextSize))) / 2,
			((settings::mainMenuButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "MAIN MENU", (float)settings::mainMenuButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("MAIN MENU", settings::mainMenuButtonPos + textOffset + extraOffset, settings::mainMenuButtonTextSize, DARKBLUE);
	}
	else
	{
		raycpp::DrawRectangleLinesEx(settings::mainMenuButtonPos, settings::mainMenuButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::mainMenuButtonSize.GetX() - ((int)MeasureText("MAIN MENU", settings::mainMenuButtonTextSize))) / 2,
			((settings::mainMenuButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "MAIN MENU", (float)settings::mainMenuButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("MAIN MENU", settings::mainMenuButtonPos + textOffset, settings::mainMenuButtonTextSize, DARKBLUE);
	}
}

void Game::RestartButton(bool isNewBest)
{

	Vec2<int> extraOffset;
	if (isNewBest)
	{
		extraOffset = { 0, 150 };
	}
	else
	{
		extraOffset = { 0, 0 };
	}

	if (raycpp::GetMousePos() - Vec2<int>{ 0, - 20 } - extraOffset > settings::restartButtonPos
		&& raycpp::GetMousePos() < settings::restartButtonPos + settings::restartButtonSize - Vec2<int>{ 0, 20 } + extraOffset)
	{
		if (mouseOverRestartButton != true)
		{
			soundManager.PlaySoundFromName("menuSound");
			mouseOverRestartButton = true;
		}
	}
	else
	{
		if (settings::restartButtonTextSize <= settings::maxRestartButtonTextSize)
		{
			restartButtonCounter++;
			if (restartButtonCounter > 0)
			{
				settings::restartButtonTextSize += 1;
				restartButtonCounter = 0;
			}
		}
		mouseOverRestartButton = false;
	}
	if (mouseOverRestartButton)
	{
		if (settings::restartButtonTextSize >= settings::minRestartButtonTextSize)
		{
			restartButtonCounter++;
			if (restartButtonCounter > 0)
			{
				settings::restartButtonTextSize -= 1;
				restartButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			ResetGame();
			soundManager.PlaySoundFromName("menuSound");
		}
	}
	DrawRestartButton(isNewBest);
}

void Game::DrawRestartButton(bool isNewBest)
{
	if (isNewBest)
	{
		Vec2<int> extraOffset{ 0, 150 };
		raycpp::DrawRectangleLinesEx(settings::restartButtonPos + extraOffset, settings::restartButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::restartButtonSize.GetX() - ((int)MeasureText("PLAY AGAIN", settings::restartButtonTextSize))) / 2,
			((settings::restartButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "PLAY AGAIN", (float)settings::restartButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("PLAY AGAIN", settings::restartButtonPos + textOffset + extraOffset, settings::restartButtonTextSize, DARKBLUE);
	}
	else
	{
		raycpp::DrawRectangleLinesEx(settings::restartButtonPos, settings::restartButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::restartButtonSize.GetX() - ((int)MeasureText("PLAY AGAIN", settings::restartButtonTextSize))) / 2,
			((settings::restartButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "PLAY AGAIN", (float)settings::restartButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("PLAY AGAIN", settings::restartButtonPos + textOffset, settings::restartButtonTextSize, DARKBLUE);
	}
}

void Game::OptionsButton(bool isNewBest)
{
	Vec2<int> extraOffset;
	if (isNewBest)
	{
		extraOffset = { 0, 150 };
	}
	else
	{
		extraOffset = { 0, 0 };
	}

	if (raycpp::GetMousePos() - Vec2<int>{ 0, -20 } - extraOffset > settings::optionsButtonPos
		&& raycpp::GetMousePos() < settings::optionsButtonPos + settings::optionsButtonSize - Vec2<int>{ 0, 20 } + extraOffset)
	{
		if (mouseOverOptionsButton != true)
		{
			soundManager.PlaySoundFromName("menuSound");
			mouseOverOptionsButton = true;
		}
	}
	else
	{
		mouseOverOptionsButton = false;
	}
	if (mouseOverOptionsButton)
	{
		if (settings::optionsButtonTextSize >= settings::minOptionsButtonTextSize)
		{
			optionsButtonCounter++;
			if (optionsButtonCounter > 0)
			{
				settings::optionsButtonTextSize -= 1;
				optionsButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			mainMenu.LoadOptions();
			soundManager.PlaySoundFromName("menuSound");
		}
	}
	else
	{
		if (settings::optionsButtonTextSize <= settings::maxOptionsButtonTextSize)
		{
			optionsButtonCounter++;
			if (optionsButtonCounter > 0)
			{
				settings::optionsButtonTextSize += 1;
				optionsButtonCounter = 0;
			}
		}
	}
	DrawOptionsButton(isNewBest);
}

void Game::DrawOptionsButton(bool isNewBest)
{
	if (isNewBest)
	{
		Vec2<int> extraOffset{ 0, 150 };
		raycpp::DrawRectangleLinesEx(settings::optionsButtonPos + extraOffset, settings::optionsButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::optionsButtonSize.GetX() - ((int)MeasureText("OPTIONS", settings::optionsButtonTextSize))) / 2,
			((settings::optionsButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "OPTIONS", (float)settings::optionsButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("OPTIONS", settings::optionsButtonPos + textOffset + extraOffset, settings::optionsButtonTextSize, DARKBLUE);
	}
	else
	{
		raycpp::DrawRectangleLinesEx(settings::optionsButtonPos, settings::optionsButtonSize, 5, BLUE);
		Vec2<int> textOffset = { (settings::optionsButtonSize.GetX() - ((int)MeasureText("OPTIONS", settings::optionsButtonTextSize))) / 2,
			((settings::optionsButtonSize.GetY() - ((int)MeasureTextEx(GetFontDefault(), "OPTIONS", (float)settings::optionsButtonTextSize, 10).y)) / 2) };
		raycpp::DrawText("OPTIONS", settings::optionsButtonPos + textOffset, settings::optionsButtonTextSize, DARKBLUE);
	}
}

void Game::ResetGame()
{
	gameShouldEnd = false;
	inputManager.LoadBoard(boardName, board);
	tetromino.SetCurrentPiece(tetrominoesList[0]);
	inputManager.LoadTetromino(tetrominoesList[0], tetromino);
	tetrominoesList.erase(tetrominoesList.begin());
	tetrominoesList.push_back(SelectRandomPiece());
	std::cout << "\nrandom piece selected ";
	gameOverCounter = 0;
	tetromino.SetPos({ board.GetWidth() / 2 - tetromino.GetDimension() / 2, 0 });
	while (!tetromino.IsBottomButTop())
	{
		tetromino.SetPos({ tetromino.GetPos().GetX(), tetromino.GetPos().GetY() - 1 });
	}
	tetromino.SetFallen(false);
	tetromino.SetIsAnythingSetToHeld(false);
	tetromino.SetRotation(Tetromino::Rotation::UP);
	holdPiece = -1;
	inputManager.SetHeld(-1);
	board.ResetScore();
	board.EraseBoard();
	newBest = false;
	inputManager.LoadHighScore(boardName);
}
