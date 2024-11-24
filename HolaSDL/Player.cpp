#include <iostream>

#include "Game.h"
#include "Player.h"
#include "SDL.h"
#include "Texture.h"
#include "Vector2D.h"


Player::Player(Texture* texture, Vector2D<int> position, Game* game, int lives, bool movingRight, MarioState marioState)
    : SceneObject(game, texture, position, { 0,0 }, false), _lives(lives), _marioState(marioState), _texture(texture)
{
    _playerFrame = 0;
    flippingVelocity = true;
    flip = SDL_FLIP_NONE;
    setScale(3);
}

Player::~Player()
{
}

void Player::Render() const
{
    if (_texture) {
        _texture->renderFrame(getRect(), 0, _playerFrame, flip);
    }
}

void Player::Update()
{
    HandleAnims();

    // Para que el jugador no se salga por la izquierda de la pantalla
    if (pos.getX() < 1 && velocity.getX() < 0) {
        velocity.setX(0);
    }

    // Si el jugador ha alcanzado la mitad de la pantalla
    if (pos.getX() >= game->WIN_WIDTH / 2 && velocity.getX() > 0) {
        // Desplazar el mapa sin mover horizontalmente al jugador
        game->addMapOffset(velocity.getX());
        velocity.setX(0);
        move();
        velocity.setX(PLAYERSPEED);
    }
    else { // Movimiento normal
        move();
    }
}

bool Player::Hit(SDL_Rect* rectDeAtaque, bool fromPlayer)
{
	if (_marioState != BASE_MARIO) _marioState = BASE_MARIO;
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
            velocity.setX(PLAYERSPEED);
            _animationState = MOVING_R;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            velocity.setX(-PLAYERSPEED);
            _animationState = MOVING_L;
            break;
        case SDLK_SPACE:
            if (colliding) {
                velocity.setY(-JUMP_POWER);
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
            velocity.setX(0);
            break;
        default:
            break;
        }
    }
}

void Player::HandleAnims()
{
    if (velocity.getX() == 0) {
        _animationState = STOPPED;
    }

    if (!colliding) _animationState = AN_JUMPING;

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