#include "GameState.h"

GameState::~GameState() {
    for (auto handler : eventHandlers) {
        delete handler;
    }

    for (auto gameObject : gameObjects) {
        delete gameObject;
    }
}
void GameState::addEventListener(EventHandler* handler) {
	eventHandlers.push_back(handler);
}
void GameState::addObject(GameObject* gameObject) {
	gameObjects.push_back(gameObject);
}
