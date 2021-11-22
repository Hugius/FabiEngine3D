#pragma once

struct ivec2;
struct ivec3;
struct ivec4;
struct fvec2;
struct fvec3;
struct fvec4;

struct ivec3 final
{
	ivec3();
	ivec3(const ivec2& other);
	ivec3(const ivec3& other);
	ivec3(const ivec4& other);
	ivec3(const fvec2& other);
	ivec3(const fvec3& other);
	ivec3(const fvec4& other);
	ivec3(const int& value);
	ivec3(const int& x, const int& y, const int& z);

	// VOID
	void operator+=(const ivec3& other);
	void operator-=(const ivec3& other);
	void operator*=(const ivec3& other);
	void operator/=(const ivec3& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// IVEC3
	const ivec3 operator-() const;
	const ivec3 operator+(const ivec3& other) const;
	const ivec3 operator-(const ivec3& other) const;
	const ivec3 operator*(const ivec3& other) const;
	const ivec3 operator/(const ivec3& other) const;
	const ivec3 operator+(const int& other) const;
	const ivec3 operator-(const int& other) const;
	const ivec3 operator*(const int& other) const;
	const ivec3 operator/(const int& other) const;

	// BOOL
	const bool operator==(const ivec3& other) const;
	const bool operator!=(const ivec3& other) const;

	// MISCELLANEOUS
	union
	{
		int f[3];

		struct
		{
			int x;
			int y;
			int z;
		};
	};
};