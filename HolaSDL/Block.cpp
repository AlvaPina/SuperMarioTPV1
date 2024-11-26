#include "Block.h"
#include <iostream>

Block::Block(Game* game, BlockType type, Point2D<int> position, Texture* tex, BlockContent content)
	: SceneObject(game, tex, position, { 0,0 }, false), _type(type), _content(content)
{
	_framecont = 0;
	setStatic(true);
	setScale(2);

	if (type == SORPRESA) renderFrame = 0;
	else renderFrame = 5;
}

void Block::Render() const
{
	texture->renderFrame(getScreenRect(), 0, renderFrame);
}

void Block::Update()
{
	manageAnims();
}

void Block::manageAnims()
{
	if (_type == SORPRESA)
	{
		if (_framecont >= ANIMATION_SPEED)
		{
			if (renderFrame >= 3) renderFrame = 0;
			else renderFrame++;
			_framecont = 0;
		}
	}
	_framecont++;
}

Collision Block::Hit(const SDL_Rect& rectDeAtaque, bool fromPlayer)
{
	Collision collisionResult{ false, false };

	SDL_Rect worldRect = getWorldRect();
	if (SDL_HasIntersection(&worldRect, &rectDeAtaque)) {
		std::cout << "BloqueColisionandoConMario";

		if (_type == SORPRESA) {
			_type = VACIO;
			renderFrame = 4;
			// spawnea el power up
		}
		collisionResult.collides = true;
		//collisionResult.colliderPosition
	}
	return collisionResult;
}
