#pragma once

#include "Game.h"
#include <vector>

class TileMap
{
private:
	std::vector<std::vector<int>> _tileIndices;
	Game* _game;
	Texture* _background;

	void loadTileMap();
public:
	const uint TILE_SIDE;
	const uint TILE_MAP;

	TileMap(Game* game, Texture* background);
	int render() const;
	Collision hit(const SDL_Rect& rect, Collision::Target target);

	static constexpr uint OBSTACLE_THRESHOLD = 4;

};

