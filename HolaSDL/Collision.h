#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "SDL.h"

struct Collision
{
	// ¿A quién afecta esta colisión? Se puede usar en lugar del
	// bool fromPlayer para objetos que atacan tanto a enemigos
	// como al jugador (caparaszón opciona).
	enum Target {
		ENEMIES = 1,	// afecta a enemigos
		PLAYER = 2,	// afecta al jugador
		BOTH = 3,	// afecta a ambos
	};

	// Tipo de resultado de la colisión
	enum Result {
		NONE,		// no ha habido colisión
		DAMAGE,		// la colisión produce daño
		OBSTACLE,	// la colisión impide el movimiento
	};

	// Lado por el que colisiona
	enum Side {
		DONTCARE,
		TOP,
		BOTTOM,
		LEFT,
		RIGHT
	};

	Result result = Result::NONE;
	Side side = Side::DONTCARE;
	int horizontal = 0;   // profundidad de la colisión horizontal
	int vertical = 0;     // profundidad de la colisión vertical
};
const Collision NO_COLLISION = Collision{ Collision::Result::NONE,Collision::Side::DONTCARE, 0, 0};
