#pragma once

#include "Collision.hpp"
#include "aabb_entity.hpp"

class CollisionDetector
{
public:
	CollisionDetector() = default;
	virtual ~CollisionDetector() = default;
	
	Collision check(const AabbEntity& box, Vec3 point, Vec3 pointDifference, Direction& collisionDir);
};