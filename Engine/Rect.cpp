#include "Rect.h"
#include "Graphics.h"
#include <assert.h>

Rect::Rect(const Vector2& topLeft, const int width, const int height)
	:
	Rect(topLeft.x, topLeft.x + width, topLeft.y, topLeft.y + height)
{
}

Rect::Rect(const int left, const int right, const int top, const int bottom)
	:
	left(left),
	right(right),
	top(top),
	bottom(bottom)
{
	assert(left >= 0);
	assert(right > left);
	assert(right <= Graphics::ScreenWidth);
	
	assert(top >= 0);
	assert(bottom > top);
	assert(bottom <= Graphics::ScreenHeight);
}

/// <summary>
/// 
/// </summary>
/// <returns>Returns the top left corner of the rect</returns>
Vector2& Rect::getPosition() const
{
	return Vector2(left, top);
}

/// <summary>
/// 
/// </summary>
/// <returns>Returns the center of the rect</returns>
Vector2& Rect::getCenter() const
{
	Vector2 temp = getSize();
	return Vector2(left + temp.x / 2, top + temp.y / 2);
}

/// <summary>
/// Returns the width and height of the Rect
/// </summary>
/// <returns>Vector2.x == width, Vector2.y == height</returns>
Vector2& Rect::getSize() const
{
	return Vector2(right - left, bottom - top);
}

bool Rect::contains(const Vector2& point) const
{
	return point.x >= left && point.x <= right
		&& point.y >= top && point.y <= bottom;
}

bool Rect::overlaps(const Rect& otherRect) const
{
	return right > otherRect.left && left < otherRect.right
		&& bottom > otherRect.top && top < otherRect.bottom;
}
