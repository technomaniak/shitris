#include "ScoreManagement.h"
#include "raylibCpp.h"
#include "Settings.h"
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
	DrawText(TextFormat("Score: \n%08i", score), settings::scoreCounterPosition.GetX(), settings::scoreCounterPosition.GetY(), settings::scoreCounterSize, VIOLET);
}

int ScoreManagement::GetScore() const
{
	return score;
}
