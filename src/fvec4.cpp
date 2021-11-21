#include "fvec4.hpp"
#include "ivec4.hpp"

fvec4::fvec4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

fvec4::fvec4(const ivec4& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = static_cast<float>(other.z);
	this->w = static_cast<float>(other.w);
}

fvec4::fvec4(const float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
	this->w = value;
}

fvec4::fvec4(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void fvec4::operator+=(const fvec4& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
}

void fvec4::operator-=(const fvec4& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
}

void fvec4::operator*=(const fvec4& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
}

void fvec4::operator/=(const fvec4& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
}

void fvec4::operator+=(const float& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
	this->w += value;
}

void fvec4::operator-=(const float& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
	this->w -= value;
}

void fvec4::operator/=(const float& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
	this->w /= value;
}

void fvec4::operator*=(const float& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
	this->w *= value;
}

const fvec4 fvec4::operator-() const
{
	return fvec4(-this->x, -this->y, -this->z, -this->w);
}

const fvec4 fvec4::operator+(const fvec4& v) const
{
	return fvec4((this->x + v.x), (this->y + v.y), (this->z + v.z), (this->w + v.w));
}

const fvec4 fvec4::operator-(const fvec4& v) const
{
	return fvec4((this->x - v.x), (this->y - v.y), (this->z - v.z), (this->w - v.w));
}

const fvec4 fvec4::operator*(const fvec4& v) const
{
	return fvec4((this->x * v.x), (this->y * v.y), (this->z * v.z), (this->w * v.w));
}

const fvec4 fvec4::operator/(const fvec4& v) const
{
	return fvec4((this->x / v.x), (this->y / v.y), (this->z / v.z), (this->w / v.w));
}

const fvec4 fvec4::operator+(const float& value) const
{
	return fvec4((this->x + value), (this->y + value), (this->z + value), (this->w + value));
}

const fvec4 fvec4::operator-(const float& value) const
{
	return fvec4((this->x - value), (this->y - value), (this->z - value), (this->w - value));
}

const fvec4 fvec4::operator/(const float& value) const
{
	return fvec4((this->x / value), (this->y / value), (this->z / value), (this->w / value));
}

const fvec4 fvec4::operator*(const float& value) const
{
	return fvec4((this->x * value), (this->y * value), (this->z * value), (this->w * value));
}

const bool fvec4::operator==(const fvec4& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z) && (this->w == other.w));
}

const bool fvec4::operator!=(const fvec4& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z) || (this->w != other.w));
}