#pragma once

#include <cmath>

struct Vec3;

struct Ivec3 final
{
	// Data access
	union
	{
		int f[3];

		struct
		{
			int x;
			int y;
			int z;
		};
	};

	// Creation
	Ivec3();
	Ivec3(const Vec3& other);
	Ivec3(int xyz);
	Ivec3(int x, int y, int z);

	// Voids
	void operator+=(const Ivec3& other);
	void operator-=(const Ivec3& other);
	void operator*=(const Ivec3& other);
	void operator/=(const Ivec3& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const Ivec3 operator-() const;
	const Ivec3 operator+(const Ivec3& other) const;
	const Ivec3 operator-(const Ivec3& other) const;
	const Ivec3 operator*(const Ivec3& other) const;
	const Ivec3 operator/(const Ivec3& other) const;
	const Ivec3 operator+(const int& other) const;
	const Ivec3 operator-(const int& other) const;
	const Ivec3 operator*(const int& other) const;
	const Ivec3 operator/(const int& other) const;

	// Booleans
	const bool operator==(const Ivec3& other) const;
	const bool operator!=(const Ivec3& other) const;
};