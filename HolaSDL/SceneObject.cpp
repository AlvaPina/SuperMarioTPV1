#include <iostream>
#include <string>

#include "checkML.h"
#include "SDL.h"
#include "SceneObject.h"
#include "GameObject.h"



SceneObject::SceneObject(Game* game, Texture* texture, Point2D<int> position, Vector2D<int> velocity, bool isStatic)
	: GameObject(game), texture(texture), velocity(velocity), pos(position)
{
    gravity = game->GRAVITY;
    flippingVelocity = false;
    collidingYAxis = false;
    scale = 1;
    pos += {0, -texture->getFrameHeight() - 10}; // Para que spawneen arriba y no se metan en el suelo al aparecer
}

SceneObject::~SceneObject() {
}

Collision
SceneObject::tryToMove(const Vector2D<int>& velocity, Collision::Target target)
{
    Collision collision;
    SDL_Rect rect = getWorldRect();

    // Intenta moverse en vertical
    if (velocity.getY() != 0) {
        rect.y += velocity.getY();

        collision = game->checkCollision(rect, target);

        // Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
        int fix = collision.vertical * (velocity.getY() > 0 ? 1 : -1);
        pos += {0, velocity.getY() - fix};

        // Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

        rect.y -= fix; // recoloca la caja para la siguiente colisión
    }

    collision.horizontal = 0; // la horizontal del choque vertical da igual

    // Intenta moverse en horizontal
    // (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (velocity.getX() != 0) {
        rect.x += velocity.getX();

        Collision partial = game->checkCollision(rect, target);

        // Copia la información de esta colisión a la que se devolverá
        collision.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            collision.result = Collision::DAMAGE;

        // Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
        int fix = collision.horizontal * (velocity.getX() > 0 ? 1 : -1);
        pos += {velocity.getX() - fix, 0};
    }

    return collision;
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

void SceneObject::setTexture(Texture* newTexture)
{
    texture = newTexture;
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

Collision::Side SceneObject::GetCollisionSide(const SDL_Rect& region, const SDL_Rect& worldRect)
{
    int deltaTop = region.y + region.h - worldRect.y;
    int deltaBottom = worldRect.y + worldRect.h - region.y;
    int deltaLeft = region.x + region.w - worldRect.x;
    int deltaRight = worldRect.x + worldRect.w - region.x;

    // Determinar el lado con la menor penetración
    int minDelta = std::min({ deltaTop, deltaBottom, deltaLeft, deltaRight });

    if (minDelta == deltaTop) {
        return Collision::TOP;
    }
    else if (minDelta == deltaBottom) {
        return Collision::BOTTOM;
    }
    else if (minDelta == deltaLeft) {
        return Collision::LEFT;
    }
    else if (minDelta == deltaRight) {
        return Collision::RIGHT;
    }

    return Collision::DONTCARE; // No colisión o colisión no relevante
}

void SceneObject::SetListAnchor(GameList<SceneObject>::anchor&& anchor) {
    this->anchorScene = std::move(anchor);
}
