#pragma once

struct imat22;
struct imat33;
struct imat44;
struct fmat22;
struct fmat33;
struct fmat44;
struct fvec2;

struct fmat22 final
{
	fmat22();
	fmat22(const float value);
	fmat22(const float m00, const float m01, const float m10, const float m11);
	fmat22(const imat22 & other);
	fmat22(const imat33 & other);
	fmat22(const imat44 & other);
	fmat22(const fmat22 & other);
	fmat22(const fmat33 & other);
	fmat22(const fmat44 & other);

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