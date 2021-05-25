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

	// Applications
	Vec3 cross(const Vec3& vector) const;
	float dot(const Vec3& vector) const;
	float getMagnitude() const;
	void normalize();
	void clear();

	// Operators
	Vec3 operator-() const;

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;

	Vec3 operator+(const float& other) const;
	Vec3 operator-(const float& other) const;
	Vec3 operator*(const float& other) const;
	Vec3 operator/(const float& other) const;

	void operator+=(const float& other);
	void operator-=(const float& other);
	void operator*=(const float& other);
	void operator/=(const float& other);

	void operator+=(const Vec3& other);
	void operator-=(const Vec3& other);
	void operator*=(const Vec3& other);
	void operator/=(const Vec3& other);

	bool operator==(const Vec3& other) const;
	bool operator!=(const Vec3& other) const;
};
