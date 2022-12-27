#pragma once

template <typename T>
class Vec2
{
public:
	Vec2() = default;
	constexpr Vec2(T x, T y)
		:
		x(x),
		y(y)
	{

	}

	constexpr T GetX() const { return x; };
	constexpr T GetY() const { return y; };
	constexpr void SetX(T x_in) { x = x_in; };
	constexpr void SetY(T y_in) { y = y_in; };

public:
	constexpr bool operator==(const Vec2& rhs) const
	{
		return ( x == rhs.x, y == rhs.y );
	}
	constexpr bool operator!=(const Vec2& rhs) const
	{
		return (x != rhs.x, y != rhs.y);
	}
	constexpr Vec2 operator+(const Vec2& rhs) const
	{
		return { x + rhs.x, y + rhs.y };
	}
	constexpr Vec2 operator+(const int rhs) const
	{
		return { x + rhs, y + rhs };
	}
	constexpr Vec2& operator+=(const Vec2& rhs)
	{
		*this = *this + rhs;
	}
	constexpr Vec2 operator-(const Vec2& rhs) const
	{
		return { x - rhs.x, y - rhs.y };
	}
	constexpr Vec2 operator-(const int rhs) const
	{
		return { x - rhs, y - rhs };
	}
	constexpr Vec2& operator-=(const Vec2& rhs)
	{
		*this = *this - rhs;
	}
	constexpr Vec2 operator*(const Vec2& rhs) const
	{
		return { x * rhs.x, y * rhs.y };
	}
	constexpr Vec2 operator*(const int rhs) const
	{
		return { x * rhs, y * rhs };
	}
	constexpr Vec2& operator*=(const Vec2& rhs)
	{
		*this = *this * rhs;
	}
	constexpr bool operator<(const Vec2& rhs) const
	{
		if (x < rhs.x && y < rhs.y)
		{
			return true;
		}
		return false;
	}
	constexpr bool operator>(const Vec2& rhs) const
	{
		if (x > rhs.x && y > rhs.y)
		{
			return true;
		}
		return false;
	}
private:
	T x;
	T y;
};