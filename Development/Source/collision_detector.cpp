#include "collision_detector.hpp"

Collision CollisionDetector::check(Vec3 aabbPosition, Vec3 aabbSize, Vec3 middle,
	float bottom, float top, float left, float right, float front, float back, 
	Vec3 positionDifference)
{
	// Temporary values
	Collision collision(false, false, false);
	const auto position = aabbPosition;
	const auto size = aabbSize / 2.0f;
	bool insideBox = false;
	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	// X collision detection
	if (((middle.x + right) > (position.x - size.x) && (middle.x + right) < (position.x + size.x)) ||
		((middle.x - left) < (position.x + size.x) && (middle.x - left) > (position.x - size.x)))
	{
		xInsideBox = true;
	}

	// Y collision detection
	if (((middle.y + top) > (position.y) && (middle.y + top) < (position.y + (size.y * 2.0f))) ||
		((middle.y - bottom) < (position.y + (size.y * 2.0f)) && (middle.y - bottom) > (position.y)))
	{
		yInsideBox = true;

	}

	// Z collision detection
	if (((middle.z + front) > (position.z - size.z) && (middle.z + front) < (position.z + size.z)) ||
		((middle.z - back) < (position.z + size.z) && (middle.z - back) > (position.z - size.z)))
	{
		zInsideBox = true;
	}

	// Check if AABB is smaller than the camera box
	bool xTooSmall = (middle.x + right) >= (position.x + size.x) && (middle.x - left) <= (position.x - size.x);
	bool yTooSmall = (middle.y + top)   >= (position.y + (size.y * 2.0f)) && (middle.y - bottom) <= position.y;
	bool zTooSmall = (middle.z + front) >= (position.z + size.z) && (middle.z - back) <= (position.z - size.z);

	// Check for any collision at all
	if ((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		insideBox = true;
	}

	// Check with which side the box collided
	if (insideBox)
	{
		// Calculate differences
		float xDiffFirst = fabsf((position.x - size.x) - (middle.x + right));
		float xDiffSecnd = fabsf((position.x + size.x) - (middle.x - left));
		float yDiffFirst = fabsf((position.y) - (middle.y + top));
		float yDiffSecnd = fabsf((position.y + (size.y * 2.0f)) - (middle.y - bottom));
		float zDiffFirst = fabsf((position.z - size.z) - (middle.z + front));
		float zDiffSecnd = fabsf((position.z + size.z) - (middle.z - back));

		// Check in which directions the box moved
		bool xCollision = (xDiffFirst <= positionDifference.x || xDiffSecnd <= positionDifference.x);
		bool yCollision = (yDiffFirst <= positionDifference.y || yDiffSecnd <= positionDifference.y);
		bool zCollision = (zDiffFirst <= positionDifference.z || zDiffSecnd <= positionDifference.z);

		// Compose collision direction
		if (xCollision) { collision.setX(true); }
		if (yCollision) { collision.setY(true); }
		if (zCollision) { collision.setZ(true); }
	}

	// Return total collision
	return collision;
}
