#include <iostream>

#include "Player.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Player::Player(Texture* texture, Vector2D<int> position, Game* game, int lives, bool movingRight, bool superMario):
	_texture(texture), _position(position), _game(game), _lives(lives), _movingRight(movingRight), _superMario(superMario)
{
	_onTheFloor = false;
	_rect.w = 50;
	_rect.h = 50;
	_rect.x = _position.getX();
	_rect.y = _position.getY();
}

void Player::render()
{
	_texture->renderFrame(_rect, 0,0);
}

void Player::update()
{


}

void Player::hit()
{
	if (_superMario) _superMario = false;
	else _lives--; // ha muerto
}

void Player::handleEvent()
{
	
}
