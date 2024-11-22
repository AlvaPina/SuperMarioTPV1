#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include "Game.h"
//#include "gameList.h"

class Game;

class GameObject
{
protected:
    Game* game;
public:
    GameObject(Game* game);
    virtual ~GameObject();

    // metodos virtuales
    virtual void Render() const = 0;
    virtual void Update() = 0;
};
#endif

