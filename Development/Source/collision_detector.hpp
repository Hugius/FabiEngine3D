#pragma once

#include "Collision.hpp"
#include "aabb_entity.hpp"

class CollisionDetector
{
public:
	CollisionDetector() = default;
	virtual ~CollisionDetector() = default;
	
	Collision check(const AabbEntity& box, vec3 point, vec3 pointDifference, CollisionDirection& collisionDir);

private:

};