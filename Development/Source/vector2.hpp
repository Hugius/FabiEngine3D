#pragma once

#include <cmath>

struct Ivec2;

struct Vec2
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

	// Applications
	float dot(const Vec2& v);
	float magnitude() const;
	void normalize();

	// Operators
	Vec2 operator-() const;

	Vec2 operator+(const Vec2& v) const;
	Vec2 operator-(const Vec2& v) const;
	Vec2 operator*(const Vec2& v) const;
	Vec2 operator/(const Vec2& v) const;

	Vec2 operator+(const float& value) const;
	Vec2 operator-(const float& value) const;
	Vec2 operator*(const float& value) const;
	Vec2 operator/(const float& value) const;

	void operator+=(const Vec2& v);
	void operator-=(const Vec2& v);
	void operator*=(const Vec2& v);
	void operator/=(const Vec2& v);

	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	bool operator==(const Vec2& other) const;
	bool operator!=(const Vec2& other) const;
};