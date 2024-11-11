#pragma once

#include "Vector2D.h"
#include "Game.h"

class Block
{
public:
enum BlockType {
	LADRILLO,
	SORPRESA,
	VACIO,
	OCULTO
};
enum Action {
	POTENCIADOR,
	MONEDA
};

Block(Game* game, BlockType type, Point2D<int> pos, Texture* texture);
void render();
void update();
void hit(SDL_Rect* rectMario);

private:
	Point2D<int> _pos;
	Texture* _texture;
	SDL_Rect _rectangulo;
	BlockType _type;
	Game* _game;

};

