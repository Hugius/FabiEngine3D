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
	static inline float degreesToRadians(float angle)
	{
		return (angle * DEG2RAD);
	}

	static inline float radiansToDegrees(float angle)
	{
		return (angle * RAD2DEG);
	}
	
	static inline float getPI()
	{
		return PI;
	}

	static inline float calculateReferenceAngle(float initialAngle)
	{
		if (initialAngle >= 0.0f && initialAngle <= 90.0f)
		{
			return initialAngle;
		}
		else if (initialAngle > 90.0f && initialAngle <= 180.0f)
		{
			return 180.0f - initialAngle;
		}
		else if (initialAngle > 180.0f && initialAngle <= 270.0f)
		{
			return initialAngle - 180.0f;
		}
		else
		{
			return 360.0f - initialAngle;
		}
	}

private:
	static inline const float PI = 3.14159265358979323846264338327f;
	static inline const float DEG2RAD = 0.01745329251994329576923690768489f;
	static inline const float RAD2DEG = 57.295779513082320876798154814278f;
};