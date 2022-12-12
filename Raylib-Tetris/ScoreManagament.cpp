#include "ScoreManagament.h"

Score::Score(int score):
	score(0)
{
}

void Score::SetScore(int increase)
{
	score += increase;
}
