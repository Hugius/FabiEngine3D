#pragma once

struct fvec2;
struct fvec3;
struct fvec4;
struct ivec2;
struct ivec3;
struct ivec4;

struct fvec4 final
{
	fvec4();
	fvec4(const fvec2& other);
	fvec4(const fvec3& other);
	fvec4(const fvec4& other);
	fvec4(const ivec2& other);
	fvec4(const ivec3& other);
	fvec4(const ivec4& other);
	fvec4(const float& value);
	fvec4(const float& x, const float& y, const float& z, const float& w);

	void operator+=(const fvec4& v);
	void operator-=(const fvec4& v);
	void operator*=(const fvec4& v);
	void operator/=(const fvec4& v);
	void operator+=(const float& value);
	void operator-=(const float& value);
	void operator/=(const float& value);
	void operator*=(const float& value);

	const fvec4 operator-() const;
	const fvec4 operator+(const fvec4& v) const;
	const fvec4 operator-(const fvec4& v) const;
	const fvec4 operator*(const fvec4& v) const;
	const fvec4 operator/(const fvec4& v) const;
	const fvec4 operator+(const float& value) const;
	const fvec4 operator-(const float& value) const;
	const fvec4 operator/(const float& value) const;
	const fvec4 operator*(const float& value) const;

	const bool operator==(const fvec4& other) const;
	const bool operator!=(const fvec4& other) const;

	union
	{
		float f[4];

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};

		struct
		{
			float r;
			float g;
			float b;
			float a;
		};
	};
};