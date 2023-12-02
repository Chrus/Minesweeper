#pragma once
#include "Vector2.h"
#include "Tile.h"
#include "Graphics.h"

class MineField
{
public:
	MineField();
	void setBombLocations();
	void setTileBombCount();

	static constexpr int numTileColumns = 45;
	static constexpr int numTileRows = 25;
	static constexpr int numBombs = 250;

	int tileCount() const;
	Tile& getTile(Vector2& position);
	void update();
	void draw(Graphics& gfx) const;

private:
	bool initiliazed = false;

	Tile tiles[numTileColumns * numTileRows];
	Vector2 offset = Vector2(0, 0);
};

