#include "Tetrominoes.h"
#include "Settings.h"
#include <string>
#include <iostream>

Tetromino::Tetromino(const bool* shape, int dimension, Color color, Board& board)
	:
	shape(shape),
	dimension(dimension),
	color(color),
	boardPos(board.GetWidth() / 2 - dimension / 2, 0),
	board(board),
	currentRotation(Rotation::UP),
	isBottom(false)
{

}

void Tetromino::RotateClockwise()
{
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch ((int)currentRotation + 1)
			{
			case 04:
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
	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			switch ((int)currentRotation + 3)
			{
			case 4:
				cell = shape[y * dimension + x];
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
	switch (val)
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
	}
}