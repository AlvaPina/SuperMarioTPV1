#include "checkML.h"
#include <iostream>
#include "SDL.h"
#include "SceneObject.h"
#include "GameObject.h"



SceneObject::SceneObject(Game* game, Point2D<int> pos, Vector2D<int> velocity, bool isStatic, int scale)
	: GameObject(game), velocity(velocity), isStatic(isStatic), scale(scale)
{
	rect.w = 50;
	rect.h = 50;
	rect.x = pos.getX();
	rect.y = pos.getY();
}

SceneObject::~SceneObject() {
}

const SDL_Rect& SceneObject::getRect() const
{
	return rect;
}

const Point2D<int> SceneObject::getPos() const
{
	return pos;
}

void SceneObject::setPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;
}

void SceneObject::setVelocity(int vx, int vy)
{
	velocity.x = vx;
	velocity.y = vy;
}

void SceneObject::setStatic(bool isStatic)
{
	isStatic = isStatic;
}