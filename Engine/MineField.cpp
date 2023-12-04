#include "MineField.h"
#include <assert.h>
#include "SpriteCodex.h"
#include <random>
#include <algorithm>

MineField::MineField()
{
	assert(!initiliazed);

	//calculate offset value to add to all calculations to center the playing field
	offset.x += ((Graphics::ScreenWidth - numTileColumns * SpriteCodex::tileSize) / 2);
	offset.y += ((Graphics::ScreenHeight - numTileRows * SpriteCodex::tileSize) / 2);

	//set tile positions
	for (int x = 0; x < numTileColumns; x++)
	{
		for (int y = 0; y < numTileRows; y++)
		{
			Vector2& tilePosition = addOffset(Vector2(x * SpriteCodex::tileSize, y * SpriteCodex::tileSize));

			tiles[y * numTileColumns + x] = Tile(tilePosition, SpriteCodex::tileSize, SpriteCodex::tileSize);
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
	position -= offset;
	position /= SpriteCodex::tileSize;
	return tiles[position.y * numTileColumns + position.x];
}

Vector2& MineField::addOffset(Vector2& oldPosition) const
{
	return oldPosition += offset;
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

bool MineField::checkForVictory()
{
	for (Tile& tile : tiles)
	{
		if (tile.state == Tile::TILE_STATE::HIDDEN)
			return false;
		if (tile.state == Tile::TILE_STATE::FLAGGED && !tile.isMine)
			return false;
	}

	state = GAME_STATE::VICTORY;
	return true;
}

void MineField::update(MainWindow& wnd)
{
	assert(initiliazed);

	//process mouse events
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event e = wnd.mouse.Read();

		//Ignore mouse events if game is over
		//But still process the Read()s or else bugs happen for some reason
		if (state != GAME_STATE::PLAYING)
			continue;

		//ignore anything outside play area
		Rect playArea = Rect(offset, numTileColumns * SpriteCodex::tileSize, numTileRows * SpriteCodex::tileSize);
		if (!playArea.contains(Vector2(e.GetPosX(), e.GetPosY())))
			continue;

		Tile& clickedTile = getTile(Vector2(e.GetPosX(), e.GetPosY()));
		if (e.GetType() == Mouse::Event::Type::RPress)
			clickedTile.clickTile(Mouse::Event::Type::RPress);
		else if (e.GetType() == Mouse::Event::Type::LPress)
		{
			if (clickedTile.clickTile(Mouse::Event::Type::LPress))
				state = GAME_STATE::DEFEAT;
			else
				revealNeighbors(clickedTile);
		}
	}
}

void MineField::draw(Graphics& gfx) const
{
	assert(initiliazed);

	gfx.DrawRect(offset.x, offset.y, 
		SpriteCodex::tileSize * numTileColumns + offset.x,
		SpriteCodex::tileSize * numTileRows + offset.y,
		SpriteCodex::baseColor);

	for (const Tile& tile : tiles)
	{
		if (state == GAME_STATE::DEFEAT)
			tile.draw(true, gfx);
		else
			tile.draw(false, gfx);
	}

	if (state == GAME_STATE::VICTORY)
		SpriteCodex::DrawWin(Vector2(150, numTileRows * SpriteCodex::tileSize + 100), gfx);
}

void MineField::revealNeighbors(Tile& tile)
{
	if (tile.isMine)
		return;
	tile.state = Tile::TILE_STATE::REVEALED;
	if (tile.neightborMineCount != 0)
		return;

	for (int x = std::max(0, tile.arrayPosition.x - 1);
		x <= std::min(numTileColumns - 1, tile.arrayPosition.x + 1);
		x++)
	{
		for (int y = std::max(0, tile.arrayPosition.y - 1);
			y <= std::min(numTileRows - 1, tile.arrayPosition.y + 1);
			y++)
		{
			if (tiles[y * numTileColumns + x].state == Tile::TILE_STATE::REVEALED)
				continue;

			revealNeighbors(tiles[y * numTileColumns + x]);
		}
	}
}
