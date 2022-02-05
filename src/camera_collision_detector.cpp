#include "camera_collision_detector.hpp"

const bool CameraCollisionDetector::checkX(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto left = box->getLeft();
	const auto right = box->getRight();
	const fvec3 halfAabbSize = (aabbSize * 0.5f);

	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		float leftDifference = fabsf((aabbPosition.x - halfAabbSize.x) - (boxMiddle.x + right));
		float rightDifference = fabsf((aabbPosition.x + halfAabbSize.x) - (boxMiddle.x - left));

		bool leftCollision = (boxMiddleChange.x > 0.0f && leftDifference <= fabs(boxMiddleChange.x));
		bool rightCollision = (boxMiddleChange.x < 0.0f && rightDifference <= fabs(boxMiddleChange.x));

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

const bool CameraCollisionDetector::checkY(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto bottom = box->getBottom();
	const auto top = box->getTop();
	const fvec3 halfAabbSize = (aabbSize * 0.5f);

	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		float bottomDifference = fabsf((aabbPosition.y) - (boxMiddle.y + top));
		float topDifference = fabsf((aabbPosition.y + (halfAabbSize.y * 2.0f)) - (boxMiddle.y - bottom));

		bool bottomCollision = (boxMiddleChange.y > 0.0f && bottomDifference <= fabs(boxMiddleChange.y));
		bool topCollision = (boxMiddleChange.y < 0.0f && topDifference <= fabs(boxMiddleChange.y));

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

const bool CameraCollisionDetector::checkZ(const fvec3& aabbPosition, const fvec3& aabbSize, const fvec3& boxMiddle, const fvec3& boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto back = box->getBack();
	const auto front = box->getFront();
	const fvec3 halfAabbSize = (aabbSize * 0.5f);

	if(_isInside(aabbPosition, halfAabbSize, boxMiddle, box))
	{
		float frontDifference = fabsf((aabbPosition.z + halfAabbSize.z) - (boxMiddle.z - front));
		float backDifference = fabsf((aabbPosition.z - halfAabbSize.z) - (boxMiddle.z + back));

		bool frontCollision = (boxMiddleChange.z < 0.0f && frontDifference <= fabs(boxMiddleChange.z));
		bool backCollision = (boxMiddleChange.z > 0.0f && backDifference <= fabs(boxMiddleChange.z));

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

const bool CameraCollisionDetector::_isInside(const fvec3& aabbPosition, const fvec3& aabbHalfSize, const fvec3& boxMiddle, const shared_ptr<Box> box) const
{
	const auto left = box->getLeft();
	const auto right = box->getRight();
	const auto bottom = box->getBottom();
	const auto top = box->getTop();
	const auto back = box->getBack();
	const auto front = box->getFront();
	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	if(((boxMiddle.x + right) > (aabbPosition.x - aabbHalfSize.x) && (boxMiddle.x + right) < (aabbPosition.x + aabbHalfSize.x)) ||
	   ((boxMiddle.x - left) < (aabbPosition.x + aabbHalfSize.x) && (boxMiddle.x - left) > (aabbPosition.x - aabbHalfSize.x)))
	{
		xInsideBox = true;
	}

	if(((boxMiddle.y + top) > (aabbPosition.y) && (boxMiddle.y + top) < (aabbPosition.y + (aabbHalfSize.y * 2.0f))) ||
	   ((boxMiddle.y - bottom) < (aabbPosition.y + (aabbHalfSize.y * 2.0f)) && (boxMiddle.y - bottom) > (aabbPosition.y)))
	{
		yInsideBox = true;

	}

	if(((boxMiddle.z + front) > (aabbPosition.z - aabbHalfSize.z) && (boxMiddle.z + front) < (aabbPosition.z + aabbHalfSize.z)) ||
	   ((boxMiddle.z - back) < (aabbPosition.z + aabbHalfSize.z) && (boxMiddle.z - back) > (aabbPosition.z - aabbHalfSize.z)))
	{
		zInsideBox = true;
	}

	bool xTooSmall = ((boxMiddle.x + right) >= (aabbPosition.x + aabbHalfSize.x)) && ((boxMiddle.x - left) <= (aabbPosition.x - aabbHalfSize.x));
	bool yTooSmall = ((boxMiddle.y + top) >= (aabbPosition.y + (aabbHalfSize.y * 2.0f))) && ((boxMiddle.y - bottom) <= aabbPosition.y);
	bool zTooSmall = ((boxMiddle.z + front) >= (aabbPosition.z + aabbHalfSize.z)) && ((boxMiddle.z - back) <= (aabbPosition.z - aabbHalfSize.z));

	if((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		return true;
	}
	else
	{
		return false;
	}
}