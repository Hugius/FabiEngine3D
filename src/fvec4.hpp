#pragma once

#include "ivec4.hpp"

struct fvec4 final
{
	fvec4();
	fvec4(const ivec4& other);
	fvec4(const float value);
	fvec4(const float x, const float y, const float z, const float w);

	// Voids
	void operator+=(const fvec4& v);
	void operator-=(const fvec4& v);
	void operator*=(const fvec4& v);
	void operator/=(const fvec4& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	// Vectors
	const fvec4 operator-() const;
	const fvec4 operator+(const fvec4& v) const;
	const fvec4 operator-(const fvec4& v) const;
	const fvec4 operator*(const fvec4& v) const;
	const fvec4 operator/(const fvec4& v) const;
	const fvec4 operator+(const float& value) const;
	const fvec4 operator-(const float& value) const;
	const fvec4 operator/(const float& value) const;
	const fvec4 operator*(const float& value) const;

	// Booleans
	const bool operator==(const fvec4& other) const;
	const bool operator!=(const fvec4& other) const;

	// Miscellaneous
	union
	{
		float f[4];

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};
};