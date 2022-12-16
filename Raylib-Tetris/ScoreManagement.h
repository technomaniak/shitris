#pragma once
class ScoreManagement
{
public:
	ScoreManagement();
	void IncreaseScore(int increase);
	void DrawScore() const;
	int GetScore() const;

private:
	int score;
};