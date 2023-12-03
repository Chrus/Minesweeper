#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Mouse.h"
#include "Graphics.h"

class Tile
{
public:
	enum TILE_STATE
	{
		HIDDEN,
		REVEALED,
		FLAGGED
	};

	Tile() = default;
	Tile(const Rect& rect);
	Tile(const Vector2& topLeft, const int width, const int height);

	Vector2& getPosition() const;
	/// <summary>
/// Process left and right clicks
/// </summary>
/// <param name="type">Only checks Mouse::Event::Type LPress and RPress</param>
/// <returns>True if game over from clicking a bomb.  False if game can continue (Does not check for game completed)</returns>
	bool clickTile(const Mouse::Event::Type type);
	void draw(bool gameLost, Graphics& gfx) const;

	bool isMine = false;
	int neightborMineCount = 0;
	Vector2 arrayPosition;
	TILE_STATE state = HIDDEN;

private:
	Rect rect;
};