#include "mathematics.hpp"

const fvec3 Math::calculateCrossProduct(fvec3 firstVector, fvec3 secondVector)
{
	fvec3 crossVector;

	crossVector.x = ((firstVector.y * secondVector.z) - (firstVector.z * secondVector.y));
	crossVector.y = ((firstVector.z * secondVector.x) - (firstVector.x * secondVector.z));
	crossVector.z = ((firstVector.x * secondVector.y) - (firstVector.y * secondVector.x));

	return crossVector;
}

const fvec2 Math::calculateDifference(fvec2 firstPosition, fvec2 secondPosition)
{
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	return fvec2(xDistance, yDistance);
}

const fvec3 Math::calculateDifference(fvec3 firstPosition, fvec3 secondPosition)
{
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	return fvec3(xDistance, yDistance, zDistance);
}

const fvec4 Math::calculateDifference(fvec4 firstPosition, fvec4 secondPosition)
{
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	return fvec4(xDistance, yDistance, zDistance, wDistance);
}

const fvec2 Math::normalize(fvec2 vector)
{
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;

	return vector;
}

const fvec3 Math::normalize(fvec3 vector)
{
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;

	return vector;
}

const fvec4 Math::normalize(fvec4 vector)
{
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;
	vector.w *= inverseMagnitude;

	return vector;
}

const float Math::calculateDistance(fvec2 firstPosition, fvec2 secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	return calculateMagnitude(fvec2(xDistance, yDistance));
}

const float Math::calculateDistance(fvec3 firstPosition, fvec3 secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	return calculateMagnitude(fvec3(xDistance, yDistance, zDistance));
}

const float Math::calculateDistance(fvec4 firstPosition, fvec4 secondPosition)
{
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	return calculateMagnitude(fvec4(xDistance, yDistance, zDistance, wDistance));
}

const float Math::calculateDotProduct(fvec2 firstVector, fvec2 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y));
}

const float Math::calculateDotProduct(fvec3 firstVector, fvec3 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z));
}

const float Math::calculateDotProduct(fvec4 firstVector, fvec4 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z) + (firstVector.w * secondVector.w));
}

const float Math::calculateMagnitude(fvec2 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

const float Math::calculateMagnitude(fvec3 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

const float Math::calculateMagnitude(fvec4 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z) + (vector.w * vector.w));
}