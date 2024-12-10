#pragma once
#include "Pickable.h"

class Mushroom : public Pickable {
private:
	Game* game;
	Texture* texture;
	Vector2D position;

public:
	Mushroom(Game* game, Texture* texture, Vector2D<int> pos);

	virtual void triggerAction() override;
};

