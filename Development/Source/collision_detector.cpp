#include "collision_detector.hpp"

#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

Collision CollisionDetector::check(const AabbEntity& box, Vec3 middle, float bottom, float top, float left, float right, float front, float back, 
	Vec3 pointDifference, Direction& collisionDir)
{
	// Temporary values
	Collision collision(false, false, false);

	// Get AABB data
	auto pos  = box.getTranslation();
	auto size = box.getScaling() / 2.0f;
	bool insideBox = false;
	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	// X collision detection
	if (((middle.x + right) > (pos.x - size.x) && (middle.x + right) < (pos.x + size.x)) ||
		((middle.x - left) < (pos.x + size.x) && (middle.x - left) > (pos.x - size.x)))
	{
		xInsideBox = true;
	}

	// Y collision detection
	if (((middle.y + top) > (pos.y) && (middle.y + top) < (pos.y + (size.y * 2.0f))) ||
		((middle.y - bottom) < (pos.y + (size.y * 2.0f)) && (middle.y - bottom) > (pos.y)))
	{
		yInsideBox = true;

	}

	// Z collision detection
	if (((middle.z + front) > (pos.z - size.z) && (middle.z + front) < (pos.z + size.z)) ||
		((middle.z - back) < (pos.z + size.z) && (middle.z - back) > (pos.z - size.z)))
	{
		zInsideBox = true;
	}

	// Check if AABB is smaller than the camera box
	bool xTooSmall = (middle.x + right) >= (pos.x + size.x)			 && (middle.x - left)   <= (pos.x - size.x);
	bool yTooSmall = (middle.y + top)   >= (pos.y + (size.y * 2.0f)) && (middle.y - bottom) <= pos.y;
	bool zTooSmall = (middle.z + front) >= (pos.z + size.z)			 && (middle.z - back)   <= (pos.z - size.z);

	// Check for any collision at all
	if ((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		insideBox = true;
	}

	// Check with which side the box collided
	if (insideBox)
	{
		// Calculate differences
		float xDiffFirst = fabsf((pos.x - size.x) - (middle.x + right));
		float xDiffSecnd = fabsf((pos.x + size.x) - (middle.x - left));
		float yDiffFirst = fabsf((pos.y) - (middle.y + top));
		float yDiffSecnd = fabsf((pos.y + (size.y * 2.0f)) - (middle.y - bottom));
		float zDiffFirst = fabsf((pos.z - size.z) - (middle.z + front));
		float zDiffSecnd = fabsf((pos.z + size.z) - (middle.z - back));

		// Check in which directions the box moved
		bool xCollision = (xDiffFirst <= pointDifference.x || xDiffSecnd <= pointDifference.x);
		bool yCollision = (yDiffFirst <= pointDifference.y || yDiffSecnd <= pointDifference.y);
		bool zCollision = (zDiffFirst <= pointDifference.z || zDiffSecnd <= pointDifference.z);

		// Perhaps collision
		if (collisionDir == Direction::NONE)
		{
			if (xCollision) { collisionDir = Direction::X; }
			if (yCollision) { collisionDir = Direction::Y; }
			if (zCollision) { collisionDir = Direction::Z; }
		}

		// Determine side
		if (collisionDir == Direction::X)
		{
			collision.setX(true);
		}
		if (collisionDir == Direction::Y)
		{
			collision.setY(true);
		}
		if (collisionDir == Direction::Z)
		{
			collision.setZ(true);
		}
	}
	else
	{
		collisionDir = Direction::NONE;
	}

	// Return total collision
	return collision;
}
