#include "Pickable.h"

Pickable::Pickable(Game* game, Texture* texture, Vector2D<int> pos)
    : SceneObject(game, texture, pos, { 0,0 }, false) {}

Collision Pickable::Hit(const SDL_Rect& region, Collision::Target target)
{
    SDL_Rect ownRect = getWorldRect();

    if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
        triggerAction();  // Se activa una acci�n (por ejemplo, recoger el objeto)
        delete this;      // El objeto se elimina despu�s de recogerlo
    }

    return NO_COLLISION;  // Devuelve una colisi�n vac�a si no hay intersecci�n
}