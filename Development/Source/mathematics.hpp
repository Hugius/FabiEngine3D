#pragma once

#include "ivector2.hpp"
#include "ivector3.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix33.hpp"
#include "matrix44.hpp"

class Math final
{
public:
	// Matrices
	static const Matrix33 invertMatrix(Matrix33 matrix);
	static const Matrix44 invertMatrix(Matrix44 matrix);
	static const Matrix33 transposeMatrix(Matrix33 matrix);
	static const Matrix44 transposeMatrix(Matrix44 matrix);
	static const Matrix44 createTranslationMatrix(float x, float y, float z);
	static const Matrix44 createRotationMatrix(float x, float y, float z);
	static const Matrix44 createRotationMatrixX(float angle);
	static const Matrix44 createRotationMatrixY(float angle);
	static const Matrix44 createRotationMatrixZ(float angle);
	static const Matrix44 createScalingMatrix(float x, float y, float z);
	static const Matrix44 createOrthoMatrix(float left, float right, float bottom, float top, float nearZ, float farZ);
	static const Matrix44 createViewMatrix(Vec3 eye, Vec3 center, Vec3 up);
	static const Matrix44 createProjectionMatrix(float fovY, float aspect, float nearZ, float farZ);

	// Vectors
	static const Vec3 calculateCrossProduct(Vec3 firstVector, Vec3 secondVector);
	static const Vec2 calculateVectorDifference(Vec2 firstPosition, Vec2 secondPosition);
	static const Vec3 calculateVectorDifference(Vec3 firstPosition, Vec3 secondPosition);
	static const Vec4 calculateVectorDifference(Vec4 firstPosition, Vec4 secondPosition);
	static const Vec2 normalizeVector(Vec2 vector);
	static const Vec3 normalizeVector(Vec3 vector);
	static const Vec4 normalizeVector(Vec4 vector);

	// Floats
	static const float calculateDeterminant(Matrix33 matrix);
	static const float calculateDeterminant(Matrix44 matrix);
	static const float calculateVectorDistance(Vec2 firstPosition, Vec2 secondPosition);
	static const float calculateVectorDistance(Vec3 firstPosition, Vec3 secondPosition);
	static const float calculateVectorDistance(Vec4 firstPosition, Vec4 secondPosition);
	static const float calculateDotProduct(Vec2 firstVector, Vec2 secondVector);
	static const float calculateDotProduct(Vec3 firstVector, Vec3 secondVector);
	static const float calculateDotProduct(Vec4 firstVector, Vec4 secondVector);
	static const float calculateVectorMagnitude(Vec2 vector);
	static const float calculateVectorMagnitude(Vec3 vector);
	static const float calculateVectorMagnitude(Vec4 vector);
	static const float calculateAngleDifference(float firstAngle, float secondAngle);
	static const float calculateReferenceAngle(float initialAngle);
	static const float convertToRadians(float degrees);
	static const float convertToDegrees(float radians);
	static const float getPI();

private:
	// Floats
	static inline const float PI = 3.14159265358979323846264338327f;
	static inline const float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline const float RAD2DEG = 57.295779513082320876798154814278f;
};