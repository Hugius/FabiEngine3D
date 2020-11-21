#pragma once

#include <cmath>

struct Vec2;

struct Ivec2
{
	// Data access
	union
	{
		int f[2];

		struct
		{
			int x;
			int y;
		};
	};

	// Creation
	Ivec2();
	Ivec2(const Vec2& other);
	Ivec2(int xy);
	Ivec2(int x, int y);

	// Operators
	Ivec2 operator-() const;

	Ivec2 operator+(const Ivec2& other) const;
	Ivec2 operator-(const Ivec2& other) const;
	Ivec2 operator*(const Ivec2& other) const;
	Ivec2 operator/(const Ivec2& other) const;

	Ivec2 operator+(const int& other) const;
	Ivec2 operator-(const int& other) const;
	Ivec2 operator*(const int& other) const;
	Ivec2 operator/(const int& other) const;

	void operator+=(const Ivec2& other);
	void operator-=(const Ivec2& other);
	void operator*=(const Ivec2& other);
	void operator/=(const Ivec2& other);

	void operator+=(const int& other);
	void operator-=(const int& other);
	void operator/=(const int& other);
	void operator*=(const int& other);

	bool operator==(const Ivec2& other) const;
	bool operator!=(const Ivec2& other) const;
};