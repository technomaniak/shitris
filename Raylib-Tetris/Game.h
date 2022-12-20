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
	Tetromino heldMino;
	InputManager inputManager;

	void Draw();
	void Update();
	int SelectRandomPiece() const;
	void DrawFuturePieces();

	int counter;
	int counterDos;
	int counterTres;
	std::vector<int> tetrominoesList;
	int holdPiece;
	bool moved;

};