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
	// Floats
	static float getPI();
	static float convertToRadians(float degrees);
	static float convertToDegrees(float radians);
	static float calculateReferenceAngle(float initialAngle);
	static float calculateAbsoluteDistance(Vec3 firstPosition, Vec3 secondPosition);
	static float calculateDotProduct(Vec2 firstVector, Vec2 secondVector);
	static float calculateDotProduct(Vec3 firstVector, Vec3 secondVector);
	static float calculateDotProduct(Vec4 firstVector, Vec4 secondVector);

private:
	// Floats
	static inline const float PI = 3.14159265358979323846264338327f;
	static inline const float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline const float RAD2DEG = 57.295779513082320876798154814278f;
};