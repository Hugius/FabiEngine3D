#pragma once

struct fvec4;
struct imat22;
struct imat33;
struct imat44;
struct fmat22;
struct fmat33;
struct fmat44;

struct fmat44 final
{
	fmat44();
	fmat44(const imat22 & other);
	fmat44(const imat33 & other);
	fmat44(const imat44 & other);
	fmat44(const fmat22 & other);
	fmat44(const fmat33 & other);
	fmat44(const fmat44 & other);
	fmat44(const float value);
	fmat44(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11, const float m12, const float m13, const float m20, const float m21, const float m22, const float m23, const float m30, const float m31, const float m32, const float m33);

	const fmat44 operator+(const fmat44 & other) const;
	const fmat44 operator-(const fmat44 & other) const;
	const fmat44 operator*(const fmat44 & other) const;

	const fvec4 operator*(const fvec4 & other) const;

	union
	{
		float m[4][4];
		float f[16];
	};
};