#include "Enemy.h"

Enemy::Enemy(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity, bool isStatic)
    : SceneObject(game, texture, pos, velocity, false) {}

Collision Enemy::Hit(const SDL_Rect& region, Collision::Target target) {
	SDL_Rect intersection;
	SDL_Rect worldRect = getWorldRect();

	// Comparar si son el mismo rect, es decir, es el propio goomba
	if (worldRect.x == region.x - velocity.getX() &&
		worldRect.y == region.y - velocity.getY() &&
		worldRect.w == region.w &&
		worldRect.h == region.h) {
		return NO_COLLISION;
	}

	bool hasIntersection = SDL_IntersectRect(&worldRect, &region, &intersection);
	if (hasIntersection) {
		Collision::Side side = GetCollisionSide(region, worldRect);

		Collision collision{ Collision::Result::OBSTACLE, side, intersection.w, intersection.h };
		if (target == Collision::ENEMIES) { //Es el player
			if (side != Collision::TOP) {
				collision = { Collision::Result::DAMAGE, side, intersection.w, intersection.h };
			}
		}
		return collision;
	}
}