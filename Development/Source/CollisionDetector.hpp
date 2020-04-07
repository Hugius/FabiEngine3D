#pragma once

#include "Collision.hpp"
#include "AabbEntity.hpp"

class CollisionDetector
{
public:
	CollisionDetector() = default;
	virtual ~CollisionDetector() = default;
	
	Collision check(const AabbEntity& box, vec3 point, vec3 pointDifference, CollisionDir& collisionDir);

private:

};