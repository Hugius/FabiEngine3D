#include "camera_collision_detector.hpp"

bool CameraCollisionDetector::checkX(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box)
{
	// Temporary values
	const auto left = box.getLeft();
	const auto right = box.getRight();
	const Vec3 halfAabbSize = (aabbSize / 2.0f);

	// Check if box is inside AABB
	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		// Calculate side differences
		float leftDifference = fabsf((aabbPosition.x - halfAabbSize.x) - (boxMiddle.x + right));
		float rightDifference = fabsf((aabbPosition.x + halfAabbSize.x) - (boxMiddle.x - left));

		// Check in which direction the box moved
		bool leftCollision = (boxMiddleChange.x > 0.0f && leftDifference <= fabs(boxMiddleChange.x));
		bool rightCollision = (boxMiddleChange.x < 0.0f && rightDifference <= fabs(boxMiddleChange.x));

		// Check for X collision
		if(leftCollision || rightCollision)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool CameraCollisionDetector::checkY(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box)
{
	// Temporary values
	const auto bottom = box.getBottom();
	const auto top = box.getTop();
	const Vec3 halfAabbSize = (aabbSize / 2.0f);

	// Check if box is inside AABB
	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		// Calculate side differences
		float bottomDifference = fabsf((aabbPosition.y) - (boxMiddle.y + top));
		float topDifference = fabsf((aabbPosition.y + (halfAabbSize.y * 2.0f)) - (boxMiddle.y - bottom));

		// Check in which direction the box moved
		bool bottomCollision = (boxMiddleChange.y > 0.0f && bottomDifference <= fabs(boxMiddleChange.y));
		bool topCollision = (boxMiddleChange.y < 0.0f && topDifference <= fabs(boxMiddleChange.y));

		// Check for Y collision
		if(bottomCollision || topCollision)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool CameraCollisionDetector::checkZ(Vec3 aabbPosition, Vec3 aabbSize, Vec3 boxMiddle, Vec3 boxMiddleChange, Box box)
{
	// Temporary values
	const auto back = box.getBack();
	const auto front = box.getFront();
	const Vec3 halfAabbSize = (aabbSize / 2.0f);

	// Check if box is inside AABB
	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		// Calculate side differences
		float frontDifference = fabsf((aabbPosition.z + halfAabbSize.z) - (boxMiddle.z - front));
		float backDifference = fabsf((aabbPosition.z - halfAabbSize.z) - (boxMiddle.z + back));

		// Check in which direction the box moved
		bool frontCollision = (boxMiddleChange.z < 0.0f && frontDifference <= fabs(boxMiddleChange.z));
		bool backCollision = (boxMiddleChange.z > 0.0f && backDifference <= fabs(boxMiddleChange.z));

		// Check for Z collision
		if(frontCollision || backCollision)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool CameraCollisionDetector::_isInside(Vec3 aabbPosition, Vec3 aabbHalfSize, Vec3 boxMiddle, Box box)
{
	// Temporary values
	const auto left = box.getLeft();
	const auto right = box.getRight();
	const auto bottom = box.getBottom();
	const auto top = box.getTop();
	const auto back = box.getBack();
	const auto front = box.getFront();
	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	// X collision detection
	if(((boxMiddle.x + right) > (aabbPosition.x - aabbHalfSize.x) && (boxMiddle.x + right) < (aabbPosition.x + aabbHalfSize.x)) ||
	   ((boxMiddle.x - left) < (aabbPosition.x + aabbHalfSize.x) && (boxMiddle.x - left) > (aabbPosition.x - aabbHalfSize.x)))
	{
		xInsideBox = true;
	}

	// Y collision detection
	if(((boxMiddle.y + top) > (aabbPosition.y) && (boxMiddle.y + top) < (aabbPosition.y + (aabbHalfSize.y * 2.0f))) ||
	   ((boxMiddle.y - bottom) < (aabbPosition.y + (aabbHalfSize.y * 2.0f)) && (boxMiddle.y - bottom) > (aabbPosition.y)))
	{
		yInsideBox = true;

	}

	// Z collision detection
	if(((boxMiddle.z + front) > (aabbPosition.z - aabbHalfSize.z) && (boxMiddle.z + front) < (aabbPosition.z + aabbHalfSize.z)) ||
	   ((boxMiddle.z - back) < (aabbPosition.z + aabbHalfSize.z) && (boxMiddle.z - back) > (aabbPosition.z - aabbHalfSize.z)))
	{
		zInsideBox = true;
	}

	// Check if AABB is smaller than the camera box
	bool xTooSmall = ((boxMiddle.x + right) >= (aabbPosition.x + aabbHalfSize.x)) && ((boxMiddle.x - left) <= (aabbPosition.x - aabbHalfSize.x));
	bool yTooSmall = ((boxMiddle.y + top) >= (aabbPosition.y + (aabbHalfSize.y * 2.0f))) && ((boxMiddle.y - bottom) <= aabbPosition.y);
	bool zTooSmall = ((boxMiddle.z + front) >= (aabbPosition.z + aabbHalfSize.z)) && ((boxMiddle.z - back) <= (aabbPosition.z - aabbHalfSize.z));

	// Check if any collision happened
	if((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		return true;
	}
	else
	{
		return false;
	}
}