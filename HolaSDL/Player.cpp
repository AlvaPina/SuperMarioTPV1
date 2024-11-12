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
    SDL_Rect newRect = _rect;

    // Movimiento EJE X (left o right)
    newRect.x += (_marioDirection == RIGHT ? PLAYERSPEED : (_marioDirection == LEFT ? -PLAYERSPEED : 0));

    if (_marioDirection == RIGHT) {
        newRect.x = _position.getX() + PLAYERSPEED;
    }
    else if (_marioDirection == LEFT) {
        if (_position.x > 0)
            newRect.x = _position.getX() - PLAYERSPEED;
    }
    // mirar si se puede aplicar el movimiento en el ejeX
    Collision horizontalCollision = _game->checkCollision(newRect, true);
    if (!horizontalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        if (_position.x >= _game->WIN_WIDTH / 2 && _position.x > 0) // Esto es para ver si en vez de avanzar al player queremos
            _game->addMapOffset(PLAYERSPEED);                       // avanzar solamente el offset
        else _position.x = newRect.x;
    }

    // Movimiento EJE Y (salto o gravedad)
    if (_marioDirection == JUMPING) {
        newRect.y += -PLAYERSPEED;
    }
    else {
        newRect.y += _game->GRAVITY;
    }
    // mirar si se puede aplicar el movimiento en el ejeY
    Collision verticalCollision = _game->checkCollision(newRect, true);
    if (!verticalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        _position.y = newRect.y;
    }

    //Actualizar rect
    _rect.x = _position.getX();
    _rect.y = _position.getY();
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
        case SDLK_d:
            _marioDirection = RIGHT;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            _marioDirection = LEFT;
            break;
        case SDLK_SPACE:
            _marioDirection = JUMPING;
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
        case SDLK_d:
        case SDLK_a:
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
