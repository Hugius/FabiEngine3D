#pragma once

#include "fvec2.hpp"
#include "mat33.hpp"
#include "mat44.hpp"

struct mat22 final
{
	mat22();
	mat22(const mat33& other);
	mat22(const mat44& other);
	mat22(const float value);
	mat22(const float m00, const float m01, const float m10, const float m11);

	// Matrices
	const mat22 operator+(const mat22& other) const;
	const mat22 operator-(const mat22& other) const;
	const mat22 operator*(const mat22& other) const;

	// Vectors
	const fvec2 operator*(const fvec2& other) const;

	// Miscellaneous
	union
	{
		float m[2][2];
		float f[4];
	};
};