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

	std::vector<Tetromino> tetrominoes;
private:
	void LoadTetrominoToFile(std::string fileName, int index);

};