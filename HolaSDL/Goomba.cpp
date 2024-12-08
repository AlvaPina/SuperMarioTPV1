#include "Goomba.h"

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"


Goomba::Goomba(Texture* texture, Vector2D<int> position, Game* game)
	: SceneObject(game, texture, position, { 0,0 }, false)
{
	_renderFrame = 0;
	_frameCont = 0;
	setScale(2);
	velocity = { -GOOMBA_SPEED, 0 };
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

		tryToMove(velocity, Collision::PLAYER);

		if (flippingVelocity) manageFlip();
	}
}

Collision Goomba::Hit(const SDL_Rect& rectDeAtaque, Collision::Target target)
{
	Collision collisionResult;

	//Comprobar si es el player
	return collisionResult;
}

bool Goomba::isInScreen()
{
	if (pos.getX() - game->getMapOffset() <= game->WIN_WIDTH) return true;
	else return false;
}

void Goomba::HandleAnims()
{
	if (_frameCont >= FRAME_SPEED)
	{
		if (_renderFrame == 0) _renderFrame = 1;
		else _renderFrame = 0;

		_frameCont = 0;
	}
	else _frameCont++;
}
