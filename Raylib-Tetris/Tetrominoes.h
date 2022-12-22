#pragma once
#include "Vec2.h"
#include "raylibCpp.h"
#include "Board.h"
#include <vector>
#include <rlgl.h>
#include <fstream>

class Tetromino
{
public:
	enum class Rotation
	{
		UP,
		RIGHT,
		DOWN,
		LEFT
	};
public:

	Tetromino(Board& board);

	void RotateClockwise();
	void RotateCounterClockwise();
	void RotateFull();
	void Fall();
	void PlaceTetromino();
	void MoveRight();
	void MoveLeft();
	bool IsBottom();
	bool IsBottomButTop();
	void Draw() const;
	void Draw(int style) const;
	void HardDrop();
	void AlignPos(Tetromino tetromino);

	void SetColor(Color c);
	void SetShape(std::vector<bool> shp);
	void SetDimension(int dim);
	void SetOverloads(int overl);
	void SetZeroToOne(std::vector<Vec2<int>> zeroToOn);
	void SetOneToZero(std::vector<Vec2<int>> oneToZer);
	void SetTwoToOne(std::vector<Vec2<int>> twoToOn);
	void SetOneToTwo(std::vector<Vec2<int>> oneToTw);
	void SetTwoToThree(std::vector<Vec2<int>> twoToThre);
	void SetThreeToTwo(std::vector<Vec2<int>> threeToTw);
	void SetThreeToZero(std::vector<Vec2<int>> threeToZer);
	void SetZeroToThree(std::vector<Vec2<int>> zerToThre);
	void SetCurrentPiece(int id);
	void SetIsAnythingSetToHeld(bool val);
	void SetRotation(Rotation rotation);
	void SetALias(std::string newAlias);

	void SetFallen(bool newData);
	bool GetFallen() const;
	void SetPos(Vec2<int> pos);

	Color GetColor() const;
	int GetDimension() const;
	std::vector<bool> GetShape() const;
	std::vector<Vec2<int>> GetZeroToOne() const;
	std::vector<Vec2<int>> GetOneToZero() const;
	std::vector<Vec2<int>> GetTwoToOne() const;
	std::vector<Vec2<int>> GetOneToTwo() const;
	std::vector<Vec2<int>> GetTwoToThree() const;
	std::vector<Vec2<int>> GetThreeToTwo() const;
	std::vector<Vec2<int>> GetThreeToZero() const;
	std::vector<Vec2<int>> GetZeroToThree() const;
	int GetOverloads() const;
	int GetCurrentPieceId() const;
	bool getIsAnythingHeld() const;
	int GetRotation() const;
	Vec2<int> GetPos() const;
	std::string GetAlias() const;

private:
	Vec2<int> boardPos;
	bool isBottom;
	bool isBottomButTop;
	Rotation currentRotation;
	std::vector<bool> shape;
	int dimension;
	std::vector<Vec2<int>> zeroToOne;
	std::vector<Vec2<int>> oneToZero;
	std::vector<Vec2<int>> oneToTwo;
	std::vector<Vec2<int>> twoToOne;
	std::vector<Vec2<int>> twoToThree;
	std::vector<Vec2<int>> threeToTwo;
	std::vector<Vec2<int>> threeToZero;
	std::vector<Vec2<int>> zeroToThree;
	int overloads;
	Color color;
	Board& board;
	bool fallen;
	int currentPieceId;
	int isAnythingHeld;
	std::string alias;
};
