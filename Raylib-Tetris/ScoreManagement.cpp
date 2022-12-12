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
	DrawText(TextFormat("SCORE: %d", score), 500, 50, 60, VIOLET);
}
