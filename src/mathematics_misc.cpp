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
	angle = fmodf(angle, 360.0f);

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
	if(angle >= 0.0f && angle <= 90.0f)
	{
		return angle;
	}
	else if(angle > 90.0f && angle <= 180.0f)
	{
		return (180.0f - angle);
	}
	else if(angle > 180.0f && angle <= 270.0f)
	{
		return (angle - 180.0f);
	}
	else
	{
		return (360.0f - angle);
	}
}

const fvec2 Math::calculateAverage(const vector<fvec2>& values)
{
	fvec2 total = fvec2(0.0f);

	for(const auto& value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const fvec3 Math::calculateAverage(const vector<fvec3>& values)
{
	fvec3 total = fvec3(0.0f);

	for(const auto& value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const fvec4 Math::calculateAverage(const vector<fvec4>& values)
{
	fvec4 total = fvec4(0.0f);

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

const unsigned int Math::calculateAverage(const vector<unsigned int>& values)
{
	unsigned int total = 0;

	for(const auto& value : values)
	{
		total += value;
	}

	return static_cast<unsigned int>(total / values.size());
}

const unsigned int Math::getRandomNumber(unsigned int min, unsigned int max)
{
	uniform_int_distribution<unsigned int> dist(min, max);

	return dist(_generator);
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

const float Math::getRandomNumber(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);

	return dist(_generator);
}

const int Math::getRandomNumber(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);

	return dist(_generator);
}

const bool Math::isNormalized(const fvec2& vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const bool Math::isNormalized(const fvec3& vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const bool Math::isNormalized(const fvec4& vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const fvec2 Math::convertToNdc(const fvec2& position)
{
	fvec2 result = position;

	result.x = ((position.x * 2.0f) - 1.0f);
	result.y = ((position.y * 2.0f) - 1.0f);

	return result;
}

const fvec2 Math::convertFromNdc(const fvec2& position)
{
	fvec2 result = position;

	result.x += 1.0f;
	result.y += 1.0f;
	result.x /= 2.0f;
	result.y /= 2.0f;

	return result;
}