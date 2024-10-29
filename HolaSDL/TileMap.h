#pragma once

#include "Game.h"

class TileMap
{
private:
	static const int TILE_MAP = 2;

	int _indices[16][32];
	Game* _game;
	Texture* _patternsTexture;

public:
	TileMap(Game* game, Texture* patternsTexture, int indices[16][32]);

};

