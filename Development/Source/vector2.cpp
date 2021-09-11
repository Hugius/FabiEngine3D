#include "vector2.hpp"
#include "ivector2.hpp"

Vec2::Vec2()
{
	this->x = 0;
	this->y = 0;
}

Vec2::Vec2(const Ivec2& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
}

Vec2::Vec2(const float value)
{
	this->x = value;
	this->y = value;
}

Vec2::Vec2(const float x, const float y) {
	this->x = x;
	this->y = y;
}

void Vec2::operator+=(const Vec2& v)
{
	this->x += v.x;
	this->y += v.y;
}

void Vec2::operator-=(const Vec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void Vec2::operator*=(const Vec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void Vec2::operator/=(const Vec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

void Vec2::operator+=(const float& value)
{
	this->x += value;
	this->y += value;
}

void Vec2::operator-=(const float& value)
{
	this->x -= value;
	this->y -= value;
}

void Vec2::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
}

void Vec2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
}

const Vec2 Vec2::operator-() const
{
	return Vec2(-this->x, -this->y);
}

const Vec2 Vec2::operator+(const Vec2& v)const
{
	return Vec2(this->x + v.x, this->y + v.y);
}

const Vec2 Vec2::operator-(const Vec2& v)const
{
	return Vec2(this->x - v.x, this->y - v.y);
}

const Vec2 Vec2::operator*(const Vec2& v)const
{
	return Vec2(this->x * v.x, this->y * v.y);
}

const Vec2 Vec2::operator/(const Vec2& v)const
{
	return Vec2(this->x / v.x, this->y / v.y);
}

const Vec2 Vec2::operator+(const float& value)const
{
	return Vec2(this->x + value, this->y + value);
}

const Vec2 Vec2::operator-(const float& value)const
{
	return Vec2(this->x - value, this->y - value);
}

const Vec2 Vec2::operator/(const float& value)const
{
	return Vec2(this->x / value, this->y / value);
}

const Vec2 Vec2::operator*(const float& value)const
{
	return Vec2(this->x * value, this->y * value);
}

const bool Vec2::operator==(const Vec2& other) const
{
	return (this->x == other.x && this->y == other.y);
}

const bool Vec2::operator!=(const Vec2& other) const
{
	return (this->x != other.x || this->y != other.y);
}