#include "vector4.hpp"

Vec4::Vec4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

Vec4::Vec4(float xyzw)
{
	this->x = xyzw;
	this->y = xyzw;
	this->z = xyzw;
	this->w = xyzw;
}

Vec4::Vec4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void Vec4::operator+=(const Vec4 & v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}

void Vec4::operator-=(const Vec4 & v)
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

void Vec4::operator/=(const float & value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
}

void Vec4::operator*=(const float & value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}

const float Vec4::getMagnitude() const
{
	return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z + this->w * this->w);
}

void Vec4::normalize()
{
	float inverseSqrt = (1.0f / this->getMagnitude());

	this->x *= inverseSqrt;
	this->y *= inverseSqrt;
	this->z *= inverseSqrt;
	this->w *= inverseSqrt;
}

void Vec4::clear()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

const Vec4 Vec4::operator-() const
{
	return Vec4(-this->x, -this->y, -this->z, -this->w);
}

const Vec4 Vec4::operator+(const Vec4 & v) const
{
	return Vec4(this->x + v.x, this->y + v.y, this->z + v.z, this->w + v.w);
}

const Vec4 Vec4::operator-(const Vec4 & v) const
{
	return Vec4(this->x - v.x, this->y - v.y, this->z - v.z, this->w - v.w);
}

const Vec4 Vec4::operator*(const Vec4& v) const
{
	return Vec4(this->x * v.x, this->y * v.y, this->z * v.z, this->w * v.w);
}

const Vec4 Vec4::operator/(const Vec4& v) const
{
	return Vec4(this->x / v.x, this->y / v.y, this->z / v.z, this->w / v.w);
}

const Vec4 Vec4::operator+(const float& value) const
{
	return Vec4(this->x + value, this->y + value, this->z + value, this->w + value);
}

const Vec4 Vec4::operator-(const float& value) const
{
	return Vec4(this->x - value, this->y - value, this->z - value, this->w - value);
}

const Vec4 Vec4::operator/(const float & value) const
{
	return Vec4(this->x / value, this->y / value, this->z / value, this->w / value);
}

const Vec4 Vec4::operator*(const float & value) const
{
	return Vec4(this->x * value, this->y * value, this->z * value, this->w * value);
}

const bool Vec4::operator==(const Vec4 & other) const
{
	return (this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w);
}

const bool Vec4::operator!=(const Vec4 & other) const
{
	return (this->x != other.x || this->y != other.y || this->z != other.z || this->w != other.w);
}