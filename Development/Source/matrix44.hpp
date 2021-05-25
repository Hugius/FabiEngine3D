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
		struct
		{
			Vec3 xAxis;
			float wx;
			Vec3 yAxis;
			float wy;
			Vec3 zAxis;
			float wz;
			Vec3 translation;
			float one;
		};
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

	// Operators
	float operator[](unsigned int index) const;
	Vec4 operator*(const Vec4& other) const;
	Vec3 operator*(const Vec3& other) const;
	Matrix44 operator+(const Matrix44& other) const;
	Matrix44 operator-(const Matrix44& other) const;
	Matrix44 operator*(const Matrix44& other) const;

	// Axes
	Vec3 GetXAxis() const;
	Vec3 GetYAxis() const;
	Vec3 GetZAxis() const;

	// Application
	float getDeterminant() const;
	bool invert();
	void transpose();
	void SetEulerAxis(float yaw, float pitch, float roll);

	// Static creations
	static Matrix44 createTranslation(float x, float y, float z);
	static Matrix44 createScaling(float x, float y, float z);
	static Matrix44 createRotation(float x, float y, float z);
	static Matrix44 createRotationX(float angle);
	static Matrix44 createRotationY(float angle);
	static Matrix44 createRotationZ(float angle);
	static Matrix44 createOrtho(float left, float right, float bottom, float top, float nearZ, float farZ);
	static Matrix44 createProjection(float fovY, float aspect, float nearZ, float farZ);
	static Matrix44 createView(const Vec3& eye, const Vec3& center, const Vec3& up);
};