#include <iostream>

#include "Player.h"
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Player::Player(Texture* texture, Vector2D<int> position, Game* game, int lives, bool movingRight, bool superMario)
    : SceneObject(game, position, { 0,0 }, false, 1), _lives(lives), _superMario(superMario), _texture(texture)
{
	_onTheFloor = true;
    _playerFrame = 0;
    _playerFlip = SDL_FLIP_NONE;
}

Player::~Player()
{
}

void Player::Render() const
{
    if (_texture) {
        _texture->renderFrame(rect, 0, _playerFrame, _playerFlip);
    }
}

void Player::Update()
{
    HandleAnims();

    SDL_Rect newRect = rect;

    // Movimiento EJE X (left o right)
    newRect.x += (_horizontalDirection == RIGHT ? PLAYERSPEED : (_horizontalDirection == LEFT ? -PLAYERSPEED : 0));

    if (_horizontalDirection == RIGHT) {
        newRect.x = pos.getX() + PLAYERSPEED;
    }
    else if (_horizontalDirection == LEFT) {
        if (pos.x > 0)
            newRect.x = pos.getX() - PLAYERSPEED;
    }
    // mirar si se puede aplicar el movimiento en el ejeX
    Collision horizontalCollision = game->checkCollision(newRect, true);
    if (!horizontalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        if (pos.x >= game->WIN_WIDTH / 2 && pos.x > 0 && _horizontalDirection == RIGHT) // Esto es para ver si en vez de avanzar al player queremos
            game->addMapOffset(PLAYERSPEED);                       // avanzar solamente el offset
        else pos.x = newRect.x;
    }

    // Movimiento EJE Y (salto o gravedad)
    if (_verticalDirection == JUMPING || _verticalDirection == FALLING) {
        if(_verticalSpeed < VERTICAL_MAX_SPEED)
        _verticalSpeed += game->GRAVITY/10;
    }
    newRect.y += _verticalSpeed;
    // mirar si se puede aplicar el movimiento en el ejeY
    Collision verticalCollision = game->checkCollision(newRect, true);
    if (!verticalCollision.collides) {
        // No hubo colision y podemos avanzarlo
        pos.y = newRect.y;
        _onTheFloor = false;
    }
    else {
        _onTheFloor = true;
        if (_verticalDirection == JUMPING) {
            _verticalDirection = VERTICAL_STATIC;
        }
    }

    //Actualizar rect
    rect.x = pos.getX();
    rect.y = pos.getY();

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


bool Player::Hit(SDL_Rect* rectDeAtaque, bool fromPlayer)
{
	if (_superMario) _superMario = false;
	else _lives--; // ha muerto
    return false; 
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

void Player::HandleAnims()
{
    switch (_animationState)
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
}