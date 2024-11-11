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
	_rect.x = _position.getX();
	_rect.y = _position.getY();
	if (_marioDirection == RIGHT) {
		if (_position.x >= _game->WIN_WIDTH / 2 && _position.x > 0)
			_game->addMapOffset(PLAYERSPEED);
		else _position.x = _position.getX() + PLAYERSPEED;
	}
	else if (_marioDirection == LEFT) {
        if(_position.x > 0)
		_position.x = _position.getX() - PLAYERSPEED;
	}
}

void Player::hit()
{
	if (_superMario) _superMario = false;
	else _lives--; // ha muerto
}

void Player::handleEvent(const SDL_Event& evento)
{
    if (evento.type == SDL_KEYDOWN) {
        switch (evento.key.keysym.sym)
        {
        case SDLK_RIGHT:
            _marioDirection = RIGHT;
            break;
        case SDLK_LEFT:
            _marioDirection = LEFT;
            break;
        case SDLK_SPACE:
            
            break;
        default:
            break;
        }
    }
    else if (evento.type == SDL_KEYUP) {
        switch (evento.key.keysym.sym)
        {
        case SDLK_RIGHT:
        case SDLK_LEFT:
            _marioDirection = STATIC;
            break;
        default:
            break;
        }
    }
}

int Player::getX()
{
	return _position.getX();
}

int Player::getY()
{
	return _position.getY();
}
