#include "mathematics.hpp"

const fvec3 Math::calculateCrossProduct(fvec3 firstVector, fvec3 secondVector)
{
	// Result
	fvec3 crossVector;

	// Calculate
	crossVector.x = ((firstVector.y * secondVector.z) - (firstVector.z * secondVector.y));
	crossVector.y = ((firstVector.z * secondVector.x) - (firstVector.x * secondVector.z));
	crossVector.z = ((firstVector.x * secondVector.y) - (firstVector.y * secondVector.x));

	// Return
	return crossVector;
}

const fvec2 Math::calculateDifference(fvec2 firstPosition, fvec2 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	// Return
	return fvec2(xDistance, yDistance);
}

const fvec3 Math::calculateDifference(fvec3 firstPosition, fvec3 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	// Return
	return fvec3(xDistance, yDistance, zDistance);
}

const fvec4 Math::calculateDifference(fvec4 firstPosition, fvec4 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	// Return
	return fvec4(xDistance, yDistance, zDistance, wDistance);
}

const fvec2 Math::normalize(fvec2 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;

	// Return
	return vector;
}

const fvec3 Math::normalize(fvec3 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;

	// Return
	return vector;
}

const fvec4 Math::normalize(fvec4 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;
	vector.w *= inverseMagnitude;

	// Return
	return vector;
}

const float Math::calculateDistance(fvec2 firstPosition, fvec2 secondPosition)
{
	// Check if distance is 0
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	// Return
	return calculateMagnitude(fvec2(xDistance, yDistance));
}

const float Math::calculateDistance(fvec3 firstPosition, fvec3 secondPosition)
{
	// Check if distance is 0
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	// Return
	return calculateMagnitude(fvec3(xDistance, yDistance, zDistance));
}

const float Math::calculateDistance(fvec4 firstPosition, fvec4 secondPosition)
{
	// Check if distance is 0
	if(firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	// Return
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