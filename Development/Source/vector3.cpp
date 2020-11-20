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

Vec3::Vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3 Vec3::operator+(const Vec3 & other) const
{
	return Vec3(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vec3 Vec3::operator-(const Vec3 & other) const
{
	return Vec3(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vec3 Vec3::operator*(const Vec3& other) const
{
	return Vec3(this->x * other.x, this->y * other.y, this->z * other.z);
}

Vec3 Vec3::operator/(const Vec3& other) const
{
	return Vec3(this->x / other.x, this->y / other.y, this->z / other.z);
}

Vec3 Vec3::operator+(const float& other) const
{
	return Vec3(this->x + other, this->y + other, this->z + other);
}

Vec3 Vec3::operator-(const float& other) const
{
	return Vec3(this->x - other, this->y - other, this->z - other);
}

Vec3 Vec3::operator*(const float& other) const
{
	return Vec3(this->x * other, this->y * other, this->z * other);
}

Vec3 Vec3::operator/(const float& other) const
{
	return Vec3(this->x / other, this->y / other, this->z / other);
}

Vec3 Vec3::operator-() const
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

void Vec3::operator+=(const Vec3 & other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
}

void Vec3::operator-=(const Vec3 & other)
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

Vec3 Vec3::cross(const Vec3 & vector) const
{
	Vec3 crossVector;
	crossVector.x = this->y * vector.z - this->z * vector.y;
	crossVector.y = this->z * vector.x - this->x * vector.z;
	crossVector.z = this->x * vector.y - this->y * vector.x;
	return crossVector;
}

float Vec3::dot(const Vec3 & vector) const
{
	return (this->x * vector.x + this->y * vector.y + this->z * vector.z); // Fastest dot product calculation
}

float Vec3::getMagnitude() const
{
	return float(sqrt(this->x*this->x + this->y*this->y + this->z*this->z));
}

void Vec3::normalize()
{
	if (*this != Vec3(0.0f, 0.0f, 0.0f)) { // Must be non-zero vector
		this->x /= this->getMagnitude();
		this->y /= this->getMagnitude();
		this->z /= this->getMagnitude();
	}
}

bool Vec3::operator==(const Vec3 & other) const
{
	return (this->x == other.x && this->y == other.y && this->z == other.z);
}

bool Vec3::operator!=(const Vec3 & other) const
{
	return (this->x != other.x || this->y != other.y || this->z != other.z);
}

void Vec3::clear()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}