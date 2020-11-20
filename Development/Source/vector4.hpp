#pragma once

#include <cmath>

struct Vec4
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
	Vec4(float xyzw);
	Vec4(float x, float y, float z, float w);

	// Applications
	void normalize();
	float getMagnitude() const;

	// Operators
	Vec4 operator-();

	Vec4 operator+(const Vec4& v) const;
	Vec4 operator-(const Vec4& v) const;
	Vec4 operator*(const Vec4& v) const;
	Vec4 operator/(const Vec4& v) const;

	Vec4 operator+(const float& value) const;
	Vec4 operator-(const float& value) const;
	Vec4 operator/(const float& value) const;
	Vec4 operator*(const float& value) const;

	void operator+=(const Vec4& v);
	void operator-=(const Vec4& v);
	void operator*=(const Vec4& v);
	void operator/=(const Vec4& v);

	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	bool operator==(const Vec4& other) const;
	bool operator!=(const Vec4& other) const;
};