#include "Pickable.h"

//Pickable::hit(const SDL_Rect& region, Collision::Target target)
//{
//    SDL_Rect ownRect = getCollisionRect();
//
//    if (target == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &region)) {
//        triggerAction();  // Se activa una acción (por ejemplo, recoger el objeto)
//        delete this;      // El objeto se elimina después de recogerlo
//    }
//
//    return NO_COLLISION;  // Devuelve una colisión vacía si no hay intersección
//}