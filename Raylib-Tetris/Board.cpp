#include "Board.h"
#include <assert.h>
#include <iostream>
#include "Game.h"
#include "Settings.h"
#include "ScoreManagement.h"

Board::Cell::Cell()
	:
	bExists(false),
	c(WHITE)
{

}

void Board::Cell::SetColor(Color c_in)
{
	c = c_in;
	bExists = true;
}

void Board::Cell::Remove()
{
	bExists = false;
}

bool Board::Cell::Exists() const
{
	return bExists;
}

Color Board::Cell::GetColor() const
{
	return c;
}

Board::Board(Vec2<int> screenPos, int cellSize_in, int padding)
	:
	screenPos(screenPos),
	cellSize(cellSize_in),
	width(settings::boardWidthHeight.GetX()),
	height(settings::boardWidthHeight.GetY()),
	padding(padding),
	speed(0),
	level(0),
	foundExtraLines(false)
{
	std::cout << "doing board";
	assert(width > 0 && height > 0); // checking if the width and height are larger than 0;
	assert(cellSize > 0); // checking if cells aren't too small
	cells.resize(width * height);
}

void Board::SetCell(Vec2<int> pos, Color c)
{
	//assert(pos.GetX() >= 0 && pos.GetY() >= 0);
	assert(pos.GetX() < width && pos.GetY() < height);

	cells[pos.GetY() * width + pos.GetX()].SetColor(c);
}

void Board::MoveCell(Vec2<int> posOld, Vec2<int> posNew)
{
	if (CellExists(posOld))
	{
		foundExtraLines = true;
		SetCell(posNew, cells[posOld.GetX() + (posOld.GetY() * GetWidth())].GetColor());
		cells[posOld.GetX() + (posOld.GetY() * GetWidth())].Remove();
	}
}

void Board::DrawCell(Vec2<int> pos) const
{
	Color color = cells[pos.GetY() * width + pos.GetX()].GetColor();
	DrawCell(pos, color);
}

void Board::DrawCell(Vec2<int> pos, Color color) const
{
	Vec2<int> topLeft = screenPos + (pos * cellSize);

	raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize } - padding, color);
}

void Board::DrawCell(Vec2<int> pos, Color color, int style) const
{
	switch (style)
	{
	case 1:
		Vec2<int> topLeft = screenPos + (pos * cellSize);
		raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize - ((cellSize / 10) * 9), cellSize } - padding, color);

		raycpp::DrawRectangle({ topLeft.GetX() + ((cellSize / 10) * 9), topLeft.GetY() },
			Vec2<int>{ cellSize - ((cellSize / 10) * 9), cellSize } - padding, color);

		raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize - ((cellSize / 10) * 9) } - padding, color);

		raycpp::DrawRectangle({ topLeft.GetX(), topLeft.GetY() + ((cellSize / 10) * 9) },
			Vec2<int>{ cellSize, cellSize - ((cellSize / 10) * 9)} - padding, color);
		break;
	}
}

void Board::DrawFutureCell(Vec2<int> pos, Color color) const
{
	Vec2<int> topLeft = { screenPos.GetX() - 30 + (pos.GetX() * cellSize), screenPos.GetY() + 20 + (pos.GetY() * cellSize) };

	raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize } - padding, color);
}

void Board::DrawHeldCell(Vec2<int> pos, Color color) const
{
	Vec2<int> topLeft = { screenPos.GetX() - 50 + (pos.GetX() * cellSize) , screenPos.GetY() + (pos.GetY() * cellSize) };

	raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize } - padding, color);
}

void Board::DrawBorder() const
{
	raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2) - 4, Vec2{ width * cellSize, height * cellSize } + cellSize + 2, cellSize / 2, Color{ 0, 0, 0, 106 });
}

void Board::DrawFutureBorder(Vec2<int> pos, Vec2<int> size) const
{
	raycpp::DrawRectangleLinesEx(pos, size, cellSize / 2, Color{ 0, 0, 0, 106 });
}

void Board::DrawHeldBorder(Vec2<int> pos, Vec2<int> size) const
{
}


void Board::DrawFutureBoardGrid(Vec2<int> pos, int amount) const
{
	for (int y = 1; y < 6; y++)
	{
		DrawLine(pos.GetX() - 2 + (y * cellSize),
			pos.GetY() - 6 + (cellSize / 2),
			pos.GetX() - 2 + (y * cellSize),
			pos.GetY() - 11 + (amount * 4 * cellSize) - (cellSize / 2),
			Color{ 102, 191, 255, 55 });
	}
	for (int x = 1; x < amount * 4; x++)
	{
		DrawLine(pos.GetX() + (cellSize / 2),
			pos.GetY() - 7 + (x * cellSize),
			pos.GetX() - 5 + (5 * cellSize) + (cellSize / 2),
			pos.GetY() - 7 + (x * cellSize),
			Color{ 102, 191, 255, 55 });
	}
}

