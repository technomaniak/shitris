#pragma once
#include <string>
#include "Board.h"
#include "Tetrominoes.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "MainMenu.h"

class Game
{
public:
	Game(int width, int height, int fps, std::string title);
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	~Game() noexcept;

	bool GameShouldClose() const;
	void Tick();

private:
	Board board;
	Tetromino tetromino;
	Tetromino futureMino;
	Tetromino drawMino;
	Tetromino heldMino;

	Texture2D cogwheel;
	Image cogwheelImage;
	Texture2D quitGameTexture;
	Image quitGameImage;

	Texture2D darkOverlay;
	Image darkOverlayImage;

	void Draw();
	void Draw(int power);
	void Update();
	void UpdateMusic();
	void LoadTextures();
	int SelectRandomPiece() const;
	void DrawFuturePieces();
	void DrawDrawMino();
	void GameOver();
	void PauseMenu();
	void MainMenuButton(bool isNewBest);
	void DrawMainMenuButton(bool isNewBest);
	void RestartButton(bool isNewBest);
	void DrawRestartButton(bool isNewBest);
	void OptionsButton(bool isNewBest);
	void DrawOptionsButton(bool isNewBest);
	void ResetGame();

	int style;
	int counterFall;
	int counterMove;
	int counterKeepMoving;
	int counterDrop;
	int lastAction;
	std::vector<int> tetrominoesList;
	int holdPiece;
	bool moved;
	bool gameShouldEnd;
	bool newBest;
	bool gamePaused;
	bool mouseOverRestartButton;
	bool mouseOverMainMenuButton;
	bool mouseOverOptionsButton;
	bool texturesLoaded;
	int resetTimer;
	int restartButtonCounter;
	int mainMenuButtonCounter;
	int gameOverCounter;
	int optionsButtonCounter;
	bool hardReset;
	std::string boardName;

	std::vector<std::vector<int>> keyBindsList{};
	InputManager inputManager;
	SoundManager soundManager;
	MainMenu mainMenu;
};

