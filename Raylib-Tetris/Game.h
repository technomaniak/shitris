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
	InputManager inputManager;

	void Draw();
	void Update();
	void SelectRandomPiece(Tetromino &tetromino);

	int counter;
	int counterDos;
	int counterTres;
	bool moved;

};