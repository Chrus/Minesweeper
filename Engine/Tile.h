#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Keyboard.h"
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
	void init(const bool isMine, const int neightborMineCount);

	Vector2& getPosition() const;
	void clickTile(const Keyboard::Event& event);
	void draw(Graphics& gfx) const;

private:
	Rect rect;
	bool initialized = false;

	bool isMine = false;
	int neightborMineCount = 0;
	TILE_STATE state = HIDDEN;
};