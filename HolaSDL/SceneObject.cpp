#include <iostream>
#include <string>

#include "checkML.h"
#include "SDL.h"
#include "SceneObject.h"
#include "GameObject.h"



SceneObject::SceneObject(Game* game, Texture* texture, Point2D<int> position, Vector2D<int> velocity, bool isStatic)
	: GameObject(game), texture(texture), velocity(velocity), isStatic(isStatic), pos(position)
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

    SDL_Rect newRect = getWorldRect();

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
    else { 
        pos.setY((game->checkCollision(newRect, false).colliderPosition.getY()) - newRect.h);
        colliding = true; 
        
       }

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

void SceneObject::renderPositions() const {
    SDL_Color yellow = { 255, 255, 0, 255 };
    SDL_Color blue = { 0, 0, 255, 255 };

    // Generar las texturas de los textos
    SDL_Texture* screenText = game->getFontTexture(
        "Screen Pos: " + std::to_string(getScreenPos().getX()) + ", " + std::to_string(getScreenPos().getY()),
        yellow, game->getRenderer());

    SDL_Texture* worldText = game->getFontTexture(
        "World Pos: " + std::to_string(getWorldPos().getX()) + ", " + std::to_string(getWorldPos().getY()),
        blue, game->getRenderer());

    Vector2D screenPos = getScreenPos();
    // Renderizar las texturas (asumiendo un tamaño de texto fijo)
    if (screenText) {
        SDL_Rect destRect = { screenPos.getX(), screenPos.getY() - 30, 150, 30}; // Posición y tamaño de renderizado
        SDL_RenderCopy(game->getRenderer(), screenText, nullptr, &destRect);
        SDL_DestroyTexture(screenText); // Liberar textura
    }

    if (worldText) {
        SDL_Rect destRect = { screenPos.getX(), screenPos.getY() - 50, 150, 30 }; // Posición y tamaño de renderizado
        SDL_RenderCopy(game->getRenderer(), worldText, nullptr, &destRect);
        SDL_DestroyTexture(worldText); // Liberar textura
    }
}

const Point2D<int> SceneObject::getWorldPos() const
{
	return pos;
}

const Point2D<int> SceneObject::getScreenPos() const
{
    Vector2D screenPos(pos.getX() - game->getMapOffset(), pos.getY());
    return screenPos;
}

const SDL_Rect SceneObject::getScreenRect() const
{
    SDL_Rect newRect;
    newRect.x = pos.getX() - game->getMapOffset();
    newRect.y = pos.getY();
    newRect.w = texture->getFrameWidth() * scale;
    newRect.h = texture->getFrameHeight() * scale;
    return newRect;
}

const SDL_Rect SceneObject::getWorldRect() const
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
