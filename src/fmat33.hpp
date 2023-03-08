#pragma once

struct fvec3;
struct fmat22;
struct fmat33;
struct mat44;

struct fmat33 final
{
	fmat33();
	fmat33(const fmat22 & other);
	fmat33(const fmat33 & other);
	fmat33(const mat44 & other);
	fmat33(const float value);
	fmat33(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12, const float m20, const float m21, const float m22);

	const fmat33 operator+(const fmat33 & other) const;
	const fmat33 operator-(const fmat33 & other) const;
	const fmat33 operator*(const fmat33 & other) const;

	const fvec3 operator*(const fvec3 & other) const;

	union
	{
		float m[3][3];
		float f[9];
	};
};