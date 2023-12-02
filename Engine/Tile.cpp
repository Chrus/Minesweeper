#include "Tile.h"
#include "SpriteCodex.h"
#include <assert.h>

Tile::Tile(const Rect& rect)
	:
	rect(rect)
{
}

Tile::Tile(const Vector2& topLeft, const int width, const int height)
	:
	Tile(Rect(topLeft.x, topLeft.x + width, topLeft.y, topLeft.y + height))
{
}

Vector2& Tile::getPosition() const
{
	return rect.getPosition();
}

void Tile::clickTile(const Keyboard::Event& event)
{
	//TODO
}

void Tile::draw(Graphics& gfx) const
{
	//if (state == HIDDEN)
	//	SpriteCodex::DrawTileButton(rect.getPosition(), gfx);
}
