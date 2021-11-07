#include "vector4.hpp"
#include "ivector4.hpp"

Vec4::Vec4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vec4::Vec4(const Ivec4& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = static_cast<float>(other.z);
	this->w = static_cast<float>(other.w);
}

Vec4::Vec4(const float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

Vec4::Vec4(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4::operator+=(const Vec4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}

void Vec4::operator-=(const Vec4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}

void Vec4::operator*=(const Vec4& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}

void Vec4::operator/=(const Vec4& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}

void Vec4::operator+=(const float& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	this->w += value;
}

void Vec4::operator-=(const float& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	this->w -= value;
}

void Vec4::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
}

void Vec4::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}

const Vec4 Vec4::operator-() const
{
	return Vec4(-this->x, -this->y, -this->z, -this->w);
}

const Vec4 Vec4::operator+(const Vec4& v) const
{
	return Vec4((this->x + v.x), (this->y + v.y), (this->z + v.z), (this->w + v.w));
}

const Vec4 Vec4::operator-(const Vec4& v) const
{
	return Vec4((this->x - v.x), (this->y - v.y), (this->z - v.z), (this->w - v.w));
}

const Vec4 Vec4::operator*(const Vec4& v) const
{
	return Vec4((this->x * v.x), (this->y * v.y), (this->z * v.z), (this->w * v.w));
}

const Vec4 Vec4::operator/(const Vec4& v) const
{
	return Vec4((this->x / v.x), (this->y / v.y), (this->z / v.z), (this->w / v.w));
}

const Vec4 Vec4::operator+(const float& value) const
{
	return Vec4((this->x + value), (this->y + value), (this->z + value), (this->w + value));
}

const Vec4 Vec4::operator-(const float& value) const
{
	return Vec4((this->x - value), (this->y - value), (this->z - value), (this->w - value));
}

const Vec4 Vec4::operator/(const float& value) const
{
	return Vec4((this->x / value), (this->y / value), (this->z / value), (this->w / value));
}

const Vec4 Vec4::operator*(const float& value) const
{
	return Vec4((this->x * value), (this->y * value), (this->z * value), (this->w * value));
}

const bool Vec4::operator==(const Vec4& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w));
}

const bool Vec4::operator!=(const Vec4& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w));
}