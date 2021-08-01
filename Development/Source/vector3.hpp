#pragma once

#include <cmath>

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
	Vec3(float xyz);
	Vec3(float x, float y, float z);

	// Voids
	void normalize();
	void clear();
	void operator+=(const float& other);
	void operator-=(const float& other);
	void operator*=(const float& other);
	void operator/=(const float& other);
	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);
	void operator*=(const Vec3& other);
	void operator/=(const Vec3& other);

	// Vectors
	const Vec3 cross(const Vec3& vector) const;
	const Vec3 operator+(const Vec3& other) const;
	const Vec3 operator-(const Vec3& other) const;
	const Vec3 operator*(const Vec3& other) const;
	const Vec3 operator/(const Vec3& other) const;
	const Vec3 operator+(const float& other) const;
	const Vec3 operator-(const float& other) const;
	const Vec3 operator*(const float& other) const;
	const Vec3 operator/(const float& other) const;
	const Vec3 operator-() const;

	// Floats
	const float dot(const Vec3& vector);
	const float getMagnitude();

	// Booleans
	const bool operator==(const Vec3& other) const;
	const bool operator!=(const Vec3& other) const;
};
