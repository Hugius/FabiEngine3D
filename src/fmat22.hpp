#pragma once

struct fvec2;
struct fmat22;
struct mat33;
struct mat44;

struct fmat22 final
{
	fmat22();
	fmat22(const fmat22 & other);
	fmat22(const mat33 & other);
	fmat22(const mat44 & other);
	fmat22(const float value);
	fmat22(const float m00, const float m01, const float m10, const float m11);

	const fmat22 operator+(const fmat22 & other) const;
	const fmat22 operator-(const fmat22 & other) const;
	const fmat22 operator*(const fmat22 & other) const;

	const fvec2 operator*(const fvec2 & other) const;

	union
	{
		float m[2][2];
		float f[4];
	};
};