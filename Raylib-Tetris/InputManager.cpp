#include "InputManager.h"
#include <fstream>
#include <string>
#include "Settings.h"
#include "Board.h"

InputManager::InputManager():
	tetrominoes(),
	tetrominoePreviewAmount(),
	tetrominoeAmount(),
	held(-1)
{

}

void InputManager::LoadBoard(std::string boardName, Board &board)
{
	std::ifstream inputFile(boardName + ".board");
	std::string input;
	
	// getting board size

	std::getline (inputFile, input, ' ');
	settings::boardWidthHeight.SetX(std::stoi(input));
	std::getline(inputFile, input);
	settings::boardWidthHeight.SetY(std::stoi(input));
	
	board.SetSize(settings::boardWidthHeight);

	// getting board data

	for (int y = 0; y < settings::boardWidthHeight.GetY(); y++)
	{
		std::getline(inputFile, input);

		for (int x = 0; x < settings::boardWidthHeight.GetX(); x++)
		{
			if (input[x] != '0')
			{
				board.SetCell({ x, y }, LIGHTGRAY);
			}
		}
	}

	// getting pieces
	
	std::getline(inputFile, input);
	tetrominoeAmount = std::stoi(input);
	for (int i = 0; i < tetrominoeAmount; i++)
	{
		std::getline(inputFile, input);
		tetrominoes.push_back(Tetromino(board));
		LoadTetrominoToFile(input, i);
	}

	// getting amount of preview

	std::getline(inputFile, input);
	tetrominoePreviewAmount = std::stoi(input);
}

void InputManager::LoadTetromino(int index, Tetromino &tetromino)
{
	tetromino.SetColor(tetrominoes[index].GetColor());
	tetromino.SetDimension(tetrominoes[index].GetDimension());
	tetromino.SetOverloads(tetrominoes[index].GetOverloads());
	tetromino.SetShape(tetrominoes[index].GetShape());
	tetromino.SetOneToTwo(tetrominoes[index].GetOneToTwo());
	tetromino.SetTwoToOne(tetrominoes[index].GetTwoToOne());
	tetromino.SetZeroToOne(tetrominoes[index].GetZeroToOne());
	tetromino.SetOneToZero(tetrominoes[index].GetOneToZero());
	tetromino.SetZeroToThree(tetrominoes[index].GetZeroToThree());
	tetromino.SetThreeToZero(tetrominoes[index].GetThreeToZero());
	tetromino.SetTwoToThree(tetrominoes[index].GetTwoToThree());
	tetromino.SetThreeToTwo(tetrominoes[index].GetThreeToTwo());
	tetromino.SetALias(tetrominoes[index].GetAlias());
}

int InputManager::GetTetrominoPreviewAmount() const
{
	return tetrominoePreviewAmount;
}

int InputManager::GetTetrominoAmount() const
{
	return tetrominoeAmount;
}

int InputManager::GetHeld() const
{
	return held;
}

void InputManager::SetHeld(int tetrominoe)
{
	held = tetrominoe;
}

void InputManager::LoadTetrominoToFile(std::string fileName, int index)
{
	std::ifstream inputFile(fileName);
	std::string input;

	// get dimension

	std::getline(inputFile, input);
	tetrominoes[index].SetDimension(std::stoi(input));
	std::vector<bool> shape(std::stoi(input) * std::stoi(input), false);

	// get shape

	std::getline(inputFile, input);
	for (size_t i = 0; i < input.size(); i++)
	{
		if (input[i] == '#')
		{
			shape[i] = true;
		}
	}

	tetrominoes[index].SetShape(shape);

	// get color

	bool r = false, g = false, b = false, a = false;
	std::vector<int> color;
	for (int i = 0; i < 4; i++)
	{
		std::getline(inputFile, input, ',');
		color.push_back(std::stoi(input));
	}
	tetrominoes[index].SetColor(Color{ (unsigned char)color[0], (unsigned char)color[1], (unsigned char)color[2], (unsigned char)color[3] });

	// get overloads

	std::getline(inputFile, input);
	std::getline(inputFile, input);
	int overloads = std::stoi(input);
	tetrominoes[index].SetOverloads(overloads);

	//get actual overloads lol

	std::vector<Vec2<int>> overloadVector;
	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetZeroToOne(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetOneToZero(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetOneToTwo(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetTwoToOne(overloadVector);


	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetTwoToThree(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetThreeToTwo(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetThreeToZero(overloadVector);

	overloadVector.clear();

	for (int i = 0; i < overloads; i++)
	{
		overloadVector.push_back({ });
		std::getline(inputFile, input, ':');
		overloadVector[i].SetX(std::stoi(input));
		std::getline(inputFile, input, '|');
		overloadVector[i].SetY(std::stoi(input));
	}
	tetrominoes[index].SetZeroToThree(overloadVector);

	overloadVector.clear();

	// get alias

	std::getline(inputFile, input);
	std::getline(inputFile, input);
	tetrominoes[index].SetALias(input);

	// end my life
}