void Board::DrawBoardGrid() const
{
	for (int y = 1; y < GetWidth(); y++)
	{
		DrawLine(settings::boardPosition.GetX() - 2 + (y * cellSize),
				 settings::boardPosition.GetY() + 2,
				 settings::boardPosition.GetX() - 2 + (y * cellSize),
				 settings::boardPosition.GetY() - 5 + (settings::boardWidthHeight.GetY() * cellSize),
			     Color{ 102, 191, 255, 55 });
	}
	for (int x = 1; x < GetHeight(); x++)
	{
		DrawLine(settings::boardPosition.GetX(),
				 settings::boardPosition.GetY() - 2 + (x * cellSize),
				 settings::boardPosition.GetX() - 5 + (settings::boardWidthHeight.GetX() * cellSize),
				 settings::boardPosition.GetY() - 2 + (x * cellSize),
				 Color{ 102, 191, 255, 55 });
	}
}

void Board::DrawBoard() const
{
	raycpp::DrawRectangle(screenPos - (cellSize / 2) - 4, Vec2{ width * cellSize, height * cellSize } + cellSize + 2, Color{ 0, 0, 0, 56 });
}

void Board::DrawFutureBoard(Vec2<int> pos, Vec2<int> size) const
{
	raycpp::DrawRectangle(pos, size, Color{ 0, 0, 0, 56 });
}

void Board::DrawTimerLine(int timer) const
{
	raycpp::DrawRectangle({ screenPos.GetX() - 4 - cellSize / 2, screenPos.GetY() + 25 + (cellSize * height) }, { (cellSize * width) + 2 + cellSize, 10 }, Color{ 255, 255, 255, 55 });
	raycpp::DrawRectangle({ screenPos.GetX() - 4 - cellSize / 2, screenPos.GetY() + 25 + (cellSize * height) },
		{ (((cellSize * width) + 2 + cellSize) * timer) / 40, 10 }, RAYWHITE);
}

void Board::Draw() const
{
	DrawBoard();
	DrawBorder();
	DrawBoardGrid();
	DrawLevel();
	for (int iY = 0; iY < height; iY++)
	{
		for (int iX = 0; iX < width; iX++)
		{
			if (CellExists({ iX, iY }))
			{
				DrawCell({ iX, iY });
			}
		}
	}
	score.DrawScore();
}

void Board::DrawLevel() const
{
	DrawText(TextFormat("Level: \n%02i", level), settings::levelCounterPosition.GetX(), settings::levelCounterPosition.GetY(), settings::levelCounterSize, PURPLE);
}

std::vector<int> Board::CheckForLines()
{
	std::vector<int> output = {};
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (!CellExists({ x, y }))
			{
				break;
			}
			if (x == width - 1)
			{
				if (CellExists({ x, y }))
				{
					output.push_back(y);
				}
			}
		}
	}
	return output;
}

void Board::ClearLines(int lastPiece, int lastAction, std::string alias, Vec2<int> pos)
{
	std::vector<int> toRemove = CheckForLines();
	for (int y = 0; y < toRemove.size(); y++)
	{
		for (int x = 0; x < width; x++) // removing cells loop
		{
			cells[ x + (toRemove[y] * GetWidth()) ].Remove();

			for (int yDos = toRemove[y]; yDos >= 0; yDos--)
			{
				MoveCell({ x, yDos }, { x, yDos + 1 });
			}
		}
	}

	for (int x = 0; x <= width; x++) // removing cells loop
	{
		for (int y = height; y >= 0; y--)
		{
			if (CellExists({ x, y }))
			{
				foundExtraLines = true;
			}
		}
	}

	if (toRemove.size() > 1)
	{
		score.IncreaseScore(toRemove.size(), lastAction, lastPiece, alias, GetLevel(), pos, foundExtraLines);
		foundExtraLines = false;
	}

	//gay porn
	//switch (toRemove.size())
	//{
	//case 1:
	//	score.IncreaseScore(40 * (level + 1));
	//	break;
	//case 2:
	//	score.IncreaseScore(100 * (level + 1));
	//	break;
	//case 3:
	//	score.IncreaseScore(300 * (level + 1));
	//	break;
	//case 4:
	//	score.IncreaseScore(1200 * (level + 1));
	//	break;
	//}
	if (score.GetScore() > (level + 1) * (level + 2) * 1500)
	{
		speed += 1;
		level += 1;
	}
}

bool Board::CellExists(Vec2<int> pos) const
{
	if (pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height)
	{
		return cells[pos.GetY() * width + pos.GetX()].Exists();
	}
	return false;
	assert(pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height); // check if cell pos is valid
}

int Board::GetWidth() const
{
	return width;
}

int Board::GetHeight() const
{
	return height;
}

int Board::GetSpeed() const
{
	return speed;
}

int Board::GetLevel() const
{
	return level;
}

Vec2<int> Board::GetScreenPos() const
{
	return screenPos;
}

int Board::GetCellSize() const
{
	return cellSize;
}

void Board::IncreaseScore(int increase)
{
	score.IncreaseScore(increase);
}

void Board::SetSize(Vec2<int> widthHei)
{
	width = widthHei.GetX();
	height = widthHei.GetY();
}
