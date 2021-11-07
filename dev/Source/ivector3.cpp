#include "ivector3.hpp"
#include "vector3.hpp"

Ivec3::Ivec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Ivec3::Ivec3(const Vec3& other)
{
	this->x = static_cast<int>(other.x);
	this->y = static_cast<int>(other.y);
	this->z = static_cast<int>(other.z);
}

Ivec3::Ivec3(const int value)
{
	this->x = value;
	this->y = value;
	this->z = value;
}

Ivec3::Ivec3(const int x, const int y, const int z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Ivec3::operator+=(const Ivec3& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}

void Ivec3::operator-=(const Ivec3& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}

void Ivec3::operator*=(const Ivec3& v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
}

void Ivec3::operator/=(const Ivec3& v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
}

void Ivec3::operator+=(const int& value)
{
	this->x += value;
	this->y += value;
	this->z += value;
}

void Ivec3::operator-=(const int& value)
{
	this->x -= value;
	this->y -= value;
	this->z -= value;
}

void Ivec3::operator/=(const int& value)
{
	this->x /= value;
	this->y /= value;
	this->z /= value;
}

void Ivec3::operator*=(const int& value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;
}

const Ivec3 Ivec3::operator-() const
{
	return Ivec3(-this->x, -this->y, -this->z);
}

const Ivec3 Ivec3::operator+(const Ivec3& other) const
{
	return Ivec3((this->x + other.x), (this->y + other.y), (this->z + other.z));
}

const Ivec3 Ivec3::operator-(const Ivec3& other) const
{
	return Ivec3((this->x - other.x), (this->y - other.y), (this->z - other.z));
}

const Ivec3 Ivec3::operator*(const Ivec3& other) const
{
	return Ivec3((this->x * other.x), (this->y * other.y), (this->z * other.z));
}

const Ivec3 Ivec3::operator/(const Ivec3& other) const
{
	return Ivec3((this->x / other.x), (this->y / other.y), (this->z / other.z));
}

const Ivec3 Ivec3::operator+(const int& other) const
{
	return Ivec3((this->x + other), (this->y + other), (this->z + other));
}

const Ivec3 Ivec3::operator-(const int& other) const
{
	return Ivec3((this->x - other), (this->y - other), (this->z - other));
}

const Ivec3 Ivec3::operator*(const int& other) const
{
	return Ivec3((this->x * other), (this->y * other), (this->z * other));
}

const Ivec3 Ivec3::operator/(const int& other) const
{
	return Ivec3((this->x / other), (this->y / other), (this->z / other));
}

const bool Ivec3::operator==(const Ivec3& other) const
{
	return ((this->x == other.x) && (this->y == other.y) && (this->z == other.z));
}

const bool Ivec3::operator!=(const Ivec3& other) const
{
	return ((this->x != other.x) || (this->y != other.y) || (this->z != other.z));
}