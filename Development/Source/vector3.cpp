#include "vector3.hpp"
#include "ivector3.hpp"

Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(const Ivec3& other)
{
	this->x = static_cast<float>(other.x);
	this->y = static_cast<float>(other.y);
	this->z = static_cast<float>(other.z);
}

Vec3::Vec3(const float value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

Vec3::Vec3(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

const Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

const Vec3 Vec3::operator-(const Vec3& other) const
{
	return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

const Vec3 Vec3::operator*(const Vec3& other) const
{
	return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

const Vec3 Vec3::operator/(const Vec3& other) const
{
	return Vec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

const Vec3 Vec3::operator+(const float& other) const
{
	return Vec3(this->x + other, this->y + other, this->z + other);
}

const Vec3 Vec3::operator-(const float& other) const
{
	return Vec3(this->x - other, this->y - other, this->z - other);
}

const Vec3 Vec3::operator*(const float& other) const
{
	return Vec3(this->x * other, this->y * other, this->z * other);
}

const Vec3 Vec3::operator/(const float& other) const
{
	return Vec3(this->x / other, this->y / other, this->z / other);
}

const Vec3 Vec3::operator-() const
{
	return Vec3(-this->x, -this->y, -this->z);
}

void Vec3::operator+=(const float& other)
{
	this->x += other;
	this->y += other;
	this->z += other;
}

void Vec3::operator-=(const float& other)
{
	this->x -= other;
	this->y -= other;
	this->z -= other;
}

void Vec3::operator+=(const Vec3& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Vec3::operator-=(const Vec3& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;
}

void Vec3::operator*=(const Vec3& other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
}

void Vec3::operator/=(const Vec3& other)
{
	this->x /= other.x;
	this->y /= other.y;
	this->z /= other.z;
}

void Vec3::operator*=(const float& other)
{
	this->x *= other;
	this->y *= other;
	this->z *= other;
}

void Vec3::operator/=(const float& other)
{
	this->x /= other;
	this->y /= other;
	this->z /= other;
}

const bool Vec3::operator==(const Vec3& other) const
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

const bool Vec3::operator!=(const Vec3& other) const
{
	return (this->x != other.x || this->y != other.y || this->z != other.z);
}