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

	struct Anim {
		int firstFrame;
		int lastFrame;
	};

	struct PlayerAnims {
		Anim runAnim;
		int jumpFrame;
	};

	Player(Texture* text, Vector2D<int> pos, Game* game, int livs, bool movR, MarioState marioState);
	~Player();

	void Render() const override;
	void Update() override;
	Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;
	void handleEvent(const SDL_Event& evento);
	void HandleAnims();
	void ChangeMarioState(MarioState newState);

	//Getters
	int GetVidas() const;
private:
	const int PLAYERSPEED = 10;
	const int JUMP_POWER = 25;

	int _lives;						// Numero de vidas de Mario
	int _playerFrame;				// Indica el frame que se renderiza
	bool _canJump;

	enum AnimationState {
		STOPPED,
		MOVING_R,
		MOVING_L,
		AN_JUMPING,
	};

	AnimationState _animationState = STOPPED;
	MarioState _marioState = BASE_MARIO;
	PlayerAnims _playerAnims;
};

