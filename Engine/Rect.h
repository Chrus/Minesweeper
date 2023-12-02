#pragma once
#include "Vector2.h"

class Rect
{
public:
	Rect() = default;
	Rect(const Vector2& topLeft, const int width, const int height);
	Rect(const int left, const int right, const int top, const int bottom);

	Vector2& getPosition() const;
	Vector2& getCenter() const;
	Vector2& getSize() const;

	bool contains(const Vector2& point) const;
	bool overlaps(const Rect& otherRect) const;

private:
	int left;
	int right;
	int top;
	int bottom;
};