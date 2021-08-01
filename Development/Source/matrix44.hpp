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

	// Voids
	void transpose();
	void setEulerAxis(float yaw, float pitch, float roll);
	
	// Matrices
	static const Matrix44 createTranslation(float x, float y, float z);
	static const Matrix44 createRotation(float x, float y, float z);
	static const Matrix44 createRotationX(float angle);
	static const Matrix44 createRotationY(float angle);
	static const Matrix44 createRotationZ(float angle);
	static const Matrix44 createScaling(float x, float y, float z);
	static const Matrix44 createOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
	static const Matrix44 createProjection(float fovY, float aspect, float nearZ, float farZ);
	static const Matrix44 createView(const Vec3& eye, const Vec3& center, const Vec3& up);
	const Matrix44 operator+(const Matrix44& other) const;
	const Matrix44 operator-(const Matrix44& other) const;
	const Matrix44 operator*(const Matrix44& other) const;

	// Vectors
	const Vec4 operator*(const Vec4& other) const;
	const Vec3 operator*(const Vec3& other) const;
	const Vec3 getXAxis();
	const Vec3 getYAxis();
	const Vec3 getZAxis();

	// Floats
	const float operator[](unsigned int index) const;
	const float getDeterminant();
	
	// Booleans
	const bool invert();
};