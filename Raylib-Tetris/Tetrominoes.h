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
	void Draw() const;
	void DebugNum();

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

private:

	Vec2<int> boardPos;
	bool isBottom;
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
};

//class Straight : public Tetromino
//{
//public:
//	Straight(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static constexpr int dimension = 4;
//	static constexpr int overloads = 4;
//	static inline std::vector<bool> shape = { 0, 0, 0, 0,
//									  1, 1, 1, 1,
//									  0, 0, 0, 0,
//									  0, 0, 0, 0 };
//	static constexpr Color color = Color{ 102, 191, 255, 255 };
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class Square : public Tetromino
//{
//public:
//	Square(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static inline std::vector<bool> shape = { 1, 1,
//									  1, 1 };
//	static constexpr int overloads = 4;
//	static constexpr int dimension = 2;
//	static constexpr Color color = YELLOW;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class Tee : public Tetromino
//{
//public:
//	Tee(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static constexpr int dimension = 3;
//	static constexpr int overloads = 4;
//	static inline std::vector<bool> shape = { 0, 1, 0,
//									  1, 1, 1,
//									  0, 0, 0 };
//	static constexpr Color color = VIOLET;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class Jay : public Tetromino
//{
//public:
//	Jay(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static inline std::vector<bool> shape = { 1, 0, 0,
//									  1, 1, 1,
//									  0, 0, 0 };
//	static constexpr int dimension = 3;
//	static constexpr Color color = BLUE;
//	static constexpr int overloads = 4;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class El : public Tetromino
//{
//public:
//	El(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static inline std::vector<bool> shape = { 0, 0, 1,
//									  1, 1, 1,
//									  0, 0, 0 };
//	static constexpr int dimension = 3;
//	static constexpr Color color = ORANGE;
//	static constexpr int overloads = 4;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class SkewS : public Tetromino
//{
//public:
//	SkewS(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static inline std::vector<bool> shape = { 0, 1, 1,
//									  1, 1, 0,
//									  0, 0, 0 };
//	static constexpr int dimension = 3;
//	static constexpr Color color = LIME;
//	static constexpr int overloads = 4;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};
//
//class SkewZ : public Tetromino
//{
//public:
//	SkewZ(Board& board)
//		:
//		Tetromino(shape,
//			dimension,
//			overloads,
//			zeroToOne,
//			oneToZero,
//			oneToTwo,
//			twoToOne,
//			twoToThree,
//			threeToTwo,
//			threeToZero,
//			zeroToThree,
//			color,
//			board)
//	{
//			}
//private:
//	static inline std::vector<bool> shape = { 1, 1, 0,
//									  0, 1, 1,
//									  0, 0, 0 };
//	static constexpr int dimension = 3;
//	static constexpr Color color = RED;
//	static constexpr int overloads = 4;
//
//	static const std::vector<Vec2<int>> zeroToOne;
//	static const std::vector<Vec2<int>> oneToZero;
//	static const std::vector<Vec2<int>> oneToTwo;
//	static const std::vector<Vec2<int>> twoToOne;
//	static const std::vector<Vec2<int>> twoToThree;
//	static const std::vector<Vec2<int>> threeToTwo;
//	static const std::vector<Vec2<int>> threeToZero;
//	static const std::vector<Vec2<int>> zeroToThree;
//};