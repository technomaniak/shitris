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
	Tetromino(const bool* shape, int dimension, Color color, Board& board);
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
	const Color color;
	Board& board;
};

class Straight : public Tetromino
{
public:
	Straight(Board& board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr int dimension = 4;
	static constexpr bool shape[] = { 0, 0, 0, 0,
									  1, 1, 1, 1,
									  0, 0, 0, 0,
									  0, 0, 0, 0 };
	static constexpr Color color = Color{ 102, 191, 255, 255 };
	static constexpr int overloads = 4;

	const std::vector<Vec2<int>> zeroToOne = { {-2, 0}, {1, 0}, {-2 , -1}, {1, 2} };
	const std::vector<Vec2<int>> oneToZero = { {2, 0}, {-1, 0}, {2 , 1}, {-1, -2} };
	const std::vector<Vec2<int>> oneToTwo = { {-1, 0}, {2, 0}, {-1 , 2}, {2, -1} };
	const std::vector<Vec2<int>> twoToOne = { {1, 0}, {-2, 0}, {1 , -2}, {-2, 1} };
	const std::vector<Vec2<int>> twoToThree = { {2, 0}, {-1, 0}, {2 , 1}, {-1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-2, 0}, {1, 0}, {-2 , -1}, {1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {1, 0}, {-2, 0}, {1 , -2}, {-2, 1} };
	const std::vector<Vec2<int>> zeroToThree = { {-1, 0}, {2, 0}, {-1 , 2}, {2, -1} };
};

class Square : public Tetromino
{
public:
	Square(Board& board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 1, 1,
									  1, 1 };
	static constexpr int dimension = 2;
	static constexpr Color color = YELLOW;
	static constexpr int overloads = 4;

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};

class Tee : public Tetromino
{
public:
	Tee(Board& board)
		:
		Tetromino(shape, dimension, color, board)
	{
		static_assert(sizeof(shape) / sizeof(bool) == dimension * dimension); // check if dimension is valid
	}
private:
	static constexpr bool shape[] = { 0, 1, 0,
									  1, 1, 1,
									  0, 0, 0 };
	static constexpr int dimension = 3;
	static constexpr Color color = VIOLET;
	static constexpr int overloads = 4;

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};

class Jay : public Tetromino
{
public:
	Jay(Board& board)
		:
		Tetromino(shape, dimension, color, board)
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

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};

class El : public Tetromino
{
public:
	El(Board& board)
		:
		Tetromino(shape, dimension, color, board)
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

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};

class SkewS : public Tetromino
{
public:
	SkewS(Board& board)
		:
		Tetromino(shape, dimension, color, board)
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

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};

class SkewZ : public Tetromino
{
public:
	SkewZ(Board& board)
		:
		Tetromino(shape, dimension, color, board)
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

	const std::vector<Vec2<int>> zeroToOne = { {-1, 0}, {-1, 1}, {0 , -2}, {-1, -2} };
	const std::vector<Vec2<int>> oneToZero = { {1, 0}, {1, -1}, {0, 2}, {1, 2} };
	const std::vector<Vec2<int>> oneToTwo = { {1, 0}, {1, -1}, {0 , 2}, {1, 2} };
	const std::vector<Vec2<int>> twoToOne = { {-1, 0}, {-1, 1}, {0, -2}, {-1, -2} };
	const std::vector<Vec2<int>> twoToThree = { {1, 0}, {1, 1}, {0 , -2}, {1, -2} };
	const std::vector<Vec2<int>> threeToTwo = { {-1, 0}, {-1, -1}, {0, 2}, {-1, 2} };
	const std::vector<Vec2<int>> threeToZero = { {-1, 0}, {-1, -1}, {0 , 2}, {-1, 2} };
	const std::vector<Vec2<int>> zeroToThree = { {1, 0}, {1, 1}, {0, -2}, {1, -2} };
};