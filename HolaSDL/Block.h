#pragma once
#include "checkML.h"

#include "Vector2D.h"
#include "Game.h"
#include "SceneObject.h"

class Block : public SceneObject
{
public:
enum BlockType {
	SORPRESA,
	VACIO,
	LADRILLO
};
enum BlockContent {
	EMPTY,
	POWER_UP,
	COIN
};

	Block(Game* game, BlockType type, Point2D<int> pos, Texture* texture, BlockContent content);
	void Render() const override;
	void Update() override;
	Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;

private:
	const int ANIMATION_SPEED = 10;

	BlockType _type;
	BlockContent _content;
	int renderFrame;		// Indica que frame se usa en el renderizado
	int _framecont;			// Contador auxiliar para las animaciones

	void manageAnims();
};

