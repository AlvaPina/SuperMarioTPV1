#pragma once

#include "Vector2D.h"
#include "Texture.h"
#include "SceneObject.h"
#include "Game.h"

class Goomba : public SceneObject
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
	bool Hit(SDL_Rect* rectDeAtaque, bool fromPlayer) override;

	Goomba(Texture* text, Vector2D<int> pos, Game* gam);
	~Goomba();
};


