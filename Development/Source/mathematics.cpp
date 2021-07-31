#include "mathematics.hpp"

float Math::degreesToRadians(float angle)
{
	return (angle * DEG2RAD);
}

float Math::radiansToDegrees(float angle)
{
	return (angle * RAD2DEG);
}

float Math::getPI()
{
	return PI;
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