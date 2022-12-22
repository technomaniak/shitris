#include "ScoreManagement.h"
#include "raylibCpp.h"
#include "Settings.h"
#include <string>
#include <iostream>

ScoreManagement::ScoreManagement():
	score(0),
	lastClear({0, 0, 0}) //lines action piece
{
}

void ScoreManagement::IncreaseScore(int lines, int lastAction, int lastPiece, std::string alias, int level, Vec2<int> pos, bool foundExtraLines)
{
	switch (lines)
	{
	case 1:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 200 * 1.5);
				DrawTextPro(GetFontDefault(), TextFormat("B2B ", alias, " spin"), 
					{ settings::boardPosition.GetX() + ((float)pos.GetX() * settings::cellSize), (float)pos.GetY() + ((float)pos.GetY() * settings::cellSize) },
					{ (float)pos.GetX(), (float)pos.GetY() }, 255, 22, 3, Color{ 255, 255, 255, 255 });
			}
			else
			{
				score += ((level + 1) * 200);
				std::cout << "Mini " + alias + " spin";
			}
		}
		else
		{
			score += ((level + 1) * 100);
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 800);
		}
		break;

	case 2:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 1200 * 1.5);
				DrawTextPro(GetFontDefault(), TextFormat("B2B %c spin", alias),
						   { settings::boardPosition.GetX() + ((float)pos.GetX() * settings::cellSize),
						   settings::boardPosition.GetY() + ((float)pos.GetY() * settings::cellSize) },
						   { (float)pos.GetX(), (float)pos.GetY() }, 69, 22, 3, Color{ 255, 255, 255, 255 });
			}
			else
			{
				score += ((level + 1) * 1200);
				std::cout << "Double " + alias + " spin";
			}
		}
		else
		{
			score += ((level + 1) * 300);
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 1200);
		}
		break;

	case 3:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 1600 * 1.5);
				std::cout << "B2B " + alias + " spin";
			}
			else
			{
				score += ((level + 1) * 1600);
				std::cout << "Triple " + alias + " spin";
			}
		}
		else
		{
			score += ((level + 1) * 500);
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 1800);
		}
		break;

	case 4:
		if (lastAction == 1)
		{
			std::cout << "Quad " + alias + " spin";
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 2000 * 1.5);
				std::cout << "B2B " + alias + " spin";
			}
			else
			{
				score += ((level + 1) * 2000);
				std::cout << "Quintiple " + alias + " spin";
			}
		}
		else
		{
			score += ((level + 1) * 800);
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 2000);
		}
		break;

	case 5:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 3000 * 1.5);
				std::cout << "B2B " + alias + " spin";
			}
			else
			{
				score += ((level + 1) * 3000);
				std::cout << "Mega " + alias + " spin";
			}
		}
		else
		{
			score += ((level + 1) * 1500);
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 2200);
		}
		break;

	case 6:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * 4500 * 1.5);
				std::cout << "B2B " + alias + " spin";
			}
			else
			{
				score += ((level + 1) * 4500);
			}
		}
		else
		{
			score += ((level + 1) * 2100);
			std::cout << "Mega " + alias + " spin";
		}
		if (foundExtraLines = false)
		{
			std::cout << "ALL CLEAR";
			score += ((level + 1) * 2400);
		}
		break;
	}
	lastClear = { lines, lastAction, lastPiece };
}

void ScoreManagement::IncreaseScore(int increase)
{
	score += increase;
}

void ScoreManagement::DrawScore() const
{
	DrawText(TextFormat("Score: \n%08i", score), settings::scoreCounterPosition.GetX(), settings::scoreCounterPosition.GetY(), settings::scoreCounterSize, VIOLET);
}

int ScoreManagement::GetScore() const
{
	return score;
}
