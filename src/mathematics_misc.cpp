#include "mathematics.hpp"

using std::uniform_int_distribution;
using std::uniform_real_distribution;

const float Mathematics::calculateAngleDifference(float firstAngle, float secondAngle)
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

const float Mathematics::limitAngle(float angle)
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

const float Mathematics::calculateReferenceAngle(float angle)
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

const fvec2 Mathematics::calculateAverage(const vector<fvec2> & values)
{
	fvec2 total = fvec2(0.0f);

	for(const auto & value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const fvec3 Mathematics::calculateAverage(const vector<fvec3> & values)
{
	fvec3 total = fvec3(0.0f);

	for(const auto & value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const fvec4 Mathematics::calculateAverage(const vector<fvec4> & values)
{
	fvec4 total = fvec4(0.0f);

	for(const auto & value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const float Mathematics::calculateAverage(const vector<float> & values)
{
	float total = 0.0f;

	for(const auto & value : values)
	{
		total += value;
	}

	return (total / static_cast<float>(values.size()));
}

const unsigned int Mathematics::calculateAverage(const vector<unsigned int> & values)
{
	unsigned int total = 0;

	for(const auto & value : values)
	{
		total += value;
	}

	return static_cast<unsigned int>(total / values.size());
}

const unsigned int Mathematics::getRandomNumber(unsigned int min, unsigned int max)
{
	uniform_int_distribution<unsigned int> dist(min, max);

	return dist(_generator);
}

const int Mathematics::calculateAverage(const vector<int> & values)
{
	int total = 0;

	for(const auto & value : values)
	{
		total += value;
	}

	return static_cast<int>(total / values.size());
}

const float Mathematics::convertToRadians(float angle)
{
	return (angle * DEG2RAD);
}

const float Mathematics::convertToDegrees(float angle)
{
	return (angle * RAD2DEG);
}

const float Mathematics::getPI()
{
	return PI;
}

const float Mathematics::getRandomNumber(float min, float max)
{
	uniform_real_distribution<float> dist(min, max);

	return dist(_generator);
}

const int Mathematics::getRandomNumber(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);

	return dist(_generator);
}

const bool Mathematics::isNormalized(const fvec2 & vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const bool Mathematics::isNormalized(const fvec3 & vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const bool Mathematics::isNormalized(const fvec4 & vector)
{
	return (calculateMagnitude(vector) == 1.0f);
}

const vector<float> Mathematics::calculateDistributedPositions(unsigned int count, float size, bool isAscending)
{
	vector<float> result;

	const auto freeSpace = (2.0f - (static_cast<float>(count) * size));
	const auto gapSpace = (freeSpace / static_cast<float>(count + 1));

	if(isAscending)
	{
		auto position = (-1.0f + (gapSpace + (size * 0.5f)));

		for(unsigned int index = 0; index < count; index++)
		{
			result.push_back(position);

			position += (gapSpace + size);
		}
	}
	else
	{
		auto position = (1.0f - (gapSpace + (size * 0.5f)));

		for(unsigned int index = 0; index < count; index++)
		{
			result.push_back(position);

			position -= (gapSpace + size);
		}
	}

	return result;
}