#pragma once

#define PI		3.14159265358979323846264338327f
#define DEG2RAD 0.01745329251994329576923690768489f

class Math final
{
public:
	static inline float degreesToRadians(float angle)
	{
		return (angle * DEG2RAD);
	}

	static inline float getPI()
	{
		return PI;
	}
};