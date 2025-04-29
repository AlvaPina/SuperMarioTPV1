#ifndef GAMESTATE_H
#define GAMESTATE_H

#include  "checkML.h"
#include <SDL.h>
#include <iostream>
#include "gameList.h"
#include "GameObject.h"
#include "EventHandler.h"

class Game;

using namespace std;

class GameState
{
public:
    GameState(Game* game) : game(game) {}
    virtual ~GameState();

    virtual void update() = 0;
    virtual void render() const = 0;
    virtual void handleEvent(const SDL_Event& event) = 0;

    void addEventListener(EventHandler* handler);
    void addObject(GameObject* gameObject);

    // Otros métodos y atributos comunes a todos los estados del juego

protected:
    // Lista de objetos del juego
    GameList<GameObject> gameObjects;
    // Lista de manejadores de eventos
    vector<EventHandler*> eventHandlers;
    Game* game;
};
#endif

