#pragma once

#include "fvec3.hpp"
#include "mat22.hpp"
#include "mat44.hpp"

struct mat33 final
{
	mat33();
	mat33(const mat22& other);
	mat33(const mat44& other);
	mat33(const float value);
	mat33
	(
		const float m00, const float m01, const float m02,
		const float m10, const float m11, const float m12,
		const float m20, const float m21, const float m22
	);

	// Matrices
	const mat33 operator+(const mat33& other) const;
	const mat33 operator-(const mat33& other) const;
	const mat33 operator*(const mat33& other) const;

	// Vectors
	const fvec3 operator*(const fvec3& other) const;

	// Miscellaneous
	union
	{
		float m[3][3];
		float f[9];
	};
};