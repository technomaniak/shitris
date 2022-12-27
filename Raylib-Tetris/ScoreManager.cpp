#include "ScoreManager.h"
#include "raylibCpp.h"
#include "Settings.h"
#include <string>
#include <iostream>
#include <fstream>

ScoreManager::ScoreManager():
	score(0),
	lastClear({0, 0, 0}),  //lines action piece
	lines(0),
	highScore(0)
{
}

void ScoreManager::IncreaseScore(int lines, int lastAction, int lastPiece, std::string alias, int level, Vec2<int> pos, bool foundExtraLines)
{
	switch (lines)
	{
	case 1:
		if (lastAction == 1)
		{
			if (lastClear[1] == lastAction && lastClear[2] == lastPiece)
			{
				score += ((level + 1) * (int)(200 * 1.5));
				DrawTextPro(GetFontDefault(), TextFormat("B2B c spin", alias), 
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
				score += ((level + 1) * (int)(1200 * 1.5));
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
				score += ((level + 1) * (int)(1600 * 1.5));
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
				score += ((level + 1) * (int)(2000 * 1.5));
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
				score += ((level + 1) * (int)(3000 * 1.5));
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
				score += ((level + 1) * (int)(4500 * 1.5));
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

void ScoreManager::IncreaseScore(int increase)
{
	score += increase;
}

void ScoreManager::IncreaseLines(int nLines)
{
	lines += nLines;
}

void ScoreManager::Draw() const
{
	DrawScore();
	DrawLines();
	DrawHighScore();
}

void ScoreManager::DrawScore() const
{
	DrawText(TextFormat("Score: \n%08i", score), settings::scoreCounterPosition.GetX(), settings::scoreCounterPosition.GetY(), settings::scoreCounterSize, VIOLET);
}

void ScoreManager::DrawHighScore() const
{
	DrawText(TextFormat("HI: %08i", highScore), settings::scoreCounterPosition.GetX(), settings::scoreCounterPosition.GetY() + 238, 20, DARKBLUE);
}

void ScoreManager::DrawLines() const
{
	DrawText(TextFormat("Lines Cleared: \n%04i", lines), settings::linesCounterPosition.GetX(), settings::linesCounterPosition.GetY(), settings::linesCounterSize, VIOLET);
}

int ScoreManager::GetScore() const
{
	return score;
}

int ScoreManager::GetLines() const
{
	return lines;
}

void ScoreManager::SaveBestScore(std::string file, bool &newBest)
{
	std::ifstream dataSave(file + ".HS");
	std::string input;
	std::getline(dataSave, input);
	if (dataSave.fail())
	{
		std::ofstream dataSaveOut(file + ".HS");
		dataSaveOut << score << "\n";
		dataSaveOut << lines;
		newBest = true;
	}
	else
	{
		if (input == "")
		{
			std::ofstream dataSaveOut(file + ".HS");
			dataSaveOut << score << "\n";
			dataSaveOut << lines;
			newBest = true;
		}
		else
		{
			if (std::stoi(input) < score)
			{
				std::ofstream dataSaveOut(file + ".HS");
				dataSaveOut << score << "\n";
				dataSaveOut << lines;
				newBest = true;
			}
		}
	}
}

void ScoreManager::SetHighScore(int highScoreNew)
{
	highScore = highScoreNew;
}
