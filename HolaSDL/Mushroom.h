#pragma once
#include "Pickable.h"

class Mushroom : public Pickable {
private:

public:
	Mushroom(Game* game, Texture* texture, Vector2D<int> pos);

	virtual void triggerAction() override;
};

