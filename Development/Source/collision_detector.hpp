#pragma once

#include "collision.hpp"
#include "mathematics.hpp"
#include "direction.hpp"

class CollisionDetector final
{
public:
	Collision check(Vec3 position, Vec3 size, Vec3 middlePosition,
		float bottom, float top, float left, float right, float front, float back,
		Vec3 middleChange, bool hasCollided);
};