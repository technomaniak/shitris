#pragma once
#include "Vec2.h"
#include <string>
#include <vector>

class ScoreManager
{
public:
	ScoreManager();
	void IncreaseScore(int lines, int lastAction, int lastPiece, std::string alias, int level, Vec2<int> pos, bool foundExtraLines);
	void IncreaseScore(int increase);
	void DrawScore() const;
	int GetScore() const;

private:
	int score;
	std::vector<int> lastClear; //lines action piece
};