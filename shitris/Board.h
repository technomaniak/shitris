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
		void SetAlternateColor(Color c_in);
		void SetAlternateColor2(Color c_in);
		void Remove();
		bool Exists() const;

		Color GetColor() const;
		Color GetAlternateColor() const;
		Color GetAlternateColor2() const;
	private:
		bool bExists;
		Color c;
		Color c2;
		Color c3;

	};

public:
	Board(Vec2<int> screenPos, int cellSize_in, int padding);
	void SetCell(Vec2<int> pos, Color c, Color c2, Color c3);
	void EraseBoard();
	void MoveCell(Vec2<int> posOld, Vec2<int> posNew);
	void DrawCell(Vec2<int> pos, int style) const;
	void DrawCell(Vec2<int> pos, Color color, Color alternateColor, Color alternateColor2, int style) const;
	void DrawFutureCell(Vec2<int> pos, Color color, Color alternateColor, Color alternateColor2, int style) const;
	void DrawPreviewCell(Vec2<int> pos, Color color, Color alternateColor, Color alternateColor2, int style) const;
	void DrawHeldCell(Vec2<int> pos, Color color, Color alternateColor, Color alternateColor2, int style) const;
	void DrawBorder() const;
	void DrawBorderMenu() const;
	void DrawFutureBorder(Vec2<int> pos, Vec2<int> size) const;
	void DrawHeldBorder(Vec2<int> pos, Vec2<int> size) const;
	void DrawBoardGrid() const;
	void DrawBoardGridMenu() const;
	void DrawFutureBoardGrid(Vec2<int> pos, int amount, int maxDimension) const;
	void DrawHeldBoardGrid(Vec2<int> pos, int amount, int maxDimension) const;
	void DrawBoard() const;
	void DrawFutureBoard(Vec2<int> pos, Vec2<int> size) const;
	void DrawHeldBoard(Vec2<int> pos, Vec2<int> size) const;
	void DrawTimerLine(int timer) const;
	void DrawRestartLine(int timer) const;
	void Draw(int style) const;
	void Draw(int style, bool isInGame) const;
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
	void ResetScore();
	void SetHighScore(int hS);
	void SetPos(Vec2<int> pos);

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
