#include "Block.h"
#include <iostream>

Block::Block(Game* game, BlockType type, Point2D<int> position, Texture* tex, BlockContent content)
	: SceneObject(game, tex, position, { 0,0 }), _type(type), _content(content)
{
	_framecount = 0;
	setScale(2);

	if (type == SORPRESA) _renderFrame = 0;
	else _renderFrame = 5;
}

Block::Block(const Block& other)
	: SceneObject(other.game, other.texture, other.pos, other.velocity),
	_type(other._type), _content(other._content), _framecount(other._framecount), _renderFrame(other._renderFrame)
{
	setScale(other.scale);
}

void Block::Render() const
{
	texture->renderFrame(getScreenRect(), 0, _renderFrame);
}

void Block::Update()
{
	manageAnims();
}

void Block::manageAnims()
{
	if (_type == SORPRESA)
	{
		if (_framecount >= ANIMATION_SPEED)
		{
			if (_renderFrame >= 3) _renderFrame = 0;
			else _renderFrame++;
			_framecount = 0;
		}
	}
	_framecount++;
}

Collision Block::Hit(const SDL_Rect& region, Collision::Target target)
{
	SDL_Rect intersection;
	SDL_Rect worldRect = getWorldRect();
	bool hasIntersection = SDL_IntersectRect(&worldRect, &region, &intersection);
	if (hasIntersection) {
		Collision::Side side = GetCollisionSide(region, worldRect);

		Collision collision{ Collision::Result::OBSTACLE, side, intersection.w, intersection.h };

		if (side == Collision::BOTTOM && _type == SORPRESA) {
			_type = VACIO;
			_renderFrame = 4;
			// spawnea el power up
		}

		return collision;
	}
		
	return NO_COLLISION;
}

SceneObject* Block::Clone() const
{
	return new Block(*this);
}
