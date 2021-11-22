#pragma once

struct fvec2;
struct fvec3;
struct fvec4;
struct ivec2;
struct ivec3;
struct ivec4;

struct fvec2 final
{
	fvec2();
	fvec2(const fvec2& other);
	fvec2(const fvec3& other);
	fvec2(const fvec4& other);
	fvec2(const ivec2& other);
	fvec2(const ivec3& other);
	fvec2(const ivec4& other);
	fvec2(const float& value);
	fvec2(const float& x, const float& y);

	// VOID
	void operator+=(const fvec2& v);
	void operator-=(const fvec2& v);
	void operator*=(const fvec2& v);
	void operator/=(const fvec2& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	// FVEC2
	const fvec2 operator-() const;
	const fvec2 operator+(const fvec2& v) const;
	const fvec2 operator-(const fvec2& v) const;
	const fvec2 operator*(const fvec2& v) const;
	const fvec2 operator/(const fvec2& v) const;
	const fvec2 operator+(const float& value) const;
	const fvec2 operator-(const float& value) const;
	const fvec2 operator*(const float& value) const;
	const fvec2 operator/(const float& value) const;

	// BOOL
	const bool operator==(const fvec2& other) const;
	const bool operator!=(const fvec2& other) const;

	// MISCELLANEOUS
	union
	{
		float f[2];

		struct
		{
			float x;
			float y;
		};
	};
};