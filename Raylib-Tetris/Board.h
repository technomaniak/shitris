#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Vec2.h"
#include "ScoreManager.h"

class Board
{
private:
	class Cell
	{
	public:
		Cell();
		void SetColor(Color c_in);
		void Remove();
		bool Exists() const;

		Color GetColor() const;
	private:
		bool bExists;
		Color c;

	};

public:
	Board(Vec2<int> screenPos, int cellSize_in, int padding);
	void SetCell(Vec2<int> pos, Color c);
	void MoveCell(Vec2<int> posOld, Vec2<int> posNew);
	void DrawCell(Vec2<int> pos) const;
	void DrawCell(Vec2<int> pos, Color color) const;
	void DrawCell(Vec2<int> pos, Color color, int style) const;
	void DrawFutureCell(Vec2<int> pos, Color color) const;
	void DrawHeldCell(Vec2<int> pos, Color color) const;
	void DrawBorder() const;
	void DrawFutureBorder(Vec2<int> pos, Vec2<int> size) const;
	void DrawHeldBorder(Vec2<int> pos, Vec2<int> size) const;
	void DrawBoardGrid() const;
	void DrawFutureBoardGrid(Vec2<int> pos, int amount, int maxDimension) const;
	void DrawBoard() const;
	void DrawFutureBoard(Vec2<int> pos, Vec2<int> size) const;
	void DrawTimerLine(int timer) const;
	void Draw() const;
	void DrawLevel() const;
	std::vector<int> CheckForLines();
	void ClearLines(int lastPiece, int lastAction, std::string alias, Vec2<int> pos);
	bool CellExists(Vec2<int> pos) const;
	int GetWidth() const;
	int GetHeight() const;
	int GetSpeed() const;
	int GetLevel() const;
	Vec2<int> GetScreenPos() const;
	int GetCellSize() const;
	void IncreaseScore(int increase);

	void SetSize(Vec2<int> widthHei);
	void SaveScore(std::string boardName, bool &newBest);
	void SetHighScore(int hS);

private:
	std::vector<Cell> cells;
	int width;
	int height;
	int cellSize;
	int padding;
	Vec2<int> screenPos;
	int speed;
	int level;
	bool foundExtraLines;
	bool scoreSaved;

	ScoreManager score;
}; 
