#include "Block.h"
#include <iostream>

Block::Block(Game* game, BlockType type, Point2D<int> pos, Texture* texture) : _game(game), _type(type), _pos(pos), _texture(texture)
{
	_rectangulo.w = 32;
	_rectangulo.h = 32;
	_rectangulo.x = pos.getX() * game->WIN_WIDTH;
	_rectangulo.y = pos.getY() * game->WIN_HEIGHT;
}

void Block::render()
{
	_texture->renderFrame(_rectangulo, 0, _type);
}

void Block::update()
{
	_rectangulo.x = _pos.getX() * _game->WIN_WIDTH - _game->getMapOffset();
}

void Block::hit(SDL_Rect* rectMario)
{
	if (SDL_HasIntersection(&_rectangulo, rectMario)) {
		std::cout << "BloqueColisionandoConMario";
	}
}
