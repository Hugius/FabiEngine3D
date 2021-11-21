#include "ivec2.hpp"
#include "ivec3.hpp"
#include "ivec4.hpp"
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"

ivec2::ivec2()
{
	this->x = 0;
	this->y = 0;
}

ivec2::ivec2(const ivec2& other)
{
	this->x = other.x;
	this->y = other.y;
}

ivec2::ivec2(const ivec3& other)
{
	this->x = other.x;
	this->y = other.y;
}

ivec2::ivec2(const ivec4& other)
{
	this->x = other.x;
	this->y = other.y;
}

ivec2::ivec2(const fvec2& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
}

ivec2::ivec2(const fvec3& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
}

ivec2::ivec2(const fvec4& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
}

ivec2::ivec2(const int& value)
{
	this->x = value;
	this->y = value;
}

ivec2::ivec2(const int& x, const int& y)
{
	this->x = x;
	this->y = y;
}

void ivec2::operator+=(const ivec2& v)
{
	this->x += v.x;
	this->y += v.y;
}

void ivec2::operator-=(const ivec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void ivec2::operator*=(const ivec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void ivec2::operator/=(const ivec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

void ivec2::operator+=(const int& value)
{
	this->x += value;
	this->y += value;
}

void ivec2::operator-=(const int& value)
{
	this->x -= value;
	this->y -= value;
}

void ivec2::operator/=(const int& value)
{
	this->x /= value;
	this->y /= value;
}

void ivec2::operator*=(const int& value)
{
	this->x *= value;
	this->y *= value;
}

const ivec2 ivec2::operator-() const
{
	return ivec2(-this->x, -this->y);
}

const ivec2 ivec2::operator+(const ivec2& v) const
{
	return ivec2((this->x + v.x), (this->y + v.y));
}

const ivec2 ivec2::operator-(const ivec2& v) const
{
	return ivec2((this->x - v.x), (this->y - v.y));
}

const ivec2 ivec2::operator*(const ivec2& v) const
{
	return ivec2((this->x * v.x), (this->y * v.y));
}

const ivec2 ivec2::operator/(const ivec2& v) const
{
	return ivec2((this->x / v.x), (this->y / v.y));
}

const ivec2 ivec2::operator+(const int& value) const
{
	return ivec2((this->x + value), (this->y + value));
}

const ivec2 ivec2::operator-(const int& value) const
{
	return ivec2((this->x - value), (this->y - value));
}

const ivec2 ivec2::operator/(const int& value) const
{
	return ivec2((this->x / value), (this->y / value));
}

const ivec2 ivec2::operator*(const int& value) const
{
	return ivec2((this->x * value), (this->y * value));
}

const bool ivec2::operator==(const ivec2& other) const
{
	return ((this->x == other.x) && (this->y == other.y));
}

const bool ivec2::operator!=(const ivec2& other) const
{
	return ((this->x != other.x) || (this->y != other.y));
}