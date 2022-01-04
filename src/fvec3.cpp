#include "fvec2.hpp"
#include "fvec3.hpp"
#include "fvec4.hpp"
#include "ivec2.hpp"
#include "ivec3.hpp"
#include "ivec4.hpp"

fvec3::fvec3()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

fvec3::fvec3(const fvec2& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = 0.0f;
}

fvec3::fvec3(const fvec3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

fvec3::fvec3(const fvec4& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

fvec3::fvec3(const ivec2& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = 0.0f;
}

fvec3::fvec3(const ivec3& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = static_cast<float>(other.z);
}

fvec3::fvec3(const ivec4& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = static_cast<float>(other.z);
}

fvec3::fvec3(const float& value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

fvec3::fvec3(const float& x, const float& y, const float& z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

const fvec3 fvec3::operator+(const fvec3& other) const
{
	return fvec3((this->x + other.x), (this->y + other.y), (this->z + other.z));
}

const fvec3 fvec3::operator-(const fvec3& other) const
{
	return fvec3((this->x - other.x), (this->y - other.y), (this->z - other.z));
}

const fvec3 fvec3::operator*(const fvec3& other) const
{
	return fvec3((this->x * other.x), (this->y * other.y), (this->z * other.z));
}

const fvec3 fvec3::operator/(const fvec3& other) const
{
	return fvec3((this->x / other.x), (this->y / other.y), (this->z / other.z));
}

const fvec3 fvec3::operator+(const float& other) const
{
	return fvec3((this->x + other), (this->y + other), (this->z + other));
}

const fvec3 fvec3::operator-(const float& other) const
{
	return fvec3((this->x - other), (this->y - other), (this->z - other));
}

const fvec3 fvec3::operator*(const float& other) const
{
	return fvec3((this->x * other), (this->y * other), (this->z * other));
}

const fvec3 fvec3::operator/(const float& other) const
{
	return fvec3((this->x / other), (this->y / other), (this->z / other));
}

const fvec3 fvec3::operator-() const
{
	return fvec3(-this->x, -this->y, -this->z);
}

void fvec3::operator+=(const float& other)
{
	this->x += other;
	this->y += other;
	this->z += other;
}

void fvec3::operator-=(const float& other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
}

void fvec3::operator+=(const fvec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void fvec3::operator-=(const fvec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

void fvec3::operator*=(const fvec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
}

void fvec3::operator/=(const fvec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
}

void fvec3::operator*=(const float& other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;
}

void fvec3::operator/=(const float& other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
}

const bool fvec3::operator==(const fvec3& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
}

const bool fvec3::operator!=(const fvec3& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z));
}