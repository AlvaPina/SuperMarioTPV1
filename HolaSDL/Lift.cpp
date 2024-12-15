#include "Lift.h"

Lift::Lift(Game* game, Texture* text, Vector2D<int> pos)
	: SceneObject(game, texture, pos, { 0,0 }), _minPos(pos.getY())
{

}

Lift::~Lift()
{
}

void Lift::Render() const
{
	texture->renderFrame(getScreenRect(), 0, 0);
}

void Lift::Update()
{
	if (pos.getY() <= _minPos) {
		velocity.setY(-_SPEED);
	}
	else if (pos.getY() >= _minPos + _MOVING_LENGHT) {
		velocity.setY(_SPEED);
	}
}

Collision Lift::Hit(const SDL_Rect& rectDeAtaque, Collision::Target target)
{
	return Collision();
}
