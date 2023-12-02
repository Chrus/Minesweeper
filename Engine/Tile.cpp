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

void Tile::init(const bool isMine, const int neightborMineCount)
{
	assert(neightborMineCount >= 0 && neightborMineCount <= 8);
	assert(!initialized);

	this->isMine = isMine;
	this->neightborMineCount = neightborMineCount;
	initialized = true;
}

Vector2& Tile::getPosition() const
{
	return rect.getPosition();
}

void Tile::clickTile(const Keyboard::Event& event)
{
	assert(initialized);
	//TODO
}

void Tile::draw(Graphics& gfx) const
{
	assert(initialized);

	if (state == HIDDEN)
		SpriteCodex::DrawTileButton(rect.getPosition(), gfx);
}
