#pragma once
#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"

class Player : public SceneObject
{
private:
	const int PLAYERSPEED = 10;
	const int JUMP_POWER = 24;

	Texture* _texture;				// Puntero a la textura de Mario
	int _lives;						// Numero de vidas de Mario
	bool _superMario;				// Forma de Mario
	int _playerFrame;				// Indica el frame que se renderiza

	enum ANIMATION_STATE {
		STOPPED,
		MOVING_R,
		MOVING_L,
		AN_JUMPING,
	};

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

