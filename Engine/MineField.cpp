#include "MineField.h"
#include <assert.h>
#include "SpriteCodex.h"
#include <random>
#include <algorithm>

MineField::MineField()
{
	assert(!initiliazed);

	//set tile positions
	for (int x = 0; x < numTileColumns; x++)
	{
		for (int y = 0; y < numTileRows; y++)
		{
			tiles[y * numTileColumns + x] = Tile(Vector2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize),
				SpriteCodex::tileSize, SpriteCodex::tileSize);
			tiles[y * numTileColumns + x].arrayPosition = Vector2(x, y);
		}
	}

	setBombLocations();
	setTileBombCount();

	initiliazed = true;
}

void MineField::setBombLocations()
{
	assert(!initiliazed);
	assert(numBombs > 0 && numBombs < numTileColumns * numTileRows);

	int bombsLeft = numBombs;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, numTileColumns);
	std::uniform_int_distribution<int> yDist(0, numTileRows);

	while (bombsLeft != 0)
	{
		int tempX = xDist(rng);
		int tempY = yDist(rng);

		Tile& tile = tiles[tempY * numTileColumns + tempX];
		if (!tile.isMine)
		{
			tile.isMine = true;
			bombsLeft--;
		}
	}
}

void MineField::setTileBombCount()
{
	for (Tile& tile : tiles)
	{
		//Look at the 8 neighbors of each tile using std::min() to prevent going out of bounds on border tiles
		for (int x = std::max(0, tile.arrayPosition.x - 1); 
			x <= std::min(numTileColumns - 1, tile.arrayPosition.x + 1); 
			x++)
		{
			for (int y = std::max(0, tile.arrayPosition.y - 1);
				y <= std::min(numTileRows - 1, tile.arrayPosition.y + 1);
				y++)
			{
				//only check neighbors not itself
				if (tile.arrayPosition.x == x && tile.arrayPosition.y == y)
					continue;

				if (tiles[y * numTileColumns + x].isMine)
					tile.neightborMineCount++;
			}
		}
	}
}

int MineField::tileCount() const
{
	return numTileColumns * numTileRows;
}

Tile& MineField::getTile(Vector2& position)
{
	position /= SpriteCodex::tileSize;
	return tiles[position.y * numTileColumns + position.x];
}

void MineField::update()
{
	assert(initiliazed);
}

void MineField::draw(Graphics& gfx) const
{
	assert(initiliazed);

	gfx.DrawRect(0, 0, 
		SpriteCodex::tileSize * numTileColumns, SpriteCodex::tileSize * numTileRows,
		Colors::Gray);

	for (const Tile& tile : tiles)
	{
		tile.draw(gfx);
	}
}
