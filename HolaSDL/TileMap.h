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


public:
	TileMap(Game* game, Texture* background, std::vector<std::vector<int>> tileIndices);
	int renderTileMap();
};

