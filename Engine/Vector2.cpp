#include "Vector2.h"
#include <cmath>

Vector2::Vector2(int x_in, int y_in)
	:
	x(x_in),
	y(y_in)
{
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2& Vector2::operator+=(const Vector2& rhs)
{
	return *this = *this + rhs;
}

Vector2 Vector2::operator*(int rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

Vector2& Vector2::operator*=(int rhs)
{
	return *this = *this * rhs;
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2& Vector2::operator-=(const Vector2& rhs)
{
	return *this = *this - rhs;
}

Vector2 Vector2::operator/(int rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

Vector2& Vector2::operator/=(int rhs)
{
	return *this = *this / rhs;
}

float Vector2::GetLength() const
{
	return std::sqrt(float(GetLengthSq()));
}

int Vector2::GetLengthSq() const
{
	return x * x + y * y;
}