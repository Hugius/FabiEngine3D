#pragma once

#include <cmath>

struct Vec4;

struct Ivec4 final
{
	// Data access
	union
	{
		int f[4];

		struct
		{
			int x;
			int y;
			int z;
			int w;
		};
	};

	// Creation
	Ivec4();
	Ivec4(const Vec4& other);
	Ivec4(const int value);
	Ivec4(const int x, const int y, const int z, const int w);

	// Voids
	void operator+=(const Ivec4& other);
	void operator-=(const Ivec4& other);
	void operator*=(const Ivec4& other);
	void operator/=(const Ivec4& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const Ivec4 operator-() const;
	const Ivec4 operator+(const Ivec4& other) const;
	const Ivec4 operator-(const Ivec4& other) const;
	const Ivec4 operator*(const Ivec4& other) const;
	const Ivec4 operator/(const Ivec4& other) const;
	const Ivec4 operator+(const int& other) const;
	const Ivec4 operator-(const int& other) const;
	const Ivec4 operator*(const int& other) const;
	const Ivec4 operator/(const int& other) const;

	// Booleans
	const bool operator==(const Ivec4& other) const;
	const bool operator!=(const Ivec4& other) const;
};