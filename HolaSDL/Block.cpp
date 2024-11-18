#include "Block.h"
#include <iostream>

Block::Block(Game* game, BlockType type, Point2D<int> pos, Texture* texture, BlockContent content) : _game(game), _type(type), _pos(pos), 
_texture(texture), _content(content)
{
	_rectangulo.w = 32;
	_rectangulo.h = 32;
	_rectangulo.x = pos.getX() * 32;
	_rectangulo.y = pos.getY() * 32;
	_framecont = 0;

	if (type == SORPRESA) renderFrame = 0;
	else renderFrame = 5;
}

void Block::render()
{
	_texture->renderFrame(_rectangulo, 0, renderFrame);
}

void Block::update()
{
	_rectangulo.x = _pos.getX() * 32 - _game->getMapOffset();

	if(_type == SORPRESA)
	{
		if (_framecont >= ANIMATION_SPEED)
		{
			if (renderFrame >= 3) renderFrame = 0;
			else renderFrame++;
			_framecont = 0;
		}
	}
	_framecont++;
}

void Block::hit(SDL_Rect* rectMario)
{
	if (SDL_HasIntersection(&_rectangulo, rectMario)) {
		std::cout << "BloqueColisionandoConMario";

		if(_type == SORPRESA){
			_type = VACIO;
			renderFrame = 4;
			// spawnea el power up
		}
	}
}
