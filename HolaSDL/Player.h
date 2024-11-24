#pragma once
#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"

class Player : public SceneObject
{
public:
	enum MarioState {
		BASE_MARIO,
		SUPER_MARIO,
		MARIO_FIRE

	};

	void Render() const override;
	void Update() override;
	bool Hit(SDL_Rect* rectDeAtaque, bool fromPlayer) override;
	void handleEvent(const SDL_Event& evento);
	void HandleAnims();

	Player(Texture* text, Vector2D<int> pos, Game* gam, int livs, bool movR, MarioState marioState);
	~Player();

private:
	const int PLAYERSPEED = 10;
	const int JUMP_POWER = 25;

	Texture* _texture;				// Puntero a la textura de Mario
	int _lives;						// Numero de vidas de Mario
	int _playerFrame;				// Indica el frame que se renderiza

	enum AnimationState {
		STOPPED,
		MOVING_R,
		MOVING_L,
		AN_JUMPING,
	};

	AnimationState _animationState = STOPPED;
	MarioState _marioState = BASE_MARIO;

};

