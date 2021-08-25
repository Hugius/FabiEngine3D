#pragma once

#include <cmath>

struct Ivec2;

struct Vec2 final
{
	// Data access
	union
	{
		float f[2];

		struct
		{
			float x;
			float y;
		};
	};

	// Creation
	Vec2();
	Vec2(const Ivec2& other);
	Vec2(float xy);
	Vec2(float x, float y);

	// Voids
	void normalize();
	void clear();
	void operator+=(const Vec2& v);
	void operator-=(const Vec2& v);
	void operator*=(const Vec2& v);
	void operator/=(const Vec2& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	// Vectors
	const Vec2 operator-() const;
	const Vec2 operator+(const Vec2& v) const;
	const Vec2 operator-(const Vec2& v) const;
	const Vec2 operator*(const Vec2& v) const;
	const Vec2 operator/(const Vec2& v) const;
	const Vec2 operator+(const float& value) const;
	const Vec2 operator-(const float& value) const;
	const Vec2 operator*(const float& value) const;
	const Vec2 operator/(const float& value) const;

	// Floats
	const float getMagnitude();

	// Booleans
	const bool operator==(const Vec2& other) const;
	const bool operator!=(const Vec2& other) const;
};