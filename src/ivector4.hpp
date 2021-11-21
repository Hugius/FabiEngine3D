#pragma once

#include <cmath>

struct fvec4;

struct Ivec4 final
{
	Ivec4();
	Ivec4(const fvec4& other);
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

	// Miscellaneous
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
};