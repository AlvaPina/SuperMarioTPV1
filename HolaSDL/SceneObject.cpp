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

    gravity = game->GRAVITY;
    flippingVelocity = false;
    colliding = false;
}

SceneObject::~SceneObject() {
}

void SceneObject::move()
{
    if (isStatic) return; // No moverse si el objeto es estático

    // Aplicamos la gravedad
    if (!colliding) {
        velocity.y += gravity;
    }

    SDL_Rect newRect = rect;

    // Comprobar colisiones eje X
    newRect.x += velocity.getX();

    if (!game->checkCollision(newRect, false).collides) {
        // Si no hay colisión, aplicar movimiento en el ejeX
        rect.x += velocity.getX();
        pos.x += velocity.getX();
    }

    // Comprobar colisiones eje Y
    newRect.y += velocity.getY();

    if (!game->checkCollision(newRect, false).collides) {
        // Si no hay colisión, aplicar movimiento en el ejeY
        rect.y += velocity.getY();
        pos.y += velocity.getY();
        colliding = false;
    }
    else colliding = true;

    if (flippingVelocity) manageFlip();
}

void SceneObject::manageFlip()
{
    if (velocity.getX() < 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (velocity.getX() > 0) {
        flip = SDL_FLIP_NONE;
    }
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

void SceneObject::setGravity(int value)
{
    gravity = value;
}