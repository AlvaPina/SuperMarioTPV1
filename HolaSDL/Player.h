#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"

class Player
{
private:
	SDL_Texture* texture;	// Puntero a la textura de Mario
	Vector2D<int> position;	// Posicion actual de Mario
	Game* game;				// Puntero al juego
	int lives;				// Numero de vidas de Mario
	bool movingRight;		// Direccion de Mario
	bool SuperMario;		// Forma de Mario
	bool onTheFloor;

public:
	void render();
	void update();
	void hit();
	void handleEvent();

	Player(SDL_Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, bool supMar);
	~Player();
};

