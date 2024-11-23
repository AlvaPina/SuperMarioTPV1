#include "Goomba.h"

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Goomba::Goomba(Texture* texture, Vector2D<int> position, Game* game): 
	_texture(texture), _game(game), _pos(position * game->TILE_SIDE)
{
	_rect.w = 32;
	_rect.h = 32;
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();

	_renderFrame = 0;
	_frameCont = 0;
	_movingLeft = true;
}

void Goomba::render() {
	if (_frameCont >= FRAME_SPEED)
	{
		if (_renderFrame == 0) _renderFrame = 1;
		else _renderFrame = 0;
	
		_frameCont = 0;
	}
	else _frameCont++;

	_texture->renderFrame(_rect, 0, _renderFrame);
}

void Goomba::update() {
	if(isInScreen())
	{
		if (_movingLeft) _pos.addX(-GOOMBA_SPEED);
		else _pos.addX(GOOMBA_SPEED);
	}
	_rect.x = _pos.getX() - _game->getMapOffset();
	_rect.y = _pos.getY();
}

bool Goomba::isInScreen()
{
	if (_pos.getX() - _game->getMapOffset() <= _game->WIN_WIDTH) return true;
	else return false;
}