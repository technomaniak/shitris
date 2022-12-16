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
	Tetromino(const bool* shape, 
		int dimension, 
		int overloads,
		std::vector<Vec2<int>> zeroToOne,
		std::vector<Vec2<int>> oneToZero,
		std::vector<Vec2<int>> oneToTwo,
		std::vector<Vec2<int>> twoToOne,
		std::vector<Vec2<int>> twoToThree,
		std::vector<Vec2<int>> threeToTwo,
		std::vector<Vec2<int>> threeToZero,
		std::vector<Vec2<int>> zeroToThree, 
		Color color, 
		Board& board);

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
	static Tetromino SelectRandomPiece(Board& board);

private:

	Vec2<int> boardPos;
	bool isBottom;
	Rotation currentRotation;
	const bool* shape;
	const int dimension;
	const std::vector<Vec2<int>> zeroToOne;
	const std::vector<Vec2<int>> oneToZero;
	const std::vector<Vec2<int>> oneToTwo;
	const std::vector<Vec2<int>> twoToOne;
	const std::vector<Vec2<int>> twoToThree;
	const std::vector<Vec2<int>> threeToTwo;
	const std::vector<Vec2<int>> threeToZero;
	const std::vector<Vec2<int>> zeroToThree;
	const int overloads;
	const Color color;
	Board& board;
};

class Straight : public Tetromino
{
public:
	Straight(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr int dimension = 4;
	static constexpr int overloads = 4;
	static constexpr bool shape[] = { 0, 0, 0, 0,
									  1, 1, 1, 1,
									  0, 0, 0, 0,
									  0, 0, 0, 0 };
	static constexpr Color color = Color{ 102, 191, 255, 255 };

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class Square : public Tetromino
{
public:
	Square(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 1, 1,
									  1, 1 };
	static constexpr int overloads = 4;
	static constexpr int dimension = 2;
	static constexpr Color color = YELLOW;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class Tee : public Tetromino
{
public:
	Tee(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr int dimension = 3;
	static constexpr int overloads = 4;
	static constexpr bool shape[] = { 0, 1, 0,
									  1, 1, 1,
									  0, 0, 0 };
	static constexpr Color color = VIOLET;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class Jay : public Tetromino
{
public:
	Jay(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 1, 0, 0,
									  1, 1, 1,
									  0, 0, 0 };
	static constexpr int dimension = 3;
	static constexpr Color color = BLUE;
	static constexpr int overloads = 4;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class El : public Tetromino
{
public:
	El(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 0, 0, 1,
									  1, 1, 1,
									  0, 0, 0 };
	static constexpr int dimension = 3;
	static constexpr Color color = ORANGE;
	static constexpr int overloads = 4;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class SkewS : public Tetromino
{
public:
	SkewS(Board& board)
		:
		Tetromino(shape,
			dimension,
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color,
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 0, 1, 1,
									  1, 1, 0,
									  0, 0, 0 };
	static constexpr int dimension = 3;
	static constexpr Color color = LIME;
	static constexpr int overloads = 4;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};

class SkewZ : public Tetromino
{
public:
	SkewZ(Board& board)
		:
		Tetromino(shape, 
			dimension, 
			overloads,
			zeroToOne,
			oneToZero,
			oneToTwo,
			twoToOne,
			twoToThree,
			threeToTwo,
			threeToZero,
			zeroToThree,
			color, 
			board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 1, 1, 0,
									  0, 1, 1,
									  0, 0, 0 };
	static constexpr int dimension = 3;
	static constexpr Color color = RED;
	static constexpr int overloads = 4;

	static const std::vector<Vec2<int>> zeroToOne;
	static const std::vector<Vec2<int>> oneToZero;
	static const std::vector<Vec2<int>> oneToTwo;
	static const std::vector<Vec2<int>> twoToOne;
	static const std::vector<Vec2<int>> twoToThree;
	static const std::vector<Vec2<int>> threeToTwo;
	static const std::vector<Vec2<int>> threeToZero;
	static const std::vector<Vec2<int>> zeroToThree;
};