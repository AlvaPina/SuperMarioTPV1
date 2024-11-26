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
		move();
	}
}

bool Goomba::Hit(SDL_Rect* rectDeAtaque, bool fromPlayer)
{
	//Comprobar si es el player
	return false;
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
