#include "Tetrominoes.h"
#include "Settings.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>

Tetromino::Tetromino(
	const bool* shape,
	int dimension,
	int overloads,
	std::vector<Vec2<int>> zeroToOne,
	std::vector<Vec2<int>> oneToZero,
	std::vector<Vec2<int>> oneToTwo,
	std::vector<Vec2<int>> twoToOne,
	std::vector<Vec2<int>> twoToThree,
	std::vector<Vec2<int>> threeToTwo,
	std::vector<Vec2<int>> threeToZero,
	std::vector<Vec2<int>> zeroToThree,
	Color color,
	Board& board)
	:
	shape(shape),
	dimension(dimension),
	overloads(overloads),
	zeroToOne(zeroToOne),
	oneToZero(oneToZero),
	oneToTwo(oneToTwo),
	twoToOne(twoToOne),
	twoToThree(twoToThree),
	threeToTwo(threeToTwo),
	threeToZero(threeToZero),
	zeroToThree(zeroToThree),
	color(color),
	boardPos(board.GetWidth() / 2 - dimension / 2, 0),
	board(board),
	currentRotation(Rotation::UP),
	isBottom(false)
{
	assert(threeToZero.size() > 0);
}

const std::vector<Vec2<int>> Straight::zeroToOne = { {-2, 0}, {1, 0}, {-2 , -1}, {1, 2} };
const std::vector<Vec2<int>> Straight::oneToZero = { {2, 0}, {-1, 0}, {2 , 1}, {-1, -2} };
const std::vector<Vec2<int>> Straight::oneToTwo = { {-1, 0}, {2, 0}, {-1 , 2}, {2, -1} };
const std::vector<Vec2<int>> Straight::twoToOne = { {1, 0}, {-2, 0}, {1 , -2}, {-2, 1} };
const std::vector<Vec2<int>> Straight::twoToThree = { {2, 0}, {-1, 0}, {2 , 1}, {-1, -2} };
const std::vector<Vec2<int>> Straight::threeToTwo = { {-2, 0}, {1, 0}, {-2 , -1}, {1, 2} };
const std::vector<Vec2<int>> Straight::threeToZero = { {1, 0}, {-2, 0}, {1 , -2}, {-2, 1} };
const std::vector<Vec2<int>> Straight::zeroToThree = { {-1, 0}, {2, 0}, {-1 , 2}, {2, -1} };

const std::vector<Vec2<int>> Square::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> Square::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> Square::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> Square::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> Square::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> Square::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> Square::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> Square::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

const std::vector<Vec2<int>> Tee::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> Tee::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> Tee::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> Tee::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> Tee::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> Tee::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> Tee::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> Tee::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

const std::vector<Vec2<int>> Jay::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> Jay::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> Jay::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> Jay::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> Jay::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> Jay::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> Jay::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> Jay::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

const std::vector<Vec2<int>> El::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> El::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> El::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> El::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> El::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> El::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> El::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> El::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

const std::vector<Vec2<int>> SkewS::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> SkewS::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> SkewS::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> SkewS::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> SkewS::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> SkewS::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> SkewS::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> SkewS::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

const std::vector<Vec2<int>> SkewZ::zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
const std::vector<Vec2<int>> SkewZ::oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
const std::vector<Vec2<int>> SkewZ::oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
const std::vector<Vec2<int>> SkewZ::twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
const std::vector<Vec2<int>> SkewZ::twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
const std::vector<Vec2<int>> SkewZ::threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
const std::vector<Vec2<int>> SkewZ::threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
const std::vector<Vec2<int>> SkewZ::zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };

void Tetromino::RotateClockwise()
{
	bool canDoOne = true;
	bool canDoTwo = true;
	bool canDoThree = true;
	bool canDoFour = true;
	bool canDoFive = true;
	
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch ((int)currentRotation + 1)
			{
			case 4:
				cell = shape[y * dimension + x];
				break;
			case 1:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case 2:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case 3:
				cell = shape[dimension - 1 * dimension + dimension * x + y];
				break;
			}

			if (cell)
			{
				std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
				if (!(boardPos.GetX() + x + 1 > 0) || !(boardPos.GetX() + x < board.GetWidth()))
				{
					std::cout << " return ";
					return;
				}
			}
		}
	}
	std::cout << "\t rotation" << (int)currentRotation << "\t";
	currentRotation = Rotation((int(currentRotation) + 1) % 4);
}

