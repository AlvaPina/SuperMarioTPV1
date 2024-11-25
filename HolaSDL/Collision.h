#pragma once
#include "Vector2D.h"

struct Collision {
	bool collides;						// Indica si hay colision
	bool damages;						// Indica si la colision provoca daño
	Vector2D<int> colliderPosition;		// Indica la posicion objeto colisionado

	operator bool() const { return collides; }
};