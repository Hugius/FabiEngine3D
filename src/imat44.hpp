#pragma once

struct ivec4;
struct imat22;
struct imat33;
struct imat44;

struct imat44 final
{
	imat44();
	imat44(const imat22 & other);
	imat44(const imat33 & other);
	imat44(const imat44 & other);
	imat44(const int value);
	imat44(const int m00, const int m01, const int m02, const int m03, const int m10, const int m11, const int m12, const int m13, const int m20, const int m21, const int m22, const int m23, const int m30, const int m31, const int m32, const int m33);

	const imat44 operator+(const imat44 & other) const;
	const imat44 operator-(const imat44 & other) const;
	const imat44 operator*(const imat44 & other) const;

	const ivec4 operator*(const ivec4 & other) const;

	union
	{
		int m[4][4];
		int f[16];
	};
};