#include "Goomba.h"

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Goomba::Goomba(Texture* texture, Vector2D<int> position, Game* game): 
	_texture(texture), _game(game)
{
	_pos.x = position.x * 32;
	_pos.y = position.y * 32;
	_rect.w = 32;
	_rect.h = 32;
	_rect.x = _pos.getX();
	_rect.y = _pos.getY();

	_renderFrame = 0;
	_movingLeft = true;
}

void Goomba::render() {
	_texture->renderFrame(_rect, 0, _renderFrame);
}

void Goomba::update() {
	//_rect.x = _pos.getX() * 32 - _game->getMapOffset();

	if (_movingLeft) _pos.x = _pos.x - GOOMBA_SPEED;
	else _pos.x = _pos.x + GOOMBA_SPEED;
	_rect.x = _pos.getX() - _game->getMapOffset();
	_rect.y = _pos.getY();

}

bool Goomba::isInScreen()
{


	return true;
}