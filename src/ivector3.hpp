#pragma once

#include <cmath>

struct fvec3;

struct ivec3 final
{
	ivec3();
	ivec3(const fvec3& other);
	ivec3(const int value);
	ivec3(const int x, const int y, const int z);

	// Voids
	void operator+=(const ivec3& other);
	void operator-=(const ivec3& other);
	void operator*=(const ivec3& other);
	void operator/=(const ivec3& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const ivec3 operator-() const;
	const ivec3 operator+(const ivec3& other) const;
	const ivec3 operator-(const ivec3& other) const;
	const ivec3 operator*(const ivec3& other) const;
	const ivec3 operator/(const ivec3& other) const;
	const ivec3 operator+(const int& other) const;
	const ivec3 operator-(const int& other) const;
	const ivec3 operator*(const int& other) const;
	const ivec3 operator/(const int& other) const;

	// Booleans
	const bool operator==(const ivec3& other) const;
	const bool operator!=(const ivec3& other) const;

	// Miscellaneous
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
};