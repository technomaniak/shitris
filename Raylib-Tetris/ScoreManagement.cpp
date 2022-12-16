#include "ScoreManagement.h"
#include "raylibCpp.h"
#include <string>

ScoreManagement::ScoreManagement():
	score(0)
{
}

void ScoreManagement::IncreaseScore(int increase)
{
	score += increase;
}

void ScoreManagement::DrawScore() const
{
	DrawText(TextFormat("Score: %d", score), 500, 50, 60, VIOLET);
}

int ScoreManagement::GetScore() const
{
	return score;
}
