#pragma once
#include "Vector2.h"
#include "Tile.h"
#include "Graphics.h"
#include "MainWindow.h"

class MineField
{
public:
	enum GAME_STATE
	{
		PLAYING,
		VICTORY,
		DEFEAT
	};

	MineField();
	void setBombLocations();
	void setTileBombCount();

	static constexpr int numTileColumns = 45;
	static constexpr int numTileRows = 25;
	static constexpr int numBombs = 100;

	int tileCount() const;
	Tile& getTile(Vector2& position);
	bool checkForVictory();
	Vector2& addOffset(Vector2& oldPosition) const;
	void resetGame();
	void update(MainWindow& wnd);
	void draw(Graphics& gfx) const;
	void revealNeighbors(Tile& tile);

private:
	bool initiliazed = false;

	Tile tiles[numTileColumns * numTileRows];
	GAME_STATE state = GAME_STATE::PLAYING;
	Vector2 offset = Vector2(0, 0);
};

