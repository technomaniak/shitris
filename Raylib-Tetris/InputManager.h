#pragma once
#include <iostream>
#include <vector>
#include "Vec2.h"
#include "Tetrominoes.h"

class InputManager
{
public:
	InputManager();

	void LoadBoard(std::string boardName, Board &board);
	void LoadTetromino(int index, Tetromino &tetromino);
	int GetTetrominoPreviewAmount() const;
	int GetTetrominoAmount() const;
	int GetHeld() const;
	void SetHeld(int tetrominoe);

	std::vector<Tetromino> tetrominoes;
	int held;
private:
	void LoadTetrominoToFile(std::string fileName, int index);
	int tetrominoePreviewAmount;
	int tetrominoeAmount;
};