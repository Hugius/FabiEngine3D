#pragma once

#include "ivec3.hpp"
#include "ivec4.hpp"
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"

struct ivec2 final
{
	ivec2();
	ivec2(const ivec2& other);
	ivec2(const ivec3& other);
	ivec2(const ivec4& other);
	ivec2(const fvec2& other);
	ivec2(const fvec3& other);
	ivec2(const fvec4& other);
	ivec2(const int value);
	ivec2(const int x, const int y);

	// Voids
	void operator+=(const ivec2& other);
	void operator-=(const ivec2& other);
	void operator*=(const ivec2& other);
	void operator/=(const ivec2& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// Vectors
	const ivec2 operator-() const;
	const ivec2 operator+(const ivec2& other) const;
	const ivec2 operator-(const ivec2& other) const;
	const ivec2 operator*(const ivec2& other) const;
	const ivec2 operator/(const ivec2& other) const;
	const ivec2 operator+(const int& other) const;
	const ivec2 operator-(const int& other) const;
	const ivec2 operator*(const int& other) const;
	const ivec2 operator/(const int& other) const;

	// Booleans
	const bool operator==(const ivec2& other) const;
	const bool operator!=(const ivec2& other) const;

	// Miscellaneous
	union
	{
		int f[2];

		struct
		{
			int x;
			int y;
		};
	};
};