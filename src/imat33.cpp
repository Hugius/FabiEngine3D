#include "ivec3.hpp"
#include "imat22.hpp"
#include "imat33.hpp"
#include "imat44.hpp"

imat33::imat33(const int m00, const int m01, const int m02, const int m10, const int m11, const int m12, const int m20, const int m21, const int m22)
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

imat33::imat33()
{
	for(int index = 0; index < 9; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = 1;
	this->m[1][1] = 1;
	this->m[2][2] = 1;
}

imat33::imat33(const imat22 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = 0;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = 0;
	this->m[0][2] = 0;
	this->m[1][2] = 0;
	this->m[2][2] = 1;
}

imat33::imat33(const imat33 & other)
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

imat33::imat33(const imat44 & other)
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

imat33::imat33(const int value)
{
	for(int index = 0; index < 9; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
}

const imat33 imat33::operator+(const imat33 & other) const
{
	imat33 result = {};

	for(int index = 0; index < 9; index++)
	{
		result.f[index] = (this->f[index] + other.f[index]);
	}

	return result;
}

const imat33 imat33::operator-(const imat33 & other) const
{
	imat33 result = {};

	for(int index = 0; index < 9; index++)
	{
		result.f[index] = (this->f[index] - other.f[index]);
	}

	return result;
}

const imat33 imat33::operator*(const imat33 & other) const
{
	imat33 result = {};

	for(int column = 0; column < 3; column++)
	{
		for(int row = 0; row < 3; row++)
		{
			result.m[row][column] = 0;

			for(int inner = 0; inner < 3; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}

const ivec3 imat33::operator*(const ivec3 & other) const
{
	ivec3 result = {};

	result.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y) + (this->m[2][0] * other.z));
	result.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y) + (this->m[2][1] * other.z));
	result.z = ((this->m[0][2] * other.x) + (this->m[1][2] * other.y) + (this->m[2][2] * other.z));

	return result;
}