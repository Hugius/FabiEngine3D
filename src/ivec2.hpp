#pragma once

struct ivec2;
struct ivec3;
struct ivec4;
struct fvec2;
struct fvec3;
struct fvec4;

struct ivec2 final
{
	ivec2();
	ivec2(const ivec2& other);
	ivec2(const ivec3& other);
	ivec2(const ivec4& other);
	ivec2(const fvec2& other);
	ivec2(const fvec3& other);
	ivec2(const fvec4& other);
	ivec2(const int& value);
	ivec2(const int& x, const int& y);

	// VOID
	void operator+=(const ivec2& other);
	void operator-=(const ivec2& other);
	void operator*=(const ivec2& other);
	void operator/=(const ivec2& other);
	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	// IVEC2
	const ivec2 operator-() const;
	const ivec2 operator+(const ivec2& other) const;
	const ivec2 operator-(const ivec2& other) const;
	const ivec2 operator*(const ivec2& other) const;
	const ivec2 operator/(const ivec2& other) const;
	const ivec2 operator+(const int& other) const;
	const ivec2 operator-(const int& other) const;
	const ivec2 operator*(const int& other) const;
	const ivec2 operator/(const int& other) const;

	// BOOL
	const bool operator==(const ivec2& other) const;
	const bool operator!=(const ivec2& other) const;

	// Miscellaneous
	union
	{
		int f[2];

		struct
		{
			int x;
			int y;
		};
	};
};