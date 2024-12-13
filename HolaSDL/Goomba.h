#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Texture.h"
#include "Enemy.h"
#include "Game.h"

class Goomba : public Enemy
{
private:
	const int GOOMBA_SPEED = 2;
	const int FRAME_SPEED = 5;

	int _renderFrame;			// Indica que frame se usa en el renderizado
	int _frameCont;

	bool isInScreen();
	void HandleAnims();

public:
	void Render() const override;
	void Update() override;
	Collision Hit(const SDL_Rect& region, Collision::Target target) override;

	Goomba(Texture* text, Vector2D<int> pos, Game* game);
	~Goomba();
};


