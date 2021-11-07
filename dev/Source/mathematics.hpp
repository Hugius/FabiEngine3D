#pragma once

#include "ivector2.hpp"
#include "ivector3.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix33.hpp"
#include "matrix44.hpp"
#include "direction_order.hpp"

#include <vector>
#include <random>
#include <ctime>

using std::vector;
using std::mt19937;

class Math final
{
public:
	Math() = delete;

	// Matrices
	static const Matrix33 invertMatrix(Matrix33 matrix);
	static const Matrix44 invertMatrix(Matrix44 matrix);
	static const Matrix33 transposeMatrix(Matrix33 matrix);
	static const Matrix44 transposeMatrix(Matrix44 matrix);
	static const Matrix44 createTranslationMatrix(float x, float y, float z);
	static const Matrix44 createTranslationMatrixX(float value);
	static const Matrix44 createTranslationMatrixY(float value);
	static const Matrix44 createTranslationMatrixZ(float value);
	static const Matrix44 createRotationMatrix(float x, float y, float z, DirectionOrder order);
	static const Matrix44 createRotationMatrixX(float angle);
	static const Matrix44 createRotationMatrixY(float angle);
	static const Matrix44 createRotationMatrixZ(float angle);
	static const Matrix44 createScalingMatrix(float x, float y, float z);
	static const Matrix44 createScalingMatrixX(float value);
	static const Matrix44 createScalingMatrixY(float value);
	static const Matrix44 createScalingMatrixZ(float value);
	static const Matrix44 createOrthoMatrix(float left, float right, float bottom, float top, float near, float far);
	static const Matrix44 createViewMatrix(Vec3 eye, Vec3 center, Vec3 up);
	static const Matrix44 createProjectionMatrix(float fov, float aspect, float near, float far);

	// Vectors
	static const Vec2 calculateAverage(const vector<Vec2>& values);
	static const Vec3 calculateAverage(const vector<Vec3>& values);
	static const Vec4 calculateAverage(const vector<Vec4>& values);
	static const Vec3 calculateCrossProduct(Vec3 firstVector, Vec3 secondVector);
	static const Vec2 calculateDifference(Vec2 firstPosition, Vec2 secondPosition);
	static const Vec3 calculateDifference(Vec3 firstPosition, Vec3 secondPosition);
	static const Vec4 calculateDifference(Vec4 firstPosition, Vec4 secondPosition);
	static const Vec2 normalize(Vec2 vector);
	static const Vec3 normalize(Vec3 vector);
	static const Vec4 normalize(Vec4 vector);
	static const Vec2 convertFromNDC(Vec2 position);
	static const Vec2 convertToNDC(Vec2 position);

	// Decimals
	static const float calculateDeterminant(Matrix33 matrix);
	static const float calculateDeterminant(Matrix44 matrix);
	static const float calculateDistance(Vec2 firstPosition, Vec2 secondPosition);
	static const float calculateDistance(Vec3 firstPosition, Vec3 secondPosition);
	static const float calculateDistance(Vec4 firstPosition, Vec4 secondPosition);
	static const float calculateDotProduct(Vec2 firstVector, Vec2 secondVector);
	static const float calculateDotProduct(Vec3 firstVector, Vec3 secondVector);
	static const float calculateDotProduct(Vec4 firstVector, Vec4 secondVector);
	static const float calculateMagnitude(Vec2 vector);
	static const float calculateMagnitude(Vec3 vector);
	static const float calculateMagnitude(Vec4 vector);
	static const float calculateAngleDifference(float firstAngle, float secondAngle);
	static const float calculateReferenceAngle(float angle);
	static const float calculateAverage(const vector<float>& values);
	static const float limitAngle(float angle);
	static const float convertToRadians(float degrees);
	static const float convertToDegrees(float radians);
	static const float getPI();
	static const float getRandomFloat(float min, float max);

	// Integers
	static const int calculateAverage(const vector<int>& values);
	static const int getRandomInteger(int min, int max);

	// Booleans
	static const bool isNormalized(Vec2 vector);
	static const bool isNormalized(Vec3 vector);
	static const bool isNormalized(Vec4 vector);

private:
	// Decimals
	static inline const float PI = 3.14159265358979323846264338327f;
	static inline const float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline const float RAD2DEG = 57.295779513082320876798154814278f;

	// Miscellaneous
	static inline mt19937 _generator = mt19937(static_cast<unsigned int>(time(nullptr)));
};