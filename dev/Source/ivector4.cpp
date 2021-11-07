#include "ivector4.hpp"
#include "vector4.hpp"

Ivec4::Ivec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Ivec4::Ivec4(const Vec4& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = static_cast<int>(other.z);
	this->w = static_cast<int>(other.w);
}

Ivec4::Ivec4(const int value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

Ivec4::Ivec4(const int x, const int y, const int z, const int w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Ivec4::operator+=(const Ivec4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}

void Ivec4::operator-=(const Ivec4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}

void Ivec4::operator*=(const Ivec4& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}

void Ivec4::operator/=(const Ivec4& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}

void Ivec4::operator+=(const int& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	this->w += value;
}

void Ivec4::operator-=(const int& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	this->w -= value;
}

void Ivec4::operator/=(const int& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
}

void Ivec4::operator*=(const int& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}

const Ivec4 Ivec4::operator-() const
{
	return Ivec4(-this->x, -this->y, -this->z, -this->w);
}

const Ivec4 Ivec4::operator+(const Ivec4& v) const
{
	return Ivec4((this->x + v.x), (this->y + v.y), (this->z + v.z), (this->w + v.w));
}

const Ivec4 Ivec4::operator-(const Ivec4& v) const
{
	return Ivec4((this->x - v.x), (this->y - v.y), (this->z - v.z), (this->w - v.w));
}

const Ivec4 Ivec4::operator*(const Ivec4& v) const
{
	return Ivec4((this->x * v.x), (this->y * v.y), (this->z * v.z), (this->w * v.w));
}

const Ivec4 Ivec4::operator/(const Ivec4& v) const
{
	return Ivec4((this->x / v.x), (this->y / v.y), (this->z / v.z), (this->w / v.w));
}

const Ivec4 Ivec4::operator+(const int& value) const
{
	return Ivec4((this->x + value), (this->y + value), (this->z + value), (this->w + value));
}

const Ivec4 Ivec4::operator-(const int& value) const
{
	return Ivec4((this->x - value), (this->y - value), (this->z - value), (this->w - value));
}

const Ivec4 Ivec4::operator/(const int& value) const
{
	return Ivec4((this->x / value), (this->y / value), (this->z / value), (this->w / value));
}

const Ivec4 Ivec4::operator*(const int& value) const
{
	return Ivec4((this->x * value), (this->y * value), (this->z * value), (this->w * value));
}

const bool Ivec4::operator==(const Ivec4& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w));
}

const bool Ivec4::operator!=(const Ivec4& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w));
}