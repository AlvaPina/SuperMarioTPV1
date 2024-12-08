#include <iostream>

#include "Game.h"
#include "Player.h"
#include "Texture.h"
#include "Vector2D.h"


Player::Player(Texture* texture, Vector2D<int> position, Game* game, int lives, bool movingRight, MarioState marioState)
    : SceneObject(game, texture, position, { 0,0 }, false), _lives(lives), _marioState(marioState), _canJump(false)
{
    _playerFrame = 0;
    flippingVelocity = true;
    flip = SDL_FLIP_NONE;
    setScale(3);
    _playerAnims.runAnim.firstFrame = 1;
    _playerAnims.runAnim.lastFrame = 2;
    _playerAnims.jumpFrame = 5;
}

Player::~Player()
{
}

void Player::Render() const
{
    if (texture) {
        texture->renderFrame(getScreenRect(), 0, _playerFrame, flip);
    }
    renderPositions();
}

void Player::Update()
{
    HandleAnims();

    if (isStatic) return; // No moverse si el objeto es estático

    // Acelra la velocidad con la gravedad
    if (velocity.getY() < Game::SPEED_LIMIT)
        velocity += {0, Game::GRAVITY};

    Vector2D screenPos = getScreenPos();
    // Para que el jugador no se salga por la izquierda de la pantalla
    if (screenPos.getX() < PLAYERSPEED && velocity.getX() < 0) {
        velocity.setX(0);
    }
    // Si el jugador ha alcanzado la mitad de la pantalla
    else if (screenPos.getX() >= game->WIN_WIDTH / 2 && velocity.getX() > 0) {
        // Desplazar el mapa
        game->addMapOffset(velocity.getX());
    }
    Collision collision = tryToMove(velocity, Collision::ENEMIES); 

    if (collision.vertical > 0) _canJump = true; // Si la colision se hunde en el suelo, le dejamos saltar
    else _canJump = false;

    if (flippingVelocity) manageFlip();
}

Collision Player::Hit(const SDL_Rect& region, Collision::Target target)
{
    if (target == Collision::PLAYER) {
        // Calcula la intersección
        SDL_Rect intersection;
        SDL_Rect ownRect = getWorldRect();
        bool hasIntersection = SDL_IntersectRect(&ownRect, &region, &intersection);

        if (hasIntersection) {
            Collision collision{ Collision::OBSTACLE, intersection.w, intersection.h };
            std::cout << "¡Jugador colisiona! Profundidad: " << intersection.w << ", " << intersection.h << std::endl;

            // Manejo necesario

            return collision;
        }
    }
    return NO_COLLISION;
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
            if (_canJump) {
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
        case SDLK_f:
            std::cout << "CAMBIO ESTADO A SUPER MARIO!";
            ChangeMarioState(MarioState::SUPER_MARIO);
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
        if (_playerFrame == _playerAnims.runAnim.firstFrame) _playerFrame = _playerAnims.runAnim.lastFrame;
        else _playerFrame = _playerAnims.runAnim.firstFrame;
        break;
    case AN_JUMPING:
        _playerFrame = _playerAnims.jumpFrame;
        break;
    }
}

void Player::ChangeMarioState(MarioState newState)
{
    if (_marioState != newState) { // comprobamos que sea un estado diferente al actual
        _playerFrame = 0; // reseteamos renderFrame
        delete(texture);

        switch (newState)
        {
        case BASE_MARIO:
            setScale(3);
            texture = game->getTexture(Game::MARIO);
            _playerAnims.runAnim.firstFrame = 1;
            _playerAnims.runAnim.lastFrame = 2;
            _playerAnims.jumpFrame = 5;
            break;
        case SUPER_MARIO:
            setScale(2);
            texture = game->getTexture(Game::SUPERMARIO);
            _playerAnims.runAnim.firstFrame = 2;
            _playerAnims.runAnim.lastFrame = 3;
            _playerAnims.jumpFrame = 6;
            break;
        case MARIO_FIRE:
            texture = game->getTexture(Game::FIREMARIO);
            break;
        }
    }
}
