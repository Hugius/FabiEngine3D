#include "mathematics.hpp"

const float Math::calculateAngleDifference(float firstAngle, float secondAngle)
{
	float difference = fabsf(firstAngle - secondAngle);

	if (difference > 180.0f)
	{
		difference = (360.0f - difference);
	}

	return difference;
}

const float Math::calculateReferenceAngle(float initialAngle)
{
	if (initialAngle >= 0.0f && initialAngle <= 90.0f) // 1st quadrant
	{
		return initialAngle;
	}
	else if (initialAngle > 90.0f && initialAngle <= 180.0f) // 2nd quadrant
	{
		return (180.0f - initialAngle);
	}
	else if (initialAngle > 180.0f && initialAngle <= 270.0f) // 3rd quadrant
	{
		return (initialAngle - 180.0f);
	}
	else // 4th quadrant
	{
		return (360.0f - initialAngle);
	}
}

const float Math::convertToRadians(float angle)
{
	return (angle * DEG2RAD);
}

const float Math::convertToDegrees(float angle)
{
	return (angle * RAD2DEG);
}

const float Math::getPI()
{
	return PI;
}