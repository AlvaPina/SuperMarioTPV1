#pragma once
#include "Vector2D.h"
#include "Texture.h"
#include "SDL.h"
#include "Game.h"

class Player
{
private:
	const int PLAYERSPEED = 5;
	const int VERTICAL_MAX_SPEED = 25;
	float _verticalSpeed = 0;

	Texture* _texture;	// Puntero a la textura de Mario
	Vector2D<int> _position;	// Posicion actual de Mario
	Game* _game;				// Puntero al juego
	SDL_Rect _rect;			// Rectangulo de Mario
	int _lives;				// Numero de vidas de Mario
	bool _superMario;		// Forma de Mario
	bool _onTheFloor;
	int playerSpeed;
	
	enum DIRECCION_HORIZONTAL {
		RIGHT,
		LEFT,
		HORIZONTAL_STATIC
	};

	enum DIRECCION_VERTICAL {
		JUMPING,
		FALLING,
		VERTICAL_STATIC
	};

	DIRECCION_HORIZONTAL _horizontalDirection = HORIZONTAL_STATIC;
	DIRECCION_VERTICAL _verticalDirection = FALLING;
public:
	void render();
	void update();
	void hit();
	void handleEvent(const SDL_Event& evento);
	// Getters
	int getX();
	int getY();

	Player(Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, bool supMar);
	~Player();
};

