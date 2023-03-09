#pragma once

#include "ivec2.hpp"
#include "ivec3.hpp"
#include "ivec4.hpp"
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"
#include "imat22.hpp"
#include "imat33.hpp"
#include "imat44.hpp"
#include "fmat22.hpp"
#include "fmat33.hpp"
#include "fmat44.hpp"
#include "direction_order_type.hpp"

#include <vector>
#include <random>
#include <ctime>

using std::vector;
using std::mt19937;

class Mathematics final
{
public:
	Mathematics() = delete;

	static const vector<float> calculateDistributedPositions(int count, float size, bool isAscending);

	static const fmat44 createTranslationMatrix(float x, float y, float z);
	static const fmat44 createTranslationMatrixX(float value);
	static const fmat44 createTranslationMatrixY(float value);
	static const fmat44 createTranslationMatrixZ(float value);
	static const fmat44 createRotationMatrix(float x, float y, float z, DirectionOrderType order);
	static const fmat44 createRotationMatrixX(float angle);
	static const fmat44 createRotationMatrixY(float angle);
	static const fmat44 createRotationMatrixZ(float angle);
	static const fmat44 createScalingMatrix(float x, float y, float z);
	static const fmat44 createScalingMatrixX(float value);
	static const fmat44 createScalingMatrixY(float value);
	static const fmat44 createScalingMatrixZ(float value);
	static const fmat44 createViewMatrix(const fvec3 & eye, const fvec3 & center, const fvec3 & up);
	static const fmat44 createOrthographicProjectionMatrix(float leftZ, float rightZ, float bottomZ, float topZ, float nearZ, float farZ);
	static const fmat44 createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far);
	static const fmat44 invertMatrix(const fmat44 & matrix);
	static const fmat44 transposeMatrix(const fmat44 & matrix);

	static const fmat33 invertMatrix(const fmat33 & matrix);
	static const fmat33 transposeMatrix(const fmat33 & matrix);

	static const fmat22 invertMatrix(const fmat22 & matrix);
	static const fmat22 transposeMatrix(const fmat22 & matrix);

	static const fvec4 calculateAverage(const vector<fvec4> & values);
	static const fvec4 calculateDifference(const fvec4 & firstPosition, const fvec4 & secondPosition);
	static const fvec4 normalize(const fvec4 & vector);

	static const fvec3 calculateAverage(const vector<fvec3> & values);
	static const fvec3 calculateCrossProduct(const fvec3 & firstVector, const fvec3 & secondVector);
	static const fvec3 calculateDifference(const fvec3 & firstPosition, const fvec3 & secondPosition);
	static const fvec3 normalize(const fvec3 & vector);

	static const fvec2 calculateAverage(const vector<fvec2> & values);
	static const fvec2 calculateDifference(const fvec2 & firstPosition, const fvec2 & secondPosition);
	static const fvec2 normalize(const fvec2 & vector);

	static const float calculateDeterminant(const fmat22 & matrix);
	static const float calculateDeterminant(const fmat33 & matrix);
	static const float calculateDeterminant(const fmat44 & matrix);
	static const float calculateDistance(const fvec2 & firstPosition, const fvec2 & secondPosition);
	static const float calculateDistance(const fvec3 & firstPosition, const fvec3 & secondPosition);
	static const float calculateDistance(const fvec4 & firstPosition, const fvec4 & secondPosition);
	static const float calculateDotProduct(const fvec2 & firstVector, const fvec2 & secondVector);
	static const float calculateDotProduct(const fvec3 & firstVector, const fvec3 & secondVector);
	static const float calculateDotProduct(const fvec4 & firstVector, const fvec4 & secondVector);
	static const float calculateMagnitude(const fvec2 & vector);
	static const float calculateMagnitude(const fvec3 & vector);
	static const float calculateMagnitude(const fvec4 & vector);
	static const float calculateAngleDifference(float firstAngle, float secondAngle);
	static const float calculateReferenceAngle(float angle);
	static const float calculateAverage(const vector<float> & values);
	static const float limitAngle(float angle);
	static const float convertToRadians(float degrees);
	static const float convertToDegrees(float radians);
	static const float getPi();
	static const float getRandomNumber(float min, float max);

	static const int calculateAverage(const vector<int> & values);
	static const int getRandomNumber(int min, int max);

	static const bool isNormalized(const fvec2 & vector);
	static const bool isNormalized(const fvec3 & vector);
	static const bool isNormalized(const fvec4 & vector);

private:
	static inline constexpr float PI = 3.1415926f;
	static inline constexpr float DEG2RAD = 0.0174532f;
	static inline constexpr float RAD2DEG = 57.2957795f;

	static inline mt19937 _generator = mt19937(static_cast<unsigned int>(time(nullptr)));
};