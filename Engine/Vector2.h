#pragma once

class Vector2
{
public:
	Vector2() = default;
	Vector2(int x_in, int y_in);
	Vector2 operator+(const Vector2& rhs) const;
	Vector2& operator+=(const Vector2& rhs);
	Vector2 operator*(int rhs) const;
	Vector2& operator*=(int rhs);
	Vector2 operator-(const Vector2& rhs) const;
	Vector2& operator-=(const Vector2& rhs);
	Vector2 operator/(int rhs) const;
	Vector2& operator/=(int rhs);
	float GetLength() const;
	int GetLengthSq() const;
public:
	int x;
	int y;
};