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
