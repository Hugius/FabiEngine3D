#include "vector2.hpp"
#include "ivector2.hpp"

fvec2::fvec2()
{
	this->x = 0;
	this->y = 0;
}

fvec2::fvec2(const ivec2& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
}

fvec2::fvec2(const float value)
{
	this->x = value;
	this->y = value;
}

fvec2::fvec2(const float x, const float y)
{
	this->x = x;
	this->y = y;
}

void fvec2::operator+=(const fvec2& v)
{
	this->x += v.x;
	this->y += v.y;
}

void fvec2::operator-=(const fvec2& v)
{
	this->x -= v.x;
	this->y -= v.y;
}

void fvec2::operator*=(const fvec2& v)
{
	this->x *= v.x;
	this->y *= v.y;
}

void fvec2::operator/=(const fvec2& v)
{
	this->x /= v.x;
	this->y /= v.y;
}

void fvec2::operator+=(const float& value)
{
	this->x += value;
	this->y += value;
}

void fvec2::operator-=(const float& value)
{
	this->x -= value;
	this->y -= value;
}

void fvec2::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
}

void fvec2::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
}

const fvec2 fvec2::operator-() const
{
	return fvec2(-this->x, -this->y);
}

const fvec2 fvec2::operator+(const fvec2& v)const
{
	return fvec2((this->x + v.x), (this->y + v.y));
}

const fvec2 fvec2::operator-(const fvec2& v)const
{
	return fvec2((this->x - v.x), (this->y - v.y));
}

const fvec2 fvec2::operator*(const fvec2& v)const
{
	return fvec2((this->x * v.x), (this->y * v.y));
}

const fvec2 fvec2::operator/(const fvec2& v)const
{
	return fvec2((this->x / v.x), (this->y / v.y));
}

const fvec2 fvec2::operator+(const float& value)const
{
	return fvec2((this->x + value), (this->y + value));
}

const fvec2 fvec2::operator-(const float& value)const
{
	return fvec2((this->x - value), (this->y - value));
}

const fvec2 fvec2::operator/(const float& value)const
{
	return fvec2((this->x / value), (this->y / value));
}

const fvec2 fvec2::operator*(const float& value)const
{
	return fvec2((this->x * value), (this->y * value));
}

const bool fvec2::operator==(const fvec2& other) const
{
	return ((this->x == other.x) && (this->y == other.y));
}

const bool fvec2::operator!=(const fvec2& other) const
{
	return ((this->x != other.x) || (this->y != other.y));
}