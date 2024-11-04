#pragma once

#include "Game.h"
#include <vector>

class TileMap
{
private:
	static constexpr uint TILE_SIDE = 32;
	static constexpr uint TILE_MAP = 16;

	std::vector<std::vector<int>> _tileIndices;
	Game* _game;
	Texture* _background;
	int mapOffset;

	void loadTileMap();
public:
	TileMap(Game* game, Texture* background);
	int renderTileMap();
	int getMapOffset() const { return mapOffset; }

};

