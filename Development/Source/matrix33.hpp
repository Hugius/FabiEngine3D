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
	Matrix33(float value);
	Matrix33
	(
		float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22
	);

	// Matrices
	const Matrix33 operator+(const Matrix33& other) const;
	const Matrix33 operator-(const Matrix33& other) const;
	const Matrix33 operator*(const Matrix33& other) const;
};