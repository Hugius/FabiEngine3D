#pragma once

struct fvec3;
struct mat22;
struct mat33;
struct mat44;

struct mat33 final
{
	mat33();
	mat33(const mat22& other);
	mat33(const mat33& other);
	mat33(const mat44& other);
	mat33(const float& value);
	mat33(const float& m00, const float& m01, const float& m02, const float& m10, const float& m11, const float& m12, const float& m20, const float& m21, const float& m22);

	const mat33 operator+(const mat33& other) const;
	const mat33 operator-(const mat33& other) const;
	const mat33 operator*(const mat33& other) const;

	const fvec3 operator*(const fvec3& other) const;

	union
	{
		float m[3][3];
		float f[9];
	};
};