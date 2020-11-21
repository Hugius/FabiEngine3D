#include "ivector2.hpp"
#include "vector2.hpp"

Ivec2::Ivec2()
{
	this->x = 0;
	this->y = 0;
}

Ivec2::Ivec2(const Vec2& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
}

Ivec2::Ivec2(int xy)
{
	this->x = xy;
	this->y = xy;
}

Ivec2::Ivec2(int x, int y) {
	this->x = x;
	this->y = y;
}

void Ivec2::operator+=(const Ivec2 & v)
{
	this->x += v.x;
	this->y += v.y;
}

void Ivec2::operator-=(const Ivec2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void Ivec2::operator*=(const Ivec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void Ivec2::operator/=(const Ivec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

void Ivec2::operator+=(const int& value)
{
	this->x += value;
	this->y += value;
}

void Ivec2::operator-=(const int& value)
{
	this->x -= value;
	this->y -= value;
}

void Ivec2::operator/=(const int & value)
{
	this->x /= value;
	this->y /= value;
}

void Ivec2::operator*=(const int & value)
{
	this->x *= value;
	this->y *= value;
}

Ivec2 Ivec2::operator-() const
{
	return Ivec2(-this->x, -this->y);
}

Ivec2 Ivec2::operator+(const Ivec2 & v) const
{
	return Ivec2(this->x + v.x, this->y + v.y);
}

Ivec2 Ivec2::operator-(const Ivec2 & v) const
{
	return Ivec2(this->x - v.x, this->y - v.y);
}

Ivec2 Ivec2::operator*(const Ivec2& v) const
{
	return Ivec2(this->x * v.x, this->y * v.y);
}

Ivec2 Ivec2::operator/(const Ivec2& v) const
{
	return Ivec2(this->x / v.x, this->y / v.y);
}

Ivec2 Ivec2::operator+(const int& value) const
{
	return Ivec2(this->x + value, this->y + value);
}

Ivec2 Ivec2::operator-(const int& value) const
{
	return Ivec2(this->x - value, this->y - value);
}

Ivec2 Ivec2::operator/(const int & value) const
{
	return Ivec2(this->x / value, this->y / value);
}

Ivec2 Ivec2::operator*(const int & value) const
{
	return Ivec2(this->x * value, this->y * value);
}

bool Ivec2::operator==(const Ivec2 & other) const
{
	return (this->x == other.x && this->y == other.y);
}

bool Ivec2::operator!=(const Ivec2 & other) const
{
	return (this->x != other.x || this->y != other.y);
}