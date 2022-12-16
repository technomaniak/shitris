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

Board::Board(Vec2<int> screenPos, Vec2<int> widhtHeight, int cellSize_in, int padding)
	:
	screenPos(screenPos),
	width(widhtHeight.GetX()),
	height(widhtHeight.GetY()),
	cellSize(cellSize_in),
	padding(padding),
	speed(0)
{
	assert(width > 0 && height > 0); // checking if the width and height are larger than 0;
	assert(cellSize > 0); // checking if cells aren't too small
	cells.resize(width * height);
}

void Board::SetCell(Vec2<int> pos, Color c)
{
	assert(pos.GetX() >= 0 && pos.GetY() >= 0);
	assert(pos.GetX() < width && pos.GetY() < height);

	cells[pos.GetY() * width + pos.GetX()].SetColor(c);
}

void Board::MoveCell(Vec2<int> posOld, Vec2<int> posNew)
{
	if (CellExists(posOld))
	{
		SetCell(posNew, cells[posOld.GetX() + (posOld.GetY() * 10)].GetColor());
		cells[posOld.GetX() + (posOld.GetY() * 10)].Remove();
	}
}

void Board::DrawCell(Vec2<int> pos) const
{
	Color color = cells[pos.GetY() * width + pos.GetX()].GetColor();
	DrawCell(pos, color);
}

void Board::DrawCell(Vec2<int> pos, Color color) const
{
	assert(pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height); // check if cell pos is valid
	Vec2<int> topLeft = screenPos + (pos * cellSize);

	raycpp::DrawRectangle(topLeft, Vec2<int>{ cellSize, cellSize } - padding, color);
}

void Board::DrawBorder() const
{
	raycpp::DrawRectangleLinesEx(screenPos - (cellSize / 2)-2, Vec2{ width * cellSize, height * cellSize } + cellSize+1, cellSize / 2, WHITE);
}

void Board::DrawBoardGrid() const
{
	//for (int y = 0; y <= GetWidth(); y++)
	//{
	//	DrawLine(settings::boardPosition.GetX() - 1 + (y * settings::cellSize),
	//		settings::boardPosition.GetY(),
	//		settings::boardPosition.GetX() + (y * settings::cellSize),
	//		settings::boardPosition.GetY() + (settings::boardWidthHeight.GetY() * settings::cellSize),
	//		Color{ 102, 191, 255, 255 });
	//}
}

void Board::Draw() const
{
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
	DrawBorder();
	DrawBoardGrid();
	score.DrawScore();
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

void Board::ClearLines()
{
	std::vector<int> toRemove = CheckForLines();
	for (int y = 0; y < toRemove.size(); y++)
	{
		for (int x = 0; x < width; x++) // removing cells loop
		{
			cells[ x + (toRemove[y] * 10) ].Remove();

			for (int yDos = toRemove[y]; yDos > 0; yDos--)
			{
				MoveCell({ x, yDos }, { x, yDos + 1 });
			}
		}
	}
	switch (toRemove.size())
	{
	case 1:
		score.IncreaseScore(40);
		break;
	case 2:
		score.IncreaseScore(100);
		break;
	case 3:
		score.IncreaseScore(300);
		break;
	case 4:
		score.IncreaseScore(1200);
		break;
	}
	if (score.GetScore() > speed * 10)
	{
		speed += 20;
	}
}

bool Board::CellExists(Vec2<int> pos) const
{
	assert(pos.GetX() >= 0 && pos.GetX() < width && pos.GetY() >= 0 && pos.GetY() < height); // check if cell pos is valid
	return cells[pos.GetY() * width + pos.GetX()].Exists();
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
