#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(GameState* gameState) : gameState(gameState) {

}

GameObject::~GameObject() {

}

void GameObject::SetListAnchor(GameList<GameObject>::anchor&& anchor) {
    this->anchorObject = std::move(anchor);
}

