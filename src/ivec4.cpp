#include "ivec2.hpp"
#include "ivec3.hpp"
#include "ivec4.hpp"
#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"

ivec4::ivec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

ivec4::ivec4(const ivec2 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = 0;
	this->w = 0;
}

ivec4::ivec4(const ivec3 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = 0;
}

ivec4::ivec4(const ivec4 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
	this->w = other.w;
}

ivec4::ivec4(const fvec2 & other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = 0;
	this->w = 0;
}

ivec4::ivec4(const fvec3 & other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = static_cast<int>(other.z);
	this->w = 0;
}

ivec4::ivec4(const fvec4 & other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = static_cast<int>(other.z);
	this->w = static_cast<int>(other.w);
}

ivec4::ivec4(const int & value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

ivec4::ivec4(const int & x, const int & y, const int & z, const int & w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void ivec4::operator+=(const ivec4 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}

void ivec4::operator-=(const ivec4 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}

void ivec4::operator*=(const ivec4 & v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}

void ivec4::operator/=(const ivec4 & v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}

void ivec4::operator+=(const int & value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	this->w += value;
}

void ivec4::operator-=(const int & value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	this->w -= value;
}

void ivec4::operator/=(const int & value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
}

void ivec4::operator*=(const int & value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}

const ivec4 ivec4::operator-() const
{
	return ivec4(-this->x, -this->y, -this->z, -this->w);
}

const ivec4 ivec4::operator+(const ivec4 & v) const
{
	return ivec4((this->x + v.x), (this->y + v.y), (this->z + v.z), (this->w + v.w));
}

const ivec4 ivec4::operator-(const ivec4 & v) const
{
	return ivec4((this->x - v.x), (this->y - v.y), (this->z - v.z), (this->w - v.w));
}

const ivec4 ivec4::operator*(const ivec4 & v) const
{
	return ivec4((this->x * v.x), (this->y * v.y), (this->z * v.z), (this->w * v.w));
}

const ivec4 ivec4::operator/(const ivec4 & v) const
{
	return ivec4((this->x / v.x), (this->y / v.y), (this->z / v.z), (this->w / v.w));
}

const ivec4 ivec4::operator+(const int & value) const
{
	return ivec4((this->x + value), (this->y + value), (this->z + value), (this->w + value));
}

const ivec4 ivec4::operator-(const int & value) const
{
	return ivec4((this->x - value), (this->y - value), (this->z - value), (this->w - value));
}

const ivec4 ivec4::operator/(const int & value) const
{
	return ivec4((this->x / value), (this->y / value), (this->z / value), (this->w / value));
}

const ivec4 ivec4::operator*(const int & value) const
{
	return ivec4((this->x * value), (this->y * value), (this->z * value), (this->w * value));
}

const bool ivec4::operator==(const ivec4 & other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w));
}

const bool ivec4::operator!=(const ivec4 & other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w));
}