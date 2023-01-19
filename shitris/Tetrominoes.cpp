#include "Tetrominoes.h"
#include "Settings.h"
#include "Game.h"
#include "InputManager.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <vector>

Tetromino::Tetromino(Board& board)
	:
	shape(shape),
	dimension(0),
	zeroToOne(zeroToOne),
	oneToZero(oneToZero),
	oneToTwo(oneToTwo),
	twoToOne(twoToOne),
	twoToThree(twoToThree),
	threeToTwo(threeToTwo),
	threeToZero(threeToZero),
	zeroToThree(zeroToThree),
	color(color),
	alternateColor(RAYWHITE),
	alternateColor2(RAYWHITE),
	fallen(true),
	board(board),
	boardPos(board.GetWidth() / 2 - dimension / 2, 0),
	currentRotation(Rotation::UP),
	isBottom(false),
	currentPieceId(-1),
	overloads(0),
	isAnythingHeld(false),
	alias(""),
	isBottomButTop(false)
{
	std::cout << "bpos " << boardPos.GetX() << "  " << boardPos.GetY() << "\n";
}

void Tetromino::RotateClockwise()
{
	std::vector<bool> canDoX(overloads + 1, true);

	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			std::cout << "\n rotation" << (int)currentRotation + 1 << "\n";
			switch ((int)currentRotation + 1)
			{
			case 4:
				cell = shape[y * dimension + x];

				// selecting rotation
				if (cell)
				{
					if (!(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << "\ndoing x = " << i + 1 << "\n";
						std::cout << "\nNEW X = " << boardPos.GetX() + threeToZero[i].GetX() << " AND NEW Y = " << boardPos.GetY() + threeToZero[i].GetY() << "\n";
						std::cout << " return " << i;
						if (!(boardPos.GetX() + x + 1 + threeToZero[i].GetX() > 0)
							|| !(boardPos.GetX() + x + threeToZero[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + threeToZero[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + threeToZero[i].GetX() , boardPos.GetY() + y + threeToZero[i].GetY() })))
						{
							std::cout << "\nI hate programming: " << i + 1 << "\n";
							canDoX[i + 1] = false;
						}
					}
				}
				break;

			case 1:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				// selecting rotation
				if (cell)
				{
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (!(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (!(boardPos.GetX() + x + 1 + zeroToOne[i].GetX() > 0)
							|| !(boardPos.GetX() + x + zeroToOne[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + zeroToOne[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + zeroToOne[i].GetX(), boardPos.GetY() + y + zeroToOne[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;

			case 2:
				std::cout << "\nnewp" << boardPos.GetX() << " " << boardPos.GetY() << "\n";
				std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";

				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				// selecting rotation
				if (cell)
				{
					std::cout << "\nnewp" << boardPos.GetX() << " " << boardPos.GetY() << "\n";
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (!(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						std::cout << "I'm false at " << x << " " << y << "\n";
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (!(boardPos.GetX() + x + 1 + oneToTwo[i].GetX() > 0)
							|| !(boardPos.GetX() + x + oneToTwo[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + oneToTwo[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + oneToTwo[i].GetX(), boardPos.GetY() + y + oneToTwo[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;
			case 3:
				cell = shape[(dimension - 1) + dimension * x - y];
				// selecting rotation
				if (cell)
				{
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (!(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (!(boardPos.GetX() + x + 1 + twoToThree[i].GetX() > 0)
							|| !(boardPos.GetX() + x + twoToThree[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + twoToThree[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + twoToThree[i].GetX(), boardPos.GetY() + y + twoToThree[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;
			}
		}
	}

	for (int i = 0; i < overloads + 1; i++)
	{
		std::cout << "\n\t" << canDoX[i];
	}

	switch (((int)currentRotation) + 1)
	{
	case 4:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 1) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			std::cout << "\nze" << threeToZero[i].GetX() << "\t";
			std::cout << boardPos.GetX() << " bo\n";
			std::cout << boardPos.GetX() + threeToZero[i].GetX() << " boze\n";
			if (canDoX[i + 1])
			{
				currentRotation = Rotation((int(currentRotation) + 1) % 4);
				boardPos.SetX(boardPos.GetX() + threeToZero[i].GetX());
				boardPos.SetY(boardPos.GetY() + threeToZero[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 1:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 1) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << zeroToOne[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + zeroToOne[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 1) % 4);
				boardPos.SetX(boardPos.GetX() + zeroToOne[i].GetX());
				boardPos.SetY(boardPos.GetY() + zeroToOne[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 2:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 1) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << oneToTwo[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + oneToTwo[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 1) % 4);
				boardPos.SetX(boardPos.GetX() + oneToTwo[i].GetX());
				boardPos.SetY(boardPos.GetY() + oneToTwo[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 3:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 1) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << twoToThree[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + twoToThree[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 1) % 4);
				boardPos.SetX(boardPos.GetX() + twoToThree[i].GetX());
				boardPos.SetY(boardPos.GetY() + twoToThree[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	}
	return;
}


void Tetromino::RotateCounterClockwise()
{
	std::vector<bool> canDoX(overloads + 1, true);

	for (int y = 0; y < dimension; y++)
	{
		for (int x = 0; x < dimension; x++)
		{
			bool cell = false;

			std::cout << "\n rotation" << (int)currentRotation + 3 << "\n";
			switch ((int)currentRotation + 3)
			{
			case 4:
				cell = shape[y * dimension + x];

				// selecting rotation
				if (cell)
				{
					if (   !(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << "\ndoing x = " << i + 1 << "\n";
						std::cout << "\nNEW X = " << boardPos.GetX() + oneToZero[i].GetX() << " AND NEW Y = " << boardPos.GetY() + oneToZero[i].GetY() << "\n";
						std::cout << " return " << i;
						if (   !(boardPos.GetX() + x + 1 + oneToZero[i].GetX() > 0) 
							|| !(boardPos.GetX() + x + oneToZero[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + oneToZero[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + oneToZero[i].GetX() , boardPos.GetY() + y + oneToZero[i].GetY() })))
						{
							std::cout << "\nI hate programming: " << i + 1 << "\n";
							canDoX[i + 1] = false;
						}
					}
				}
				break;

			case 5:
				cell = shape[dimension * (dimension - 1) - dimension * x + y];
				// selecting rotation
				if (cell)
				{
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (   !(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (   !(boardPos.GetX() + x + 1 + twoToOne[i].GetX() > 0) 
							|| !(boardPos.GetX() + x + twoToOne[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + twoToOne[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + twoToOne[i].GetX(), boardPos.GetY() + y + twoToOne[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;

			case 6:
				std::cout << "\nnewp" << boardPos.GetX() << " " << boardPos.GetY() << "\n";
				std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";

				cell = shape[(dimension * dimension - 1) - dimension * y - x];
				// selecting rotation
				if (cell)
				{
					std::cout << "\nnewp" << boardPos.GetX() << " " << boardPos.GetY() << "\n";
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (   !(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						std::cout << "I'm false at " << x << " " << y << "\n";
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (   !(boardPos.GetX() + x + 1 + threeToTwo[i].GetX() > 0) 
							|| !(boardPos.GetX() + x + threeToTwo[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + threeToTwo[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + threeToTwo[i].GetX(), boardPos.GetY() + y + threeToTwo[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;
			case 3:
				cell = shape[(dimension - 1) + dimension * x - y];
				// selecting rotation
				if (cell)
				{
					std::cout << "\n" << boardPos.GetX() + x + 1 << " r \n";
					if (   !(boardPos.GetX() + x + 1 > 0)
						|| !(boardPos.GetX() + x < board.GetWidth())
						|| !(boardPos.GetY() + y < board.GetHeight())
						|| (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y })))
					{
						canDoX[0] = false;
					}
					for (int i = 0; i < overloads; i++)
					{
						std::cout << " return " << i;
						if (   !(boardPos.GetX() + x + 1 + zeroToThree[i].GetX() > 0) 
							|| !(boardPos.GetX() + x + zeroToThree[i].GetX() < board.GetWidth())
							|| !(boardPos.GetY() + y + zeroToThree[i].GetY() < board.GetHeight())
							|| (board.CellExists({ boardPos.GetX() + x + zeroToThree[i].GetX(), boardPos.GetY() + y + zeroToThree[i].GetY() })))
						{
							canDoX[i + 1] = false;
						}
					}
				}
				break;
			}
		}
	}

	for (int i = 0; i < overloads + 1; i++)
	{
		std::cout << "\n\t" << canDoX[i];
	}

	switch (((int)currentRotation) + 3)
	{
	case 4:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 3) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			std::cout << "\nze" << oneToZero[i].GetX() << "\t";
			std::cout << boardPos.GetX() << " bo\n";
			std::cout << boardPos.GetX() + oneToZero[i].GetX() << " boze\n";
			if (canDoX[i + 1])
			{
				currentRotation = Rotation((int(currentRotation) + 3) % 4);
				boardPos.SetX(boardPos.GetX() + oneToZero[i].GetX());
				boardPos.SetY(boardPos.GetY() + oneToZero[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 5:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 3) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << twoToOne[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + twoToOne[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 3) % 4);
				boardPos.SetX(boardPos.GetX() + twoToOne[i].GetX());
				boardPos.SetY(boardPos.GetY() + twoToOne[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 6:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 3) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << threeToTwo[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + threeToTwo[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 3) % 4);
				boardPos.SetX(boardPos.GetX() + threeToTwo[i].GetX());
				boardPos.SetY(boardPos.GetY() + threeToTwo[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	case 3:
		// processing rotation
		if (canDoX[0])
		{
			currentRotation = Rotation((int(currentRotation) + 3) % 4);
			return;
		}
		for (int i = 0; i < overloads; i++)
		{
			if (canDoX[i + 1])
			{
				std::cout << "\n\t\t" << zeroToThree[i].GetX() << "\t";
				std::cout << boardPos.GetX() << "\n";
				std::cout << boardPos.GetX() + zeroToThree[i].GetX() << "\n";
				currentRotation = Rotation((int(currentRotation) + 3) % 4);
				boardPos.SetX(boardPos.GetX() + zeroToThree[i].GetX());
				boardPos.SetY(boardPos.GetY() + zeroToThree[i].GetY());
				std::cout << boardPos.GetX() << "\n";
				return;
			}
		}
		return;
	}
	return;
}

void Tetromino::RotateFull()
{
	currentRotation = Rotation((int(currentRotation) + 2) % 4);
}

void Tetromino::Fall()
{
	boardPos.SetY(boardPos.GetY() + 1);	
}

void Tetromino::PlaceTetromino(bool &shouldEnd)
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
				if (boardPos.GetY() + y < 0)
				{
					shouldEnd = true;
				}
				if (!shouldEnd)
				{
					board.SetCell({ boardPos.GetX() + x,  boardPos.GetY() + y }, color, alternateColor, alternateColor2);
				}
			}
		}
	}
	fallen = true;
	if (!shouldEnd)
	{

	}
	else
	{
		// insert play_end_sound
	}
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
				cell = shape[(dimension - 1) + dimension * x - y];
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
	isBottom = false;
	return isBottom;
}

bool Tetromino::IsBottomButTop()
{
	bool found = false;
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
				if (board.CellExists({ boardPos.GetX() + x, boardPos.GetY() + y }))
				{
					isBottomButTop = false;
					return isBottomButTop;
				}
				if (boardPos.GetY() + y - 1 < 0)
				{
					found = true;
					isBottomButTop = true;
				}
			}
		}
	}
	if (!found)
	{
		return false;
	}
	return isBottomButTop;
}

void Tetromino::Draw(int style) const
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
				board.DrawCell(boardPos + Vec2<int>{x, y}, color, alternateColor, alternateColor2, style);
			}
		}
		
	}
}

void Tetromino::HardDrop()
{
	while (!IsBottom())
	{
		Fall();
		board.IncreaseScore((int)((2 + board.GetLevel()) * 1.5));
	}
}

void Tetromino::AlignPos(Tetromino tetromino)
{
	dimension = tetromino.GetDimension();
	shape = tetromino.GetShape();
	boardPos = tetromino.GetPos();
	color = tetromino.GetColor();
	alternateColor = tetromino.GetAlternateColor();
	alternateColor2 = tetromino.GetAlternateColor2();
	currentRotation = (Rotation)tetromino.GetRotation();
	while (!IsBottom())
	{
		Fall();
	}
}

void Tetromino::SetColor(Color c)
{
	color = c;
}

void Tetromino::SetAlternateColor(Color c)
{
	alternateColor = c;
}

void Tetromino::SetAlternateColor2(Color c)
{
	alternateColor2 = c;
}

void Tetromino::SetShape(std::vector<bool> shp)
{
	shape = shp;
}

void Tetromino::SetDimension(int dim)
{
	dimension = dim;
}

void Tetromino::SetOverloads(int overl)
{
	overloads = overl;
}

void Tetromino::SetZeroToOne(std::vector<Vec2<int>> zeroToOn)
{
	zeroToOne = zeroToOn;
}

void Tetromino::SetOneToZero(std::vector<Vec2<int>> oneToZer)
{
	oneToZero = oneToZer;
}

void Tetromino::SetTwoToOne(std::vector<Vec2<int>> twoToOn)
{
	twoToOne = twoToOn;
}

void Tetromino::SetOneToTwo(std::vector<Vec2<int>> oneToTw)
{
	oneToTwo = oneToTw;
}

void Tetromino::SetTwoToThree(std::vector<Vec2<int>> twoToThre)
{
	twoToThree = twoToThre;
}

void Tetromino::SetThreeToTwo(std::vector<Vec2<int>> threeToTw)
{
	threeToTwo = threeToTw;
}

void Tetromino::SetThreeToZero(std::vector<Vec2<int>> threeToZer)
{
	threeToZero = threeToZer;
}

void Tetromino::SetZeroToThree(std::vector<Vec2<int>> zerToThre)
{
	zeroToThree = zerToThre;
}

void Tetromino::SetCurrentPiece(int id)
{
	currentPieceId = id;
}

void Tetromino::SetIsAnythingSetToHeld(bool val)
{
	isAnythingHeld = val;
}

void Tetromino::SetRotation(Rotation rotation)
{
	currentRotation = rotation;
}

void Tetromino::SetAlias(std::string newAlias)
{
	alias = newAlias;
}

void Tetromino::SetFallen(bool newData)
{
	fallen = newData;
}

bool Tetromino::GetFallen() const
{
	return fallen;
}

void Tetromino::SetPos(Vec2<int> pos)
{
	boardPos = pos;
}

Color Tetromino::GetColor() const
{
	return color;
}

Color Tetromino::GetAlternateColor() const
{
	return alternateColor;
}

Color Tetromino::GetAlternateColor2() const
{
	return alternateColor2;
}

int Tetromino::GetDimension() const
{
	return dimension;
}

std::vector<bool> Tetromino::GetShape() const
{
	return shape;
}

std::vector<Vec2<int>> Tetromino::GetZeroToOne() const
{
	return zeroToOne;
}

std::vector<Vec2<int>> Tetromino::GetOneToZero() const
{
	return oneToZero;
}

std::vector<Vec2<int>> Tetromino::GetTwoToOne() const
{
	return twoToOne;
}

std::vector<Vec2<int>> Tetromino::GetOneToTwo() const
{
	return oneToTwo;
}

std::vector<Vec2<int>> Tetromino::GetTwoToThree() const
{
	return twoToThree;
}

std::vector<Vec2<int>> Tetromino::GetThreeToTwo() const
{
	return threeToTwo;
}

std::vector<Vec2<int>> Tetromino::GetThreeToZero() const
{
	return threeToZero;
}

std::vector<Vec2<int>> Tetromino::GetZeroToThree() const
{
	return zeroToThree;
}

int Tetromino::GetOverloads() const
{
	return overloads;
}

int Tetromino::GetCurrentPieceId() const
{
	return currentPieceId;
}

bool Tetromino::getIsAnythingHeld() const
{
	return isAnythingHeld;
}

int Tetromino::GetRotation() const
{
	return (int)currentRotation;
}

Vec2<int> Tetromino::GetPos() const
{
	return boardPos;
}

std::string Tetromino::GetAlias() const
{
	return alias;
}
