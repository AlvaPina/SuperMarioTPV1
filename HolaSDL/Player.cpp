#include <iostream>

#include "Player.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Player::Player(Texture* texture, Vector2D<int> position, Game* game, int lives, bool movingRight, bool superMario):
	_texture(texture), _position(position), _game(game), _lives(lives), _superMario(superMario)
{
	_onTheFloor = true;
	_rect.w = 50;
	_rect.h = 50;
	_rect.x = _position.getX();
	_rect.y = _position.getY();
    _playerFrame = 0;
    _playerFlip = SDL_FLIP_NONE;
}

void Player::render()
{
    switch(_animationState)
    {
    case STOPPED:
        _playerFrame = 0;
        break;
    case MOVING_R: case MOVING_L:
        if (_playerFrame == 2) _playerFrame = 1;
        else _playerFrame = 2;
        break;
    case AN_JUMPING:
        _playerFrame = 5;
        break;
    }

	_texture->renderFrame(_rect, 0, _playerFrame, _playerFlip);
}

void Player::update()
{
    SDL_Rect newRect = _rect;

    // Movimiento EJE X (left o right)
    newRect.x += (_horizontalDirection == RIGHT ? PLAYERSPEED : (_horizontalDirection == LEFT ? -PLAYERSPEED : 0));

    if (_horizontalDirection == RIGHT) {
        newRect.x = _position.getX() + PLAYERSPEED;
    }
    else if (_horizontalDirection == LEFT) {
        if (_position.x > 0)
            newRect.x = _position.getX() - PLAYERSPEED;
    }
    // mirar si se puede aplicar el movimiento en el ejeX
    Collision horizontalCollision = _game->checkCollision(newRect, true);
    if (!horizontalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        if (_position.x >= _game->WIN_WIDTH / 2 && _position.x > 0 && _horizontalDirection == RIGHT) // Esto es para ver si en vez de avanzar al player queremos
            _game->addMapOffset(PLAYERSPEED);                       // avanzar solamente el offset
        else _position.x = newRect.x;
    }

    // Movimiento EJE Y (salto o gravedad)
    if (_verticalDirection == JUMPING || _verticalDirection == FALLING) {
        if(_verticalSpeed < VERTICAL_MAX_SPEED)
        _verticalSpeed += _game->GRAVITY/10;
    }
    newRect.y += _verticalSpeed;
    // mirar si se puede aplicar el movimiento en el ejeY
    Collision verticalCollision = _game->checkCollision(newRect, true);
    if (!verticalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        _position.y = newRect.y;
        _onTheFloor = false;
    }
    else {
        _onTheFloor = true;
        if (_verticalDirection == JUMPING) {
            _verticalDirection = VERTICAL_STATIC;
        }
    }

    //Actualizar rect
    _rect.x = _position.getX();
    _rect.y = _position.getY();

    // Actualizar estatus de la animacion LIMPIAR
    if (!_onTheFloor) _animationState = AN_JUMPING;
    else
    {
        switch(_horizontalDirection)
        {
        case RIGHT:
            _playerFlip = SDL_FLIP_NONE;
            break;
        case LEFT:
            _playerFlip = SDL_FLIP_HORIZONTAL;
            break;

        case HORIZONTAL_STATIC:
            _animationState = STOPPED;
            break;        
        }
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
        case SDLK_d:
            _horizontalDirection = RIGHT;
            _animationState = MOVING_R;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            _horizontalDirection = LEFT;
            _animationState = MOVING_L;
            break;
        case SDLK_SPACE:
            if (_onTheFloor) {
                _verticalSpeed = -JUMP_POWER;
                _verticalDirection = JUMPING;
                _animationState = AN_JUMPING;
            }
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
            _horizontalDirection = HORIZONTAL_STATIC;
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
