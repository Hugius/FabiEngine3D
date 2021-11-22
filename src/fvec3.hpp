#pragma once

struct fvec2;
struct fvec3;
struct fvec4;
struct ivec2;
struct ivec3;
struct ivec4;

struct fvec3 final
{
	fvec3();
	fvec3(const fvec2& other);
	fvec3(const fvec3& other);
	fvec3(const fvec4& other);
	fvec3(const ivec2& other);
	fvec3(const ivec3& other);
	fvec3(const ivec4& other);
	fvec3(const float& value);
	fvec3(const float& x, const float& y, const float& z);

	// VOID
	void operator+=(const float& other);
	void operator-=(const float& other);
	void operator*=(const float& other);
	void operator/=(const float& other);
	void operator+=(const fvec3& other);
	void operator-=(const fvec3& other);
	void operator*=(const fvec3& other);
	void operator/=(const fvec3& other);

	// FVEC3
	const fvec3 operator+(const fvec3& other) const;
	const fvec3 operator-(const fvec3& other) const;
	const fvec3 operator*(const fvec3& other) const;
	const fvec3 operator/(const fvec3& other) const;
	const fvec3 operator+(const float& other) const;
	const fvec3 operator-(const float& other) const;
	const fvec3 operator*(const float& other) const;
	const fvec3 operator/(const float& other) const;
	const fvec3 operator-() const;

	// BOOL
	const bool operator==(const fvec3& other) const;
	const bool operator!=(const fvec3& other) const;

	// Miscellaneous
	union
	{
		float f[3];

		struct
		{
			float x;
			float y;
			float z;
		};

		struct
		{
			float r;
			float g;
			float b;
		};
	};
};