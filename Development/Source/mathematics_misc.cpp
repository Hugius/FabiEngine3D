#include "mathematics.hpp"

using std::uniform_int_distribution;
using std::uniform_real_distribution;

const float Math::calculateAngleDifference(float firstAngle, float secondAngle)
{
	float difference = fabsf(firstAngle - secondAngle);

	if(difference > 180.0f)
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
	if(angle < 0.0f)
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
	if(angle >= 0.0f && angle <= 90.0f) // 1st quadrant
	{
		return angle;
	}
	else if(angle > 90.0f && angle <= 180.0f) // 2nd quadrant
	{
		return (180.0f - angle);
	}
	else if(angle > 180.0f && angle <= 270.0f) // 3rd quadrant
	{
		return (angle - 180.0f);
	}
	else // 4th quadrant
	{
		return (360.0f - angle);
	}
}

const Vec3 Math::calculateAverage(const vector<Vec3>& values)
{
	Vec3 total = Vec3(0.0f);

	for(const auto& value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const float Math::calculateAverage(const vector<float>& values)
{
	float total = 0.0f;

	for(const auto& value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const int Math::calculateAverage(const vector<int>& values)
{
	int total = 0;

	for(const auto& value : values)
	{
		total += value;
	}

	return static_cast<int>(total / values.size());
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

const float Math::getRandomFloat(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);
	return dist(_generator);
}

const int Math::getRandomInteger(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(_generator);
}

const Vec2 Math::convertToNDC(Vec2 position)
{
	position.x = ((position.x * 2.0f) - 1.0f);
	position.y = ((position.y * 2.0f) - 1.0f);

	return Vec2(position.x, position.y);
}

const Vec2 Math::convertFromNDC(Vec2 position)
{
	position.x += 1.0f;
	position.y += 1.0f;
	position.x /= 2.0f;
	position.y /= 2.0f;

	return Vec2(position.x, position.y);
}