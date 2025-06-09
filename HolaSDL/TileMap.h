#pragma once
#include "checkML.h"

#include <vector>
#include "PlayState.h"

class TileMap
{
private:
	std::vector<std::vector<int>> _tileIndices;
	GameState* gameState;
	Texture* _background;

	void loadTileMap();
public:
	const uint TILE_SIDE;
	const uint TILE_MAP;

	TileMap(GameState* game, Texture* background);
	int render() const;
	Collision hit(const SDL_Rect& rect, Collision::Target target);

	static constexpr uint OBSTACLE_THRESHOLD = 4;

};

