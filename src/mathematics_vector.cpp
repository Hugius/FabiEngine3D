#include "mathematics.hpp"

const fvec3 Mathematics::calculateCrossProduct(const fvec3 & firstVector, const fvec3 & secondVector)
{
	fvec3 result = {};

	result.x = ((firstVector.y * secondVector.z) - (firstVector.z * secondVector.y));
	result.y = ((firstVector.z * secondVector.x) - (firstVector.x * secondVector.z));
	result.z = ((firstVector.x * secondVector.y) - (firstVector.y * secondVector.x));

	return result;
}

const fvec2 Mathematics::calculateDifference(const fvec2 & firstPosition, const fvec2 & secondPosition)
{
	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);

	return fvec2(xDistance, yDistance);
}

const fvec3 Mathematics::calculateDifference(const fvec3 & firstPosition, const fvec3 & secondPosition)
{
	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);
	const auto zDistance = fabsf(firstPosition.z - secondPosition.z);

	return fvec3(xDistance, yDistance, zDistance);
}

const fvec4 Mathematics::calculateDifference(const fvec4 & firstPosition, const fvec4 & secondPosition)
{
	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);
	const auto zDistance = fabsf(firstPosition.z - secondPosition.z);
	const auto wDistance = fabsf(firstPosition.w - secondPosition.w);

	return fvec4(xDistance, yDistance, zDistance, wDistance);
}

const fvec2 Mathematics::normalize(const fvec2 & vector)
{
	const auto invertedMagnitude = (1.0f / calculateMagnitude(vector));

	return fvec2((vector.x * invertedMagnitude), (vector.y * invertedMagnitude));
}

const fvec3 Mathematics::normalize(const fvec3 & vector)
{
	const auto invertedMagnitude = (1.0f / calculateMagnitude(vector));

	return fvec3((vector.x * invertedMagnitude), (vector.y * invertedMagnitude), (vector.z * invertedMagnitude));
}

const fvec4 Mathematics::normalize(const fvec4 & vector)
{
	const auto invertedMagnitude = (1.0f / calculateMagnitude(vector));

	return fvec4((vector.x * invertedMagnitude), (vector.y * invertedMagnitude), (vector.z * invertedMagnitude), (vector.w * invertedMagnitude));
}

const float Mathematics::calculateDistance(const fvec2 & firstPosition, const fvec2 & secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);

	return calculateMagnitude(fvec2(xDistance, yDistance));
}

const float Mathematics::calculateDistance(const fvec3 & firstPosition, const fvec3 & secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);
	const auto zDistance = fabsf(firstPosition.z - secondPosition.z);

	return calculateMagnitude(fvec3(xDistance, yDistance, zDistance));
}

const float Mathematics::calculateDistance(const fvec4 & firstPosition, const fvec4 & secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	const auto xDistance = fabsf(firstPosition.x - secondPosition.x);
	const auto yDistance = fabsf(firstPosition.y - secondPosition.y);
	const auto zDistance = fabsf(firstPosition.z - secondPosition.z);
	const auto wDistance = fabsf(firstPosition.w - secondPosition.w);

	return calculateMagnitude(fvec4(xDistance, yDistance, zDistance, wDistance));
}

const float Mathematics::calculateDotProduct(const fvec2 & firstVector, const fvec2 & secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y));
}

const float Mathematics::calculateDotProduct(const fvec3 & firstVector, const fvec3 & secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z));
}

const float Mathematics::calculateDotProduct(const fvec4 & firstVector, const fvec4 & secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z) + (firstVector.w * secondVector.w));
}

const float Mathematics::calculateMagnitude(const fvec2 & vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

const float Mathematics::calculateMagnitude(const fvec3 & vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

const float Mathematics::calculateMagnitude(const fvec4 & vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z) + (vector.w * vector.w));
}