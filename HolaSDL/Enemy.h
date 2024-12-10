#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include "SceneObject.h"

class Enemy : public SceneObject {
public:
    Enemy(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity = { 0, 0 }, bool isStatic = true);
    virtual ~Enemy() = default;

    // Metodo comun a todos los enemigos
    virtual Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;
};

#endif

