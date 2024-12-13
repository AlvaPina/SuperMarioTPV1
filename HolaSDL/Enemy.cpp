#include "Enemy.h"

Enemy::Enemy(Game* game, Texture* texture, Point2D<int> pos, Vector2D<int> velocity, bool isStatic)
    : SceneObject(game, texture, pos, velocity, false) {}

Collision Enemy::Hit(const SDL_Rect& region, Collision::Target target) {
	SDL_Rect intersection;
	SDL_Rect worldRect = getWorldRect();

	bool hasIntersection = SDL_IntersectRect(&worldRect, &region, &intersection);
	if (hasIntersection) {
		Collision::Side side = GetCollisionSide(region, worldRect);

		if (target == Collision::ENEMIES) { //Es el player
			if (side != Collision::TOP) {
				Collision collision = { Collision::Result::DAMAGE, side, intersection.w, intersection.h };
				return collision;
			}
		}
	}
	return NO_COLLISION;
}