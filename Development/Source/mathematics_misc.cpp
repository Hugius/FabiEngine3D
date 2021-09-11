#include "mathematics.hpp"

const float Math::calculateAngleDifference(float firstAngle, float secondAngle)
{
	float difference = fabsf(firstAngle - secondAngle);

	if (difference > 180.0f)
	{
		return (360.0f - difference);
	}
	else
	{
		return difference;
	}
}

const float Math::limitAngle(float angle)
{
	// 360 degrees max
	angle = fmodf(angle, 360.0f);

	// Make the angle non-negative
	if (angle < 0.0f)
	{
		return (360.0f - fabsf(angle));
	}
	else
	{
		return angle;
	}
}

const float Math::calculateReferenceAngle(float angle)
{
	if (angle >= 0.0f && angle <= 90.0f) // 1st quadrant
	{
		return angle;
	}
	else if (angle > 90.0f && angle <= 180.0f) // 2nd quadrant
	{
		return (180.0f - angle);
	}
	else if (angle > 180.0f && angle <= 270.0f) // 3rd quadrant
	{
		return (angle - 180.0f);
	}
	else // 4th quadrant
	{
		return (360.0f - angle);
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