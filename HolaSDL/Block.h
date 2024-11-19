#pragma once

#include "Vector2D.h"
#include "Game.h"

class Block
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
void render();
void update();
void hit(SDL_Rect* rectMario);

private:
	const int ANIMATION_SPEED = 10;

	Point2D<int> _pos;
	Texture* _texture;
	SDL_Rect _rect;
	BlockType _type;
	Game* _game;
	BlockContent _content;
	int renderFrame;		// Indica que frame se usa en el renderizado
	int _framecont;			// Contador auxiliar para las animaciones

};

