#pragma once

#include "ivec2.hpp"
#include "ivec3.hpp"
#include "ivec4.hpp"
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"
#include "mat22.hpp"
#include "mat33.hpp"
#include "mat44.hpp"
#include "direction_order.hpp"

#include <vector>
#include <random>
#include <ctime>

using std::vector;
using std::mt19937;

class Mathematics final
{
public:
	Mathematics() = delete;

	static const vector<float> calculateDistributedPositions(unsigned int count, float size, bool isAscending);

	static const mat44 createTranslationMatrix(float x, float y, float z);
	static const mat44 createTranslationMatrixX(float value);
	static const mat44 createTranslationMatrixY(float value);
	static const mat44 createTranslationMatrixZ(float value);
	static const mat44 createRotationMatrix(float x, float y, float z, DirectionOrder order);
	static const mat44 createRotationMatrixX(float angle);
	static const mat44 createRotationMatrixY(float angle);
	static const mat44 createRotationMatrixZ(float angle);
	static const mat44 createScalingMatrix(float x, float y, float z);
	static const mat44 createScalingMatrixX(float value);
	static const mat44 createScalingMatrixY(float value);
	static const mat44 createScalingMatrixZ(float value);
	static const mat44 createViewMatrix(const fvec3 & eye, const fvec3 & center, const fvec3 & up);
	static const mat44 createOrthographicProjectionMatrix(float leftZ, float rightZ, float bottomZ, float topZ, float nearZ, float farZ);
	static const mat44 createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far);
	static const mat44 invertMatrix(const mat44 & matrix);
	static const mat44 transposeMatrix(const mat44 & matrix);

	static const mat33 invertMatrix(const mat33 & matrix);
	static const mat33 transposeMatrix(const mat33 & matrix);

	static const mat22 invertMatrix(const mat22 & matrix);

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

	static const float calculateDeterminant(const mat22 & matrix);
	static const float calculateDeterminant(const mat33 & matrix);
	static const float calculateDeterminant(const mat44 & matrix);
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
	static const float getPI();
	static const float getRandomNumber(float min, float max);

	static const unsigned int calculateAverage(const vector<unsigned int> & values);
	static const unsigned int getRandomNumber(unsigned int min, unsigned int max);

	static const int calculateAverage(const vector<int> & values);
	static const int getRandomNumber(int min, int max);

	static const bool isNormalized(const fvec2 & vector);
	static const bool isNormalized(const fvec3 & vector);
	static const bool isNormalized(const fvec4 & vector);

private:
	static inline constexpr float PI = 3.14159265358979323846264338327f;
	static inline constexpr float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline constexpr float RAD2DEG = 57.295779513082320876798154814278f;

	static inline mt19937 _generator = mt19937(static_cast<unsigned int>(time(nullptr)));
};