#pragma once
#include "Vec2.h"
#include "raylibCpp.h"
#include "Board.h"
#include <rlgl.h>

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
	static constexpr bool shape[] = { 0, 0, 0, 0,
									  1, 1, 1, 1,
									  0, 0, 0, 0,
									  0, 0, 0, 0 };
	static constexpr int dimension = 4;
	static constexpr Color color = Color{ 102, 191, 255, 255 };
	
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
};