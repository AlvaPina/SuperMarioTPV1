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
	Block(const Block& other); // Constructor por copia

	void Render() const override;
	void Update() override;
	Collision Hit(const SDL_Rect& rectDeAtaque, Collision::Target target) override;
	SceneObject* Clone() const override;

private:
	const int ANIMATION_SPEED = 10;

	BlockType _type;
	BlockContent _content;
	int _renderFrame;		// Indica que frame se usa en el renderizado
	int _framecount;			// Contador auxiliar para las animaciones

	void manageAnims();
};

