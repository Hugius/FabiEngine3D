#pragma once

struct ivec2;
struct imat22;
struct imat33;
struct imat44;
struct fmat22;
struct fmat33;
struct fmat44;

struct imat22 final
{
	imat22();
	imat22(const imat22 & other);
	imat22(const imat33 & other);
	imat22(const imat44 & other);
	imat22(const fmat22 & other);
	imat22(const fmat33 & other);
	imat22(const fmat44 & other);
	imat22(const int value);
	imat22(const int m00, const int m01, const int m10, const int m11);

	const imat22 operator+(const imat22 & other) const;
	const imat22 operator-(const imat22 & other) const;
	const imat22 operator*(const imat22 & other) const;

	const ivec2 operator*(const ivec2 & other) const;

	union
	{
		int m[2][2];
		int f[4];
	};
};