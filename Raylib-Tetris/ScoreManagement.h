#pragma once
class ScoreManagement
{
public:
	ScoreManagement();
	void IncreaseScore(int increase);
	void DrawScore() const;

private:
	int score;
};