void Tetromino::RotateCounterClockwise()
{
	std::vector<bool> canDoX(overloads, true);

	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch ((int)currentRotation + 3)
			{
			case 4:
				cell = shape[y * dimension + x];

				if (cell)
				{
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";

					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (!(boardPos.GetX() + x + 1 + threeToZero[i].GetX() > 0) || !(boardPos.GetX() + x < board.GetWidth()))
						{
							canDoX[i] = false;
						}
					}
				}

				break;
			case 5:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case 6:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case 3:
				cell = shape[dimension - 1 * dimension + dimension * x + y];
				break;
			}
		}
	}
	std::cout << "\t rotation" << (int)currentRotation << "\t";
	currentRotation = Rotation((int(currentRotation) + 3) % 4);
}

void Tetromino::RotateFull()
{
	currentRotation = Rotation((int(currentRotation) + 2) % 4);
}

void Tetromino::Fall()
{
	bool found = false;
	bool end = false;
	for (int y = dimension-1; y >= 0; y--)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[(dimension - 1) + dimension * x - y];
				break;
			default:
				break;
			}

			if (cell)
			{
				if (boardPos.GetY() + y + 2 > settings::boardWidthHeight.GetY())
				{
					PlaceTetromino();
				}
				else if (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y + 1 }))
				{
					PlaceTetromino();
				}

				if (end)
				{
					board.SetCell({ boardPos.GetX() + x,  boardPos.GetY() + y }, color);
				}
			}
		}
	}
	if (!end)
	{
		boardPos.SetY(boardPos.GetY() + 1);
	}
}

void Tetromino::PlaceTetromino()
{

	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[(dimension - 1) + dimension * x - y];
				break;
			default:
				break;
			}

			if (cell)
			{
				board.SetCell({ boardPos.GetX() + x,  boardPos.GetY() + y }, color);
			}
		}
	}
	boardPos.SetX(board.GetWidth() / 2 - dimension / 2);
	boardPos.SetY(0);
	currentRotation = Rotation::UP;
	return;
}

void Tetromino::MoveRight()
{
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[dimension - 1 * dimension + dimension * x + y];
				break;
			default:
				break;
			}

			if (cell)
			{
				std::cout << boardPos.GetX() + x + 2;
				if (boardPos.GetX() + x + 2 > settings::boardWidthHeight.GetX() || board.CellExists({ boardPos.GetX() + x + 1, boardPos.GetY() + y }))
				{
					return;
				}
			}
		}
	}
	std::cout << "\n";
	boardPos.SetX(boardPos.GetX() + 1);
}

void Tetromino::MoveLeft()
{
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[(dimension - 1) + dimension * x - y];
				break;
			default:
				break;
			}

			if (cell)
			{
				std::cout << boardPos.GetX() << " ";
				if (boardPos.GetX() + x - 1 < 0 || board.CellExists({ boardPos.GetX() + x - 1, boardPos.GetY() + y }))
				{
					return;
				}
			}
		}
	}
	std::cout << "\n";
	boardPos.SetX(boardPos.GetX() - 1);
}

bool Tetromino::IsBottom()
{
	for (int y = dimension - 1; y >= 0; y--)
	{
		for (int x = dimension - 1; x >= 0; x--)
		{
			bool cell = false;
			
			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[(dimension - 1) + dimension * x - y];
				break;
			default:
				break;
			}

			if (cell)
			{
				if (boardPos.GetY() + y + 2 > settings::boardWidthHeight.GetY())
				{
					isBottom = true;
					return isBottom;
				}
				else if (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y + 1 }))
				{
					isBottom = true;
					return isBottom;
				}
			}
		}
	}
	std::cout << isBottom;
	isBottom = false;
	return isBottom;
}

void Tetromino::Draw() const
{
	//assert(threeToZero.size() > 0);

	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++) 
		{
			bool cell = false;
			
			switch (currentRotation)
			{
			case Tetromino::Rotation::UP:
				cell = shape[y * dimension + x];
				break;
			case Tetromino::Rotation::RIGHT:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				break;
			case Tetromino::Rotation::DOWN:
				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				break;
			case Tetromino::Rotation::LEFT:
				cell = shape[(dimension - 1) + dimension * x - y];
				break;
			default:
				break;
			}

			if (cell)
			{
				board.DrawCell(boardPos + Vec2<int>{x, y}, color);
			}
		}
	}
}

void Tetromino::DebugNum()
{
	DrawText(std::to_string(boardPos.GetX()).c_str(), 150, 0, 13, RED);
	DrawText(std::to_string(boardPos.GetY()).c_str(), 160, 0, 13, RED);
}

Tetromino Tetromino::SelectRandomPiece(Board& board)
{
	srand(time(NULL));
	int val = rand()%7;
	std::cout << "\ngenerated new piece" << val;
	return Straight(board);
	/*switch (val)
	{
	case 0:
		return SkewZ(board);
	case 1:
		return SkewS(board);
	case 2:
		return Straight(board);
	case 3:
		return Square(board);
	case 4:
		return Jay(board);
	case 5:
		return El(board);
	case 6:
		return Tee(board);
	}*/
}