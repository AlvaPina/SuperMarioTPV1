#pragma once
#ifndef PICKABLE_H
#define PICKABLE_H
#include "checkML.h"

#include "SceneObject.h"

class Pickable : public SceneObject {
public:
    Pickable(Game* game, Texture* text, Vector2D<int> pos);
    virtual ~Pickable() = default;

    // Método para manejar la colisión con Mario
    virtual Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;

protected:
    virtual void triggerAction() = 0;
};

#endif


