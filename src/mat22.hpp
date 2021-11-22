#pragma once

struct fvec2;
struct mat22;
struct mat33;
struct mat44;

struct mat22 final
{
	mat22();
	mat22(const mat22& other);
	mat22(const mat33& other);
	mat22(const mat44& other);
	mat22(const float& value);
	mat22(const float& m00, const float& m01, const float& m10, const float& m11);

	// MAT44
	const mat22 operator+(const mat22& other) const;
	const mat22 operator-(const mat22& other) const;
	const mat22 operator*(const mat22& other) const;

	// FVEC2
	const fvec2 operator*(const fvec2& other) const;

	// Miscellaneous
	union
	{
		float m[2][2];
		float f[4];
	};
};