#include "checkML.h"
#include <iostream>
#include "SDL.h"
#include "SceneObject.h"
#include "GameObject.h"



SceneObject::SceneObject(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity, bool isStatic)
	: GameObject(game), texture(texture), velocity(velocity), isStatic(isStatic)
{
    gravity = game->GRAVITY;
    flippingVelocity = false;
    colliding = false;
    scale = 1;
}

SceneObject::~SceneObject() {
}

void SceneObject::move()
{
    if (isStatic) return; // No moverse si el objeto es estático

    // Aplicamos la gravedad
    if (!colliding) {
        velocity.addY(gravity);
    }

    SDL_Rect newRect = getRect();

    // Comprobar colisiones eje X
    newRect.x += velocity.getX();

    if (!game->checkCollision(newRect, false).collides) {
        // Si no hay colisión, aplicar movimiento en el ejeX
        pos.addX(velocity.getX());
    }

    // Comprobar colisiones eje Y
    newRect.y += velocity.getY();

    if (!game->checkCollision(newRect, false).collides) {
        // Si no hay colisión, aplicar movimiento en el ejeY
        pos.addY(velocity.getY());
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

const Point2D<int> SceneObject::getPos() const
{
	return pos;
}

const SDL_Rect SceneObject::getRect() const
{
    SDL_Rect newRect;
    newRect.x = pos.getX();
    newRect.y = pos.getY();
    newRect.w = texture->getFrameWidth() * scale;
    newRect.h = texture->getFrameHeight() * scale;
    return newRect;
}

void SceneObject::setPosition(int x, int y)
{
    pos.setX(x);
    pos.setY(y);
}

void SceneObject::setVelocity(int vx, int vy)
{
	velocity.setX(vx);
	velocity.setY(vy);
}

void SceneObject::setStatic(bool isStatic)
{
	isStatic = isStatic;
}

void SceneObject::setGravity(int value)
{
    gravity = value;
}

void SceneObject::setScale(int value)
{
    scale = value;
}
