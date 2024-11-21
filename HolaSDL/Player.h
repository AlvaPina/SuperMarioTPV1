#pragma once
#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"

class Player : public SceneObject
{
private:
	const int PLAYERSPEED = 10;
	const int VERTICAL_MAX_SPEED = 25;
	const int JUMP_POWER = 12;

	float _verticalSpeed = 0;
	Texture* _texture;				// Puntero a la textura de Mario
	int _lives;						// Numero de vidas de Mario
	bool _superMario;				// Forma de Mario
	bool _onTheFloor;				// Indica si Mario está en el suelo
	int playerSpeed;				// Velocidad del personaje
	int _playerFrame;				// Indica el frame que se renderiza
	SDL_RendererFlip _playerFlip;	// Indica en que direccion se rota el sprite

	
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

	enum ANIMATION_STATE {
		STOPPED,
		MOVING_R,
		MOVING_L,
		AN_JUMPING,
	};

	DIRECCION_HORIZONTAL _horizontalDirection = HORIZONTAL_STATIC;
	DIRECCION_VERTICAL _verticalDirection = FALLING;
	ANIMATION_STATE _animationState = STOPPED;
public:
	void Render() const override;
	void Update() override;
	bool Hit(SDL_Rect* rectDeAtaque, bool fromPlayer) override;
	void handleEvent(const SDL_Event& evento);
	void HandleAnims();

	Player(Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, bool supMar);
	~Player();
};

