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
	void IncreaseLines(int nLines);
	void Draw() const;
	void DrawScore() const;
	void DrawHighScore() const;
	void DrawLines() const;
	int GetScore() const;
	int GetLines() const;
	void SaveBestScore(std::string file, bool &newBest);

	void SetHighScore(int highScoreNew);

private:
	int score;
	int lines;
	int highScore;
	
	std::vector<int> lastClear; //lines action piece
};