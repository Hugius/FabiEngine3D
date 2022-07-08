#include "camera_collision_handler.hpp"

const bool CameraCollisionHandler::_isInsideAabbX(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto left = box->getLeft();
	const auto right = box->getRight();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabbPosition, aabbSize, boxMiddle, box))
	{
		const auto leftDifference = fabsf((aabbPosition.x - halfAabbSize.x) - (boxMiddle.x + right));
		const auto rightDifference = fabsf((aabbPosition.x + halfAabbSize.x) - (boxMiddle.x - left));
		const auto leftCollision = ((boxMiddleChange.x > 0.0f) && (leftDifference <= fabs(boxMiddleChange.x)));
		const auto rightCollision = ((boxMiddleChange.x < 0.0f) && (rightDifference <= fabs(boxMiddleChange.x)));

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

const bool CameraCollisionHandler::_isInsideAabbY(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto bottom = box->getBottom();
	const auto top = box->getTop();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabbPosition, aabbSize, boxMiddle, box))
	{
		const auto bottomDifference = fabsf((aabbPosition.y) - (boxMiddle.y + top));
		const auto topDifference = fabsf((aabbPosition.y + (halfAabbSize.y * 2.0f)) - (boxMiddle.y - bottom));
		const auto bottomCollision = ((boxMiddleChange.y > 0.0f) && (bottomDifference <= fabs(boxMiddleChange.y)));
		const auto topCollision = ((boxMiddleChange.y < 0.0f) && (topDifference <= fabs(boxMiddleChange.y)));

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

const bool CameraCollisionHandler::_isInsideAabbZ(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const fvec3 & boxMiddleChange, const shared_ptr<Box> box) const
{
	const auto back = box->getBack();
	const auto front = box->getFront();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabbPosition, aabbSize, boxMiddle, box))
	{
		const auto frontDifference = fabsf((aabbPosition.z + halfAabbSize.z) - (boxMiddle.z - front));
		const auto backDifference = fabsf((aabbPosition.z - halfAabbSize.z) - (boxMiddle.z + back));
		const auto frontCollision = ((boxMiddleChange.z < 0.0f) && (frontDifference <= fabs(boxMiddleChange.z)));
		const auto backCollision = ((boxMiddleChange.z > 0.0f) && (backDifference <= fabs(boxMiddleChange.z)));

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

const bool CameraCollisionHandler::_isInsideAabb(const fvec3 & aabbPosition, const fvec3 & aabbSize, const fvec3 & boxMiddle, const shared_ptr<Box> box) const
{
	const auto left = box->getLeft();
	const auto right = box->getRight();
	const auto bottom = box->getBottom();
	const auto top = box->getTop();
	const auto back = box->getBack();
	const auto front = box->getFront();
	const auto halfAabbSize = (aabbSize * 0.5f);

	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	if(((boxMiddle.x + right) > (aabbPosition.x - halfAabbSize.x) && (boxMiddle.x + right) < (aabbPosition.x + halfAabbSize.x)) ||
	   ((boxMiddle.x - left) < (aabbPosition.x + halfAabbSize.x) && (boxMiddle.x - left) > (aabbPosition.x - halfAabbSize.x)))
	{
		xInsideBox = true;
	}

	if(((boxMiddle.y + top) > (aabbPosition.y) && (boxMiddle.y + top) < (aabbPosition.y + (halfAabbSize.y * 2.0f))) ||
	   ((boxMiddle.y - bottom) < (aabbPosition.y + (halfAabbSize.y * 2.0f)) && (boxMiddle.y - bottom) > (aabbPosition.y)))
	{
		yInsideBox = true;

	}

	if(((boxMiddle.z + front) > (aabbPosition.z - halfAabbSize.z) && (boxMiddle.z + front) < (aabbPosition.z + halfAabbSize.z)) ||
	   ((boxMiddle.z - back) < (aabbPosition.z + halfAabbSize.z) && (boxMiddle.z - back) > (aabbPosition.z - halfAabbSize.z)))
	{
		zInsideBox = true;
	}

	const auto xTooSmall = ((boxMiddle.x + right) >= (aabbPosition.x + halfAabbSize.x)) && ((boxMiddle.x - left) <= (aabbPosition.x - halfAabbSize.x));
	const auto yTooSmall = ((boxMiddle.y + top) >= (aabbPosition.y + (halfAabbSize.y * 2.0f))) && ((boxMiddle.y - bottom) <= aabbPosition.y);
	const auto zTooSmall = ((boxMiddle.z + front) >= (aabbPosition.z + halfAabbSize.z)) && ((boxMiddle.z - back) <= (aabbPosition.z - halfAabbSize.z));

	if((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		return true;
	}
	else
	{
		return false;
	}
}