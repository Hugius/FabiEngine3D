#include "fvec3.hpp"
#include "mat22.hpp"
#include "mat33.hpp"
#include "mat44.hpp"

mat33::mat33(const float m00, const float m01, const float m02, const float m10, const float m11, const float m12, const float m20, const float m21, const float m22)
{
	this->m[0][0] = m00;
	this->m[1][0] = m10;
	this->m[2][0] = m20;
	this->m[0][1] = m01;
	this->m[1][1] = m11;
	this->m[2][1] = m21;
	this->m[0][2] = m02;
	this->m[1][2] = m12;
	this->m[2][2] = m22;
}

mat33::mat33()
{
	for(int i = 0; i < 9; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
}

mat33::mat33(const mat22& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = 0.0f;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = 0.0f;
	this->m[0][2] = 0.0f;
	this->m[1][2] = 0.0f;
	this->m[2][2] = 1.0f;
}

mat33::mat33(const mat33& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = other.m[2][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = other.m[2][1];
	this->m[0][2] = other.m[0][2];
	this->m[1][2] = other.m[1][2];
	this->m[2][2] = other.m[2][2];
}

mat33::mat33(const mat44& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = other.m[2][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = other.m[2][1];
	this->m[0][2] = other.m[0][2];
	this->m[1][2] = other.m[1][2];
	this->m[2][2] = other.m[2][2];
}

mat33::mat33(const float value)
{
	for(int i = 0; i < 9; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
}

const mat33 mat33::operator+(const mat33& other) const
{
	mat33 result;

	for(int i = 0; i < 9; i++)
	{
		result.f[i] = (this->f[i] + other.f[i]);
	}

	return result;
}

const mat33 mat33::operator-(const mat33& other) const
{
	mat33 result;

	for(int i = 0; i < 9; i++)
	{
		result.f[i] = (this->f[i] - other.f[i]);
	}

	return result;
}

const mat33 mat33::operator*(const mat33& other) const
{
	mat33 result(0.0f);

	for(int column = 0; column < 3; column++)
	{
		for(int row = 0; row < 3; row++)
		{
			for(int inner = 0; inner < 3; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}

const fvec3 mat33::operator*(const fvec3& other) const
{
	fvec3 result;

	result.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y) + (this->m[2][0] * other.z));
	result.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y) + (this->m[2][1] * other.z));
	result.z = ((this->m[0][2] * other.x) + (this->m[1][2] * other.y) + (this->m[2][2] * other.z));

	return result;
}