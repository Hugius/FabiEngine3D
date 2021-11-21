#pragma once

#include "ivec2.hpp"

struct fvec2 final
{
	fvec2();
	fvec2(const ivec2& other);
	fvec2(const float value);
	fvec2(const float x, const float y);

	// Voids
	void operator+=(const fvec2& v);
	void operator-=(const fvec2& v);
	void operator*=(const fvec2& v);
	void operator/=(const fvec2& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	// Vectors
	const fvec2 operator-() const;
	const fvec2 operator+(const fvec2& v) const;
	const fvec2 operator-(const fvec2& v) const;
	const fvec2 operator*(const fvec2& v) const;
	const fvec2 operator/(const fvec2& v) const;
	const fvec2 operator+(const float& value) const;
	const fvec2 operator-(const float& value) const;
	const fvec2 operator*(const float& value) const;
	const fvec2 operator/(const float& value) const;

	// Booleans
	const bool operator==(const fvec2& other) const;
	const bool operator!=(const fvec2& other) const;

	// Miscellaneous
	union
	{
		float f[2];

		struct
		{
			float x;
			float y;
		};
	};
};