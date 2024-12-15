#include "Goomba.h"

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Goomba::Goomba(Texture* texture, Vector2D<int> position, Game* game)
	: Enemy(game, texture, position, { 0,0 })
{
	_renderFrame = 0;
	_frameCount = 0;
	setScale(2);
	velocity = { -GOOMBA_SPEED, 0 };
}

Goomba::Goomba(const Goomba& other)
	: Enemy(other.game, other.texture, other.pos, other.velocity)
{
	_renderFrame = other._renderFrame;
	_frameCount = other._frameCount;
	setScale(other.scale);
}

Goomba::~Goomba()
{
}

void Goomba::Render() const {
	texture->renderFrame(getScreenRect(), 0, _renderFrame);
}

void Goomba::Update() {

	HandleAnims();

	if(isInScreen())
	{
		// Acelra la velocidad con la gravedad
		if (velocity.getY() < Game::SPEED_LIMIT)
			velocity += {0, Game::GRAVITY};

		Collision collision = tryToMove(velocity, Collision::PLAYER);

		if (collision.result == Collision::DAMAGE) {
			game->addPoints(50);
			delete this;
		}

		// Si toca un objeto en horizontal cambia de dirección
		if (collision.horizontal)
			velocity.setX(-velocity.getX());

		// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
		if (collision.vertical)
			velocity.setY(0);

		if (collision.result == Collision::Result::DAMAGE) {
			//delete this;
			return;
		}
		if (flippingVelocity) manageFlip();
	}
}

Collision Goomba::Hit(const SDL_Rect& region, Collision::Target target)
{
	if (isInScreen()) {
		return Enemy::Hit(region, target);
	}
	return NO_COLLISION;

}

SceneObject* Goomba::Clone() const
{
	return new Goomba(*this);
}

bool Goomba::isInScreen()
{
	if (pos.getX() - game->getMapOffset() <= game->WIN_WIDTH) return true;
	else return false;
}

void Goomba::HandleAnims()
{
	if (_frameCount >= FRAME_SPEED)
	{
		if (_renderFrame == 0) _renderFrame = 1;
		else _renderFrame = 0;

		_frameCount = 0;
	}
	else _frameCount++;
}
