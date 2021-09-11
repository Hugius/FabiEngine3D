#pragma once

#include <cmath>

struct Ivec3;

struct Vec3 final
{
	// Data access
	union
	{
		float f[3];

		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
	};

	// Creation
	Vec3();
	Vec3(const Ivec3& other);
	Vec3(const float value);
	Vec3(const float x, const float y, const float z);

	// Voids
	void operator+=(const float& other);
	void operator-=(const float& other);
	void operator*=(const float& other);
	void operator/=(const float& other);
	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);
	void operator*=(const Vec3& other);
	void operator/=(const Vec3& other);

	// Vectors
	const Vec3 operator+(const Vec3& other) const;
	const Vec3 operator-(const Vec3& other) const;
	const Vec3 operator*(const Vec3& other) const;
	const Vec3 operator/(const Vec3& other) const;
	const Vec3 operator+(const float& other) const;
	const Vec3 operator-(const float& other) const;
	const Vec3 operator*(const float& other) const;
	const Vec3 operator/(const float& other) const;
	const Vec3 operator-() const;

	// Booleans
	const bool operator==(const Vec3& other) const;
	const bool operator!=(const Vec3& other) const;
};
