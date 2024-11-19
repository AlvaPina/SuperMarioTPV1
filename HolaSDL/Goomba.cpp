#include "Goomba.h"

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Goomba::Goomba(Texture* texture, Vector2D<int> position, Game* game): 
	_texture(texture), _pos(position), _game(game)
{
	_rect.w = 32;
	_rect.h = 32;
	_rect.x = _pos.getX() * 32;
	_rect.y = _pos.getY() * 32;

	_renderFrame = 0;
	_movingLeft = true;
}

void Goomba::render() {
	_texture->renderFrame(_rect, 0, _renderFrame);
}

void Goomba::update() {
	_rect.x = _pos.getX() * 32 - _game->getMapOffset();


}