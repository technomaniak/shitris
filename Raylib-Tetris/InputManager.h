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
	int LoadHighScore(std::string boardName);
	int GetTetrominoPreviewAmount() const;
	int GetTetrominoAmount() const;
	int GetHeld() const;
	void SetHeld(int tetrominoe);
	int GetMaxDimension() const;

	std::vector<Tetromino> tetrominoes;
	int held;
private:
	void LoadTetrominoToFile(std::string fileName, int index);
	int tetrominoePreviewAmount;
	int tetrominoeAmount;
	int maxDimension;
};