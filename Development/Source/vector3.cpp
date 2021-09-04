#include "vector3.hpp"

Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3::Vec3(float xyz)
{
	this->x = xyz;
	this->y = xyz;
	this->z = xyz;
}

Vec3::Vec3(float x, float y, float z)
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