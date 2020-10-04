#include "collision_detector.hpp"

#include <vector>
#include <algorithm>

using std::vector;

Collision CollisionDetector::check(const AabbEntity& box, vec3 point, vec3 pointDifference, CollisionDirection& collisionDir)
{
	Collision collision(false, false, false);

	// Get info
	auto pos  = box.getTranslation();
	auto size = box.getScaling();
	bool insideBox = false;

	// Check for any collision at all
	if (point.x > (pos.x - size.x) && point.x < (pos.x + size.x))
	{
		if (point.y > (pos.y - size.y) && point.y < (pos.y + size.y))
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
		float yDiffFirst = fabsf((pos.y - size.y) - point.y);
		float yDiffSecnd = fabsf((pos.y + size.y) - point.y);
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
		if (collisionDir == CollisionDirection::NONE)
		{
			if (xCollision) { collisionDir = CollisionDirection::X; }
			if (yCollision) { collisionDir = CollisionDirection::Y; }
			if (zCollision) { collisionDir = CollisionDirection::Z; }
		}

		// Determine side
		if (collisionDir == CollisionDirection::X)
		{
			collision.setX(true);
		}
		if (collisionDir == CollisionDirection::Y)
		{
			collision.setY(true);
		}
		if (collisionDir == CollisionDirection::Z)
		{
			collision.setZ(true);
		}
	}
	else
	{
		collisionDir = CollisionDirection::NONE;
	}

	// Return total collision
	return collision;
}
