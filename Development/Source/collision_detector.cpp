#include "collision_detector.hpp"

#include <vector>
#include <algorithm>

using std::vector;

Collision CollisionDetector::check(const AabbEntity& box, Vec3 point, Vec3 pointDifference, Direction& collisionDir)
{
	Collision collision(false, false, false);

	// Get info
	auto pos  = box.getTranslation();
	auto size = box.getScaling() / 2.0f;
	bool insideBox = false;

	// Check for any collision at all
	if (point.x > (pos.x - size.x) && point.x < (pos.x + size.x))
	{
		if (point.y > pos.y && point.y < (pos.y + (size.y * 2.0f)))
		{
			if (point.z > (pos.z - size.z) && point.z < (pos.z + size.z))
			{
				insideBox = true;
			}
		}
	}

	// Check with which side the point collided
	if (insideBox)
	{
		// Get differences
		float xDiffFirst = fabsf((pos.x - size.x) - point.x);
		float xDiffSecnd = fabsf((pos.x + size.x) - point.x);
		float yDiffFirst = fabsf((pos.y) - point.y);
		float yDiffSecnd = fabsf((pos.y + (size.y * 2.0f)) - point.y);
		float zDiffFirst = fabsf((pos.z - size.z) - point.z);
		float zDiffSecnd = fabsf((pos.z + size.z) - point.z);

		// Calculate the minimum difference
		vector<float> diffList = { xDiffFirst, xDiffSecnd, yDiffFirst, yDiffSecnd, zDiffFirst, zDiffSecnd };
		float minDiff = *std::min_element(diffList.begin(), diffList.end());

		// Collision checks
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
