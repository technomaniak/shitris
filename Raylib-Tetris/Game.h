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
	Game(const Game& other)= delete;
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
	InputManager inputManager;
	SoundManager soundManager;
	MainMenu mainMenu;

	void Draw();
	void Update();
	int SelectRandomPiece() const;
	void DrawFuturePieces();
	void DrawDrawMino();
	void GameOver();
	void RestartButton(bool isNewBest);

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
	std::string boardName;

};