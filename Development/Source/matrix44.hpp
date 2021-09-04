#pragma once

#include "vector3.hpp"
#include "vector4.hpp"

struct Matrix33;

struct Matrix44 final
{
	// Data access
	union
	{
		float m[4][4];
		float f[16];
	};

	// Creation
	Matrix44();
	Matrix44(float value);
	Matrix44(const Matrix33& other);
	Matrix44
	(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);
	
	// Matrices
	const Matrix44 operator+(const Matrix44& other) const;
	const Matrix44 operator-(const Matrix44& other) const;
	const Matrix44 operator*(const Matrix44& other) const;

	// Vectors
	const Vec4 operator*(const Vec4& other) const;
	const Vec3 operator*(const Vec3& other) const;
};