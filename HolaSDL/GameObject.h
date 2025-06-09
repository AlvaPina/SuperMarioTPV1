#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include "Game.h"
#include "gameList.h"

class Game;

class GameObject
{
protected:
    GameState* gameState;
    GameList<GameObject>::anchor anchorObject;

public:
    GameObject(GameState* game);
    virtual ~GameObject();
    void SetListAnchor(GameList<GameObject>::anchor&& anchor);

    // metodos virtuales
    virtual void Render() const = 0;
    virtual void Update() = 0;
};
#endif

