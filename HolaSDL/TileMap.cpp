#include "TileMap.h"

#include <iostream>

TileMap::TileMap(Game* game, Texture* patternsTexture, int indices[16][32])
	: _game(game), _patternsTexture(patternsTexture)
{
	for (int i = 0; i < sizeof(indices[0]); i++) {

	}
}
