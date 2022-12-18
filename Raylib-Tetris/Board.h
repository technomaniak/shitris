#pragma once
#include "raylibCpp.h"
#include <vector>
#include "Vec2.h"
#include "ScoreManagement.h"

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
	void DrawBorder() const;
	void DrawBoardGrid() const;
	void DrawBoard() const;
	void DrawTimerLine() const;
	void Draw() const;
	void DrawLevel() const;
	std::vector<int> CheckForLines();
	void ClearLines();
	bool CellExists(Vec2<int> pos) const;
	int GetWidth() const;
	int GetHeight() const;
	int GetSpeed() const;

	void SetSize(Vec2<int> widthHei);

private:
	std::vector<Cell> cells;
	int width;
	int height;
	int cellSize;
	int padding;
	Vec2<int> screenPos;
	int speed;
	int level;

	ScoreManagement score;
}; 
