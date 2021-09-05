#include "mathematics.hpp"

const Vec3 Math::calculateCrossProduct(Vec3 firstVector, Vec3 secondVector)
{
	// Result
	Vec3 crossVector;

	// Calculate
	crossVector.x = ((firstVector.y * secondVector.z) - (firstVector.z * secondVector.y));
	crossVector.y = ((firstVector.z * secondVector.x) - (firstVector.x * secondVector.z));
	crossVector.z = ((firstVector.x * secondVector.y) - (firstVector.y * secondVector.x));

	// Return
	return crossVector;
}

const Vec2 Math::calculateVectorDifference(Vec2 firstPosition, Vec2 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	// Return
	return Vec2(xDistance, yDistance);
}

const Vec3 Math::calculateVectorDifference(Vec3 firstPosition, Vec3 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	// Return
	return Vec3(xDistance, yDistance, zDistance);
}

const Vec4 Math::calculateVectorDifference(Vec4 firstPosition, Vec4 secondPosition)
{
	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	// Return
	return Vec4(xDistance, yDistance, zDistance, wDistance);
}

const Vec2 Math::normalizeVector(Vec2 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateVectorMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;

	// Return
	return vector;
}

const Vec3 Math::normalizeVector(Vec3 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateVectorMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;

	// Return
	return vector;
}

const Vec4 Math::normalizeVector(Vec4 vector)
{
	// Calculate inverse magnitude
	float inverseMagnitude = (1.0f / calculateVectorMagnitude(vector));

	// Normalize
	vector.x *= inverseMagnitude;
	vector.y *= inverseMagnitude;
	vector.z *= inverseMagnitude;
	vector.w *= inverseMagnitude;

	// Return
	return vector;
}

const float Math::calculateVectorDistance(Vec2 firstPosition, Vec2 secondPosition)
{
	// Check if distance is 0
	if (firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);

	// Return
	return calculateVectorMagnitude(Vec2(xDistance, yDistance));
}

const float Math::calculateVectorDistance(Vec3 firstPosition, Vec3 secondPosition)
{
	// Check if distance is 0
	if (firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);

	// Return
	return calculateVectorMagnitude(Vec3(xDistance, yDistance, zDistance));
}

const float Math::calculateVectorDistance(Vec4 firstPosition, Vec4 secondPosition)
{
	// Check if distance is 0
	if (firstPosition == secondPosition)
	{
		return 0.0f;
	}

	// Calculate
	float xDistance = fabsf(firstPosition.x - secondPosition.x);
	float yDistance = fabsf(firstPosition.y - secondPosition.y);
	float zDistance = fabsf(firstPosition.z - secondPosition.z);
	float wDistance = fabsf(firstPosition.w - secondPosition.w);

	// Return
	return calculateVectorMagnitude(Vec4(xDistance, yDistance, zDistance, wDistance));
}

const float Math::calculateDotProduct(Vec2 firstVector, Vec2 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y));
}

const float Math::calculateDotProduct(Vec3 firstVector, Vec3 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z));
}

const float Math::calculateDotProduct(Vec4 firstVector, Vec4 secondVector)
{
	return ((firstVector.x * secondVector.x) + (firstVector.y * secondVector.y) + (firstVector.z * secondVector.z) + (firstVector.w * secondVector.w));
}

const float Math::calculateVectorMagnitude(Vec2 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
}

const float Math::calculateVectorMagnitude(Vec3 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z));
}

const float Math::calculateVectorMagnitude(Vec4 vector)
{
	return sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z) + (vector.w * vector.w));
}