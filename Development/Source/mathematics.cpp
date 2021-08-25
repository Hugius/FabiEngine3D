#include "mathematics.hpp"
#include "mathematics.hpp"

float Math::calculateDotProduct(Vec2 firstVector, Vec2 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y));
}

float Math::calculateDotProduct(Vec3 firstVector, Vec3 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z));
}

float Math::calculateDotProduct(Vec4 firstVector, Vec4 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z) + (firstVector.w * secondVector.w));
}

float Math::getPI()
{
	return PI;
}

float Math::convertToRadians(float angle)
{
	return (angle * DEG2RAD);
}

float Math::convertToDegrees(float angle)
{
	return (angle * RAD2DEG);
}

float Math::calculateReferenceAngle(float initialAngle)
{
	if (initialAngle >= 0.0f && initialAngle <= 90.0f)
	{
		return initialAngle;
	}
	else if (initialAngle > 90.0f && initialAngle <= 180.0f)
	{
		return 180.0f - initialAngle;
	}
	else if (initialAngle > 180.0f && initialAngle <= 270.0f)
	{
		return initialAngle - 180.0f;
	}
	else
	{
		return 360.0f - initialAngle;
	}
}

float Math::calculateAbsoluteDistance(Vec3 firstPosition, Vec3 secondPosition)
{
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	return sqrtf((xDistance * xDistance) + (yDistance * yDistance) + (zDistance * zDistance));
}