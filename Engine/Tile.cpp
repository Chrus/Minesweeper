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

bool Tile::clickTile(const Mouse::Event::Type type)
{
	if (state == TILE_STATE::REVEALED)
		return false;

	if (type == Mouse::Event::Type::RPress)
	{
		if (state == TILE_STATE::HIDDEN)
			state = TILE_STATE::FLAGGED;
		else
			state = TILE_STATE::HIDDEN;

		return false;
	}
	else if (type == Mouse::Event::Type::LPress)
	{
		//Flagged tiles need to be unflagged first before they can be revealed
		if (state == TILE_STATE::FLAGGED)
			return false;
		else
		{
			state = TILE_STATE::REVEALED;
			return isMine;
		}
	}

	return false;
}

void Tile::draw(bool gameLost, Graphics& gfx) const
{
	if (gameLost)
	{
		switch (state)
		{
		case TILE_STATE::HIDDEN:
			if (isMine)
				SpriteCodex::DrawTileBomb(getPosition(), gfx);
			else
				SpriteCodex::DrawTileButton(getPosition(), gfx);

			break;
		case TILE_STATE::FLAGGED:
			if (isMine)
			{
				SpriteCodex::DrawTileButton(getPosition(), gfx);
				SpriteCodex::DrawTileFlag(getPosition(), gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(getPosition(), gfx);
				SpriteCodex::DrawTileCross(getPosition(), gfx);
			}

			break;
		case TILE_STATE::REVEALED:
			if (isMine)
				SpriteCodex::DrawTileBombRed(getPosition(), gfx);
			else
				SpriteCodex::DrawTileNumber(getPosition(), neightborMineCount, gfx);

			break;
		}
	}
	else
	{
		switch (state)
		{
		case TILE_STATE::HIDDEN:
			SpriteCodex::DrawTileButton(rect.getPosition(), gfx);
			break;
		case TILE_STATE::FLAGGED:
			SpriteCodex::DrawTileButton(rect.getPosition(), gfx);
			SpriteCodex::DrawTileFlag(rect.getPosition(), gfx);
			break;
		case TILE_STATE::REVEALED:
			if (isMine)
				SpriteCodex::DrawTileBomb(rect.getPosition(), gfx);
			else
				SpriteCodex::DrawTileNumber(rect.getPosition(), neightborMineCount, gfx);

			break;
		}
	}
}
