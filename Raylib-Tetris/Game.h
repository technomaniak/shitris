#pragma once
#include <string>
#include "Board.h"
#include "Tetrominoes.h"
#include "InputManager.h"

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

	void Draw();
	void Update();
	int SelectRandomPiece() const;
	void DrawFuturePieces();
	void DrawDrawMino();

	int counterFall;
	int counterMove;
	int counterKeepMoving;
	int counterDrop;
	std::vector<int> tetrominoesList;
	int holdPiece;
	bool moved;

};