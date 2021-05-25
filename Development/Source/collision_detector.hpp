#pragma once

#include "collision.hpp"
#include "aabb_entity.hpp"

class CollisionDetector final
{
public:
	Collision check(const AabbEntity& box, Vec3 middle, float bottom, float top, float left, float right, float front, float back,
		Vec3 pointDifference, Direction& collisionDir);
};