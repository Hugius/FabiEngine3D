#include "collision_detector.hpp"

Collision CollisionDetector::check(Vec3 boxPosition, Vec3 boxSize, Vec3 middlePosition,
	float bottom, float top, float left, float right, float front, float back, 
	Vec3 middleChange, bool hasCollided)
{
	// Temporary values
	Collision collision(false, false, false);
	const auto position = boxPosition;
	const auto size = boxSize / 2.0f;
	bool isInsideBox = false;
	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	// X collision detection
	if (((middlePosition.x + right) > (position.x - size.x) && (middlePosition.x + right) < (position.x + size.x)) ||
		((middlePosition.x - left) < (position.x + size.x) && (middlePosition.x - left) > (position.x - size.x)))
	{
		xInsideBox = true;
	}

	// Y collision detection
	if (((middlePosition.y + top) > (position.y) && (middlePosition.y + top) < (position.y + (size.y * 2.0f))) ||
		((middlePosition.y - bottom) < (position.y + (size.y * 2.0f)) && (middlePosition.y - bottom) > (position.y)))
	{
		yInsideBox = true;

	}

	// Z collision detection
	if (((middlePosition.z + front) > (position.z - size.z) && (middlePosition.z + front) < (position.z + size.z)) ||
		((middlePosition.z - back) < (position.z + size.z) && (middlePosition.z - back) > (position.z - size.z)))
	{
		zInsideBox = true;
	}

	// Check if AABB is smaller than the camera box
	bool xTooSmall = (middlePosition.x + right) >= (position.x + size.x) && (middlePosition.x - left) <= (position.x - size.x);
	bool yTooSmall = (middlePosition.y + top)   >= (position.y + (size.y * 2.0f)) && (middlePosition.y - bottom) <= position.y;
	bool zTooSmall = (middlePosition.z + front) >= (position.z + size.z) && (middlePosition.z - back) <= (position.z - size.z);

	// Check for any collision at all
	if ((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		isInsideBox = true;
	}

	// Check which side collided
	if (isInsideBox)
	{
		// Calculate side differences
		float leftDifference = fabsf((position.x - size.x) - (middlePosition.x + right));
		float rightDifference = fabsf((position.x + size.x) - (middlePosition.x - left));
		float bottomDifference = fabsf((position.y) - (middlePosition.y + top));
		float topDifference = fabsf((position.y + (size.y * 2.0f)) - (middlePosition.y - bottom));
		float backDifference = fabsf((position.z - size.z) - (middlePosition.z + back));
		float frontDifference = fabsf((position.z + size.z) - (middlePosition.z - front));

		// Check in which direction the box moved
		bool leftCollision = (middleChange.x > 0.0f && leftDifference <= fabs(middleChange.x));
		bool rightCollision = (middleChange.x < 0.0f && rightDifference <= fabs(middleChange.x));
		bool bottomCollision = (middleChange.y > 0.0f && bottomDifference <= fabs(middleChange.y));
		bool topCollision = (middleChange.y < 0.0f && topDifference <= fabs(middleChange.y));
		bool backCollision = (middleChange.z > 0.0f && backDifference <= fabs(middleChange.z));
		bool frontCollision = (middleChange.z < 0.0f && frontDifference <= fabs(middleChange.z));

		// Compose collision direction
		if (leftCollision   || rightCollision) { collision.setX(true); }
		if (bottomCollision || topCollision)   { collision.setY(true); }
		if (backCollision   || frontCollision) { collision.setZ(true); }
	}
	
	// Return total collision
	return collision;
}