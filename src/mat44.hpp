#pragma once

#include "fvec4.hpp"
#include "mat22.hpp"
#include "mat33.hpp"

struct mat44 final
{
	mat44();
	mat44(const mat22& other);
	mat44(const mat33& other);
	mat44(const float value);
	mat44
	(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33
	);

	// Matrices
	const mat44 operator+(const mat44& other) const;
	const mat44 operator-(const mat44& other) const;
	const mat44 operator*(const mat44& other) const;

	// Vectors
	const fvec4 operator*(const fvec4& other) const;

	// Miscellaneous
	union
	{
		float m[4][4];
		float f[16];
	};
};