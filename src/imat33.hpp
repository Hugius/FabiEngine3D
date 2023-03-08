#pragma once

struct ivec3;
struct imat22;
struct imat33;
struct imat44;

struct imat33 final
{
	imat33();
	imat33(const imat22 & other);
	imat33(const imat33 & other);
	imat33(const imat44 & other);
	imat33(const int value);
	imat33(const int m00, const int m01, const int m02, const int m10, const int m11, const int m12, const int m20, const int m21, const int m22);

	const imat33 operator+(const imat33 & other) const;
	const imat33 operator-(const imat33 & other) const;
	const imat33 operator*(const imat33 & other) const;

	const ivec3 operator*(const ivec3 & other) const;

	union
	{
		int m[3][3];
		int f[9];
	};
};