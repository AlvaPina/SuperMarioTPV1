#include "GameObject.h"
#include "Game.h"

GameObject::GameObject(Game* game) : game(game) {

}
GameObject::~GameObject() {

}
void GameObject::SetListAnchor(GameList<GameObject>::anchor&& anchor) {
    this->anchorObject = std::move(anchor);
}

