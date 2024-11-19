#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"

class Goomba
{
private:
	const int GOOMBA_SPEED = 2;

	Texture* _texture;			// Puntero a la textura
	Vector2D<int> _pos;	// Posicion actual
	Game* _game;				// Puntero al juego
	SDL_Rect _rect;
	bool _movingLeft;			// Indica direccion de movimiento
	int _renderFrame;			// Indica que frame se usa en el renderizado

	bool isInScreen();

public:
	void render();
	void update();
	Goomba(Texture* text, Vector2D<int> pos, Game* gam);
};


