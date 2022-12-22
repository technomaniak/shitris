#pragma once
#include "Vec2.h"
#include <string>
#include <vector>

class ScoreManagement
{
public:
	ScoreManagement();
	void IncreaseScore(int lines, int lastAction, int lastPiece, std::string alias, int level, Vec2<int> pos);
	void IncreaseScore(int increase);
	void DrawScore() const;
	int GetScore() const;

private:
	long long int score;
	std::vector<int> lastClear; //lines action piece
};