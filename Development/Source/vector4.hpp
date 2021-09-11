#pragma once

#include <cmath>

struct Ivec4;

struct Vec4 final
{
	// Data access
	union
	{
		float f[4];

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};

	// Creation
	Vec4();
	Vec4(const Ivec4& other);
	Vec4(const float value);
	Vec4(const float x, const float y, const float z, const float w);

	// Voids
	void operator+=(const Vec4& v);
	void operator-=(const Vec4& v);
	void operator*=(const Vec4& v);
	void operator/=(const Vec4& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	// Vectors
	const Vec4 operator-() const;
	const Vec4 operator+(const Vec4& v) const;
	const Vec4 operator-(const Vec4& v) const;
	const Vec4 operator*(const Vec4& v) const;
	const Vec4 operator/(const Vec4& v) const;
	const Vec4 operator+(const float& value) const;
	const Vec4 operator-(const float& value) const;
	const Vec4 operator/(const float& value) const;
	const Vec4 operator*(const float& value) const;

	// Booleans
	const bool operator==(const Vec4& other) const;
	const bool operator!=(const Vec4& other) const;
};