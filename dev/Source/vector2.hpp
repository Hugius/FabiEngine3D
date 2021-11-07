#pragma once

#include <cmath>

struct Ivec2;

struct Vec2 final
{
	Vec2();
	Vec2(const Ivec2& other);
	Vec2(const float value);
	Vec2(const float x, const float y);

	// Voids
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

	// Booleans
	const bool operator==(const Vec2& other) const;
	const bool operator!=(const Vec2& other) const;

	// Miscellaneous
	union
	{
		float f[2];

		struct
		{
			float x;
			float y;
		};
	};
};