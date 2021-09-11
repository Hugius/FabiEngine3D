#pragma once

#include "vector2.hpp"

struct Matrix44;

struct Matrix33 final
{
	// Data access
	union
	{
		float m[3][3];
		float f[9];
	};

	// Creation
	Matrix33();
	Matrix33(const Matrix44& other);
	Matrix33(const float value);
	Matrix33
	(
		const float m00, const float m01, const float m02,
		const float m10, const float m11, const float m12,
		const float m20, const float m21, const float m22
	);

	// Matrices
	const Matrix33 operator+(const Matrix33& other) const;
	const Matrix33 operator-(const Matrix33& other) const;
	const Matrix33 operator*(const Matrix33& other) const;
};