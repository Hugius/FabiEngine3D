#pragma once

#include <cmath>

struct Vec3;

struct Ivec3
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

	// Operators
	Ivec3 operator-() const;

	Ivec3 operator+(const Ivec3& other) const;
	Ivec3 operator-(const Ivec3& other) const;
	Ivec3 operator*(const Ivec3& other) const;
	Ivec3 operator/(const Ivec3& other) const;

	Ivec3 operator+(const int& other) const;
	Ivec3 operator-(const int& other) const;
	Ivec3 operator*(const int& other) const;
	Ivec3 operator/(const int& other) const;

	void operator+=(const Ivec3& other);
	void operator-=(const Ivec3& other);
	void operator*=(const Ivec3& other);
	void operator/=(const Ivec3& other);

	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	bool operator==(const Ivec3& other) const;
	bool operator!=(const Ivec3& other) const;
};