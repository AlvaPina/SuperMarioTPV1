#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"

class Player
{
private:
	Texture* _texture;	// Puntero a la textura de Mario
	Vector2D<int> _position;	// Posicion actual de Mario
	Game* _game;				// Puntero al juego
	SDL_Rect _rect;			// Rectangulo de Mario
	int _lives;				// Numero de vidas de Mario
	bool _movingRight;		// Direccion de Mario
	bool _superMario;		// Forma de Mario
	bool _onTheFloor;
	

public:
	void render();
	void update();
	void hit();
	void handleEvent();

	Player(Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, bool supMar);
	~Player();
};

