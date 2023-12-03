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

void MineField::resetGame()
{
	initiliazed = false;

	for (Tile& tile : tiles)
	{
		tile.isMine = false;
		tile.neightborMineCount = 0;
		tile.state = Tile::TILE_STATE::HIDDEN;
	}

	setBombLocations();
	setTileBombCount();
	state = GAME_STATE::PLAYING;

	initiliazed = true;
}

void MineField::update(MainWindow& wnd)
{
	assert(initiliazed);

	//Ignore mouse events if game is over
	if (state != GAME_STATE::PLAYING)
		return;

	//process mouse events
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();
		Vector2 pos = Vector2(e.GetPosX() / SpriteCodex::tileSize,
			e.GetPosY() / SpriteCodex::tileSize);

		//ignore anything outside playing area
		if (pos.x < 0 || pos.x > numTileColumns
			|| pos.y < 0 || pos.y > numTileRows)
			return;

		if (e.GetType() == Mouse::Event::Type::RPress)
			tiles[pos.y * numTileColumns + pos.x].clickTile(Mouse::Event::Type::RPress);
		else if (e.GetType() == Mouse::Event::Type::LPress)
		{
			if (tiles[pos.y * numTileColumns + pos.x].clickTile(Mouse::Event::Type::LPress))
				state = GAME_STATE::DEFEAT;
		}
	}
}

void MineField::draw(Graphics& gfx) const
{
	assert(initiliazed);

	gfx.DrawRect(0, 0, 
		SpriteCodex::tileSize * numTileColumns, SpriteCodex::tileSize * numTileRows,
		SpriteCodex::baseColor);

	for (const Tile& tile : tiles)
	{
		if (state == GAME_STATE::DEFEAT)
			tile.draw(true, gfx);
		else
			tile.draw(false, gfx);
	}

	//if (state == GAME_STATE::DEFEAT)
	//	SpriteCodex::DrawWin(Vector2(150, numTileRows * SpriteCodex::tileSize + 100), gfx);
}
