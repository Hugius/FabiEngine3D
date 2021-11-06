#pragma once

#include "vector4.hpp"

struct Matrix33;

struct Matrix44 final
{
	Matrix44();
	Matrix44(const Matrix33& other);
	Matrix44(const float value);
	Matrix44
	(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23,
		const float m30, const float m31, const float m32, const float m33
	);

	// Matrices
	const Matrix44 operator+(const Matrix44& other) const;
	const Matrix44 operator-(const Matrix44& other) const;
	const Matrix44 operator*(const Matrix44& other) const;

	// Vectors
	const Vec4 operator*(const Vec4& other) const;

	// Miscellaneous
	union
	{
		float m[4][4];
		float f[16];
	};
};