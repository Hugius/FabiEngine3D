#include "camera_collision_handler.hpp"

const bool CameraCollisionHandler::_isInsideAabbX(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, const shared_ptr<Box> cameraBox) const
{
	const auto left = cameraBox->getLeft();
	const auto right = cameraBox->getRight();
	const auto aabbPosition = aabb->getBasePosition();
	const auto aabbSize = aabb->getBaseSize();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabb, cameraBoxMiddle, cameraBox))
	{
		const auto leftDifference = fabsf((aabbPosition.x - halfAabbSize.x) - (cameraBoxMiddle.x + right));
		const auto rightDifference = fabsf((aabbPosition.x + halfAabbSize.x) - (cameraBoxMiddle.x - left));
		const auto leftCollision = ((cameraBoxMiddleChange.x > 0.0f) && (leftDifference <= fabs(cameraBoxMiddleChange.x)));
		const auto rightCollision = ((cameraBoxMiddleChange.x < 0.0f) && (rightDifference <= fabs(cameraBoxMiddleChange.x)));

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

const bool CameraCollisionHandler::_isInsideAabbY(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, const shared_ptr<Box> cameraBox) const
{
	const auto bottom = cameraBox->getBottom();
	const auto top = cameraBox->getTop();
	const auto aabbPosition = aabb->getBasePosition();
	const auto aabbSize = aabb->getBaseSize();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabb, cameraBoxMiddle, cameraBox))
	{
		const auto bottomDifference = fabsf((aabbPosition.y) - (cameraBoxMiddle.y + top));
		const auto topDifference = fabsf((aabbPosition.y + (halfAabbSize.y * 2.0f)) - (cameraBoxMiddle.y - bottom));
		const auto bottomCollision = ((cameraBoxMiddleChange.y > 0.0f) && (bottomDifference <= fabs(cameraBoxMiddleChange.y)));
		const auto topCollision = ((cameraBoxMiddleChange.y < 0.0f) && (topDifference <= fabs(cameraBoxMiddleChange.y)));

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

const bool CameraCollisionHandler::_isInsideAabbZ(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const fvec3 & cameraBoxMiddleChange, const shared_ptr<Box> cameraBox) const
{
	const auto back = cameraBox->getBack();
	const auto front = cameraBox->getFront();
	const auto aabbPosition = aabb->getBasePosition();
	const auto aabbSize = aabb->getBaseSize();
	const auto halfAabbSize = (aabbSize * 0.5f);

	if(_isInsideAabb(aabb, cameraBoxMiddle, cameraBox))
	{
		const auto frontDifference = fabsf((aabbPosition.z + halfAabbSize.z) - (cameraBoxMiddle.z - front));
		const auto backDifference = fabsf((aabbPosition.z - halfAabbSize.z) - (cameraBoxMiddle.z + back));
		const auto frontCollision = ((cameraBoxMiddleChange.z < 0.0f) && (frontDifference <= fabs(cameraBoxMiddleChange.z)));
		const auto backCollision = ((cameraBoxMiddleChange.z > 0.0f) && (backDifference <= fabs(cameraBoxMiddleChange.z)));

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

const bool CameraCollisionHandler::_isInsideAabb(shared_ptr<Aabb> aabb, const fvec3 & cameraBoxMiddle, const shared_ptr<Box> cameraBox) const
{
	const auto left = cameraBox->getLeft();
	const auto right = cameraBox->getRight();
	const auto bottom = cameraBox->getBottom();
	const auto top = cameraBox->getTop();
	const auto back = cameraBox->getBack();
	const auto front = cameraBox->getFront();
	const auto aabbPosition = aabb->getBasePosition();
	const auto aabbSize = aabb->getBaseSize();
	const auto halfAabbSize = (aabbSize * 0.5f);

	bool xInsideBox = false;
	bool yInsideBox = false;
	bool zInsideBox = false;

	if(((cameraBoxMiddle.x + right) > (aabbPosition.x - halfAabbSize.x) && (cameraBoxMiddle.x + right) < (aabbPosition.x + halfAabbSize.x)) ||
	   ((cameraBoxMiddle.x - left) < (aabbPosition.x + halfAabbSize.x) && (cameraBoxMiddle.x - left) > (aabbPosition.x - halfAabbSize.x)))
	{
		xInsideBox = true;
	}

	if(((cameraBoxMiddle.y + top) > (aabbPosition.y) && (cameraBoxMiddle.y + top) < (aabbPosition.y + (halfAabbSize.y * 2.0f))) ||
	   ((cameraBoxMiddle.y - bottom) < (aabbPosition.y + (halfAabbSize.y * 2.0f)) && (cameraBoxMiddle.y - bottom) > (aabbPosition.y)))
	{
		yInsideBox = true;

	}

	if(((cameraBoxMiddle.z + front) > (aabbPosition.z - halfAabbSize.z) && (cameraBoxMiddle.z + front) < (aabbPosition.z + halfAabbSize.z)) ||
	   ((cameraBoxMiddle.z - back) < (aabbPosition.z + halfAabbSize.z) && (cameraBoxMiddle.z - back) > (aabbPosition.z - halfAabbSize.z)))
	{
		zInsideBox = true;
	}

	const auto xTooSmall = ((cameraBoxMiddle.x + right) >= (aabbPosition.x + halfAabbSize.x)) && ((cameraBoxMiddle.x - left) <= (aabbPosition.x - halfAabbSize.x));
	const auto yTooSmall = ((cameraBoxMiddle.y + top) >= (aabbPosition.y + (halfAabbSize.y * 2.0f))) && ((cameraBoxMiddle.y - bottom) <= aabbPosition.y);
	const auto zTooSmall = ((cameraBoxMiddle.z + front) >= (aabbPosition.z + halfAabbSize.z)) && ((cameraBoxMiddle.z - back) <= (aabbPosition.z - halfAabbSize.z));

	if((xInsideBox || xTooSmall) && (yInsideBox || yTooSmall) && (zInsideBox || zTooSmall))
	{
		return true;
	}
	else
	{
		return false;
	}
}