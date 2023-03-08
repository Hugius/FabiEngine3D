#include "ivec4.hpp"
#include "imat22.hpp"
#include "imat33.hpp"
#include "imat44.hpp"
#include "fmat22.hpp"
#include "fmat33.hpp"
#include "fmat44.hpp"

imat44::imat44(const int m00, const int m01, const int m02, const int m03, const int m10, const int m11, const int m12, const int m13, const int m20, const int m21, const int m22, const int m23, const int m30, const int m31, const int m32, const int m33)
{
	this->m[0][0] = m00;
	this->m[1][0] = m10;
	this->m[2][0] = m20;
	this->m[3][0] = m30;
	this->m[0][1] = m01;
	this->m[1][1] = m11;
	this->m[2][1] = m21;
	this->m[3][1] = m31;
	this->m[0][2] = m02;
	this->m[1][2] = m12;
	this->m[2][2] = m22;
	this->m[3][2] = m32;
	this->m[0][3] = m03;
	this->m[1][3] = m13;
	this->m[2][3] = m23;
	this->m[3][3] = m33;
}

imat44::imat44()
{
	for(int index = 0; index < 16; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = 1;
	this->m[1][1] = 1;
	this->m[2][2] = 1;
	this->m[3][3] = 1;
}

imat44::imat44(const imat22 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = 0;
	this->m[3][0] = 0;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = 0;
	this->m[3][1] = 0;
	this->m[0][2] = 0;
	this->m[1][2] = 0;
	this->m[2][2] = 1;
	this->m[3][2] = 0;
	this->m[0][3] = 0;
	this->m[1][3] = 0;
	this->m[2][3] = 0;
	this->m[3][3] = 1;
}

imat44::imat44(const imat33 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = other.m[2][0];
	this->m[3][0] = 0;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = other.m[2][1];
	this->m[3][1] = 0;
	this->m[0][2] = other.m[0][2];
	this->m[1][2] = other.m[1][2];
	this->m[2][2] = other.m[2][2];
	this->m[3][2] = 0;
	this->m[0][3] = 0;
	this->m[1][3] = 0;
	this->m[2][3] = 0;
	this->m[3][3] = 1;
}

imat44::imat44(const imat44 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = other.m[2][0];
	this->m[3][0] = other.m[3][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = other.m[2][1];
	this->m[3][1] = other.m[3][1];
	this->m[0][2] = other.m[0][2];
	this->m[1][2] = other.m[1][2];
	this->m[2][2] = other.m[2][2];
	this->m[3][2] = other.m[3][2];
	this->m[0][3] = other.m[0][3];
	this->m[1][3] = other.m[1][3];
	this->m[2][3] = other.m[2][3];
	this->m[3][3] = other.m[3][3];
}

imat44::imat44(const fmat22 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[2][0] = 0;
	this->m[3][0] = 0;
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
	this->m[2][1] = 0;
	this->m[3][1] = 0;
	this->m[0][2] = 0;
	this->m[1][2] = 0;
	this->m[2][2] = 1;
	this->m[3][2] = 0;
	this->m[0][3] = 0;
	this->m[1][3] = 0;
	this->m[2][3] = 0;
	this->m[3][3] = 1;
}

imat44::imat44(const fmat33 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[2][0] = static_cast<int>(other.m[2][0]);
	this->m[3][0] = 0;
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
	this->m[2][1] = static_cast<int>(other.m[2][1]);
	this->m[3][1] = 0;
	this->m[0][2] = static_cast<int>(other.m[0][2]);
	this->m[1][2] = static_cast<int>(other.m[1][2]);
	this->m[2][2] = static_cast<int>(other.m[2][2]);
	this->m[3][2] = 0;
	this->m[0][3] = 0;
	this->m[1][3] = 0;
	this->m[2][3] = 0;
	this->m[3][3] = 1;
}

imat44::imat44(const fmat44 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[2][0] = static_cast<int>(other.m[2][0]);
	this->m[3][0] = static_cast<int>(other.m[3][0]);
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
	this->m[2][1] = static_cast<int>(other.m[2][1]);
	this->m[3][1] = static_cast<int>(other.m[3][1]);
	this->m[0][2] = static_cast<int>(other.m[0][2]);
	this->m[1][2] = static_cast<int>(other.m[1][2]);
	this->m[2][2] = static_cast<int>(other.m[2][2]);
	this->m[3][2] = static_cast<int>(other.m[3][2]);
	this->m[0][3] = static_cast<int>(other.m[0][3]);
	this->m[1][3] = static_cast<int>(other.m[1][3]);
	this->m[2][3] = static_cast<int>(other.m[2][3]);
	this->m[3][3] = static_cast<int>(other.m[3][3]);
}

imat44::imat44(const int value)
{
	for(int index = 0; index < 16; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
	this->m[3][3] = value;
}

const ivec4 imat44::operator*(const ivec4 & other) const
{
	ivec4 result = {};

	result.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y) + (this->m[2][0] * other.z) + (this->m[3][0] * other.w));
	result.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y) + (this->m[2][1] * other.z) + (this->m[3][1] * other.w));
	result.z = ((this->m[0][2] * other.x) + (this->m[1][2] * other.y) + (this->m[2][2] * other.z) + (this->m[3][2] * other.w));
	result.w = ((this->m[0][3] * other.x) + (this->m[1][3] * other.y) + (this->m[2][3] * other.z) + (this->m[3][3] * other.w));

	return result;
}

const imat44 imat44::operator+(const imat44 & other) const
{
	imat44 result = {};

	for(int index = 0; index < 16; index++)
	{
		result.f[index] = (this->f[index] + other.f[index]);
	}

	return result;
}

const imat44 imat44::operator-(const imat44 & other) const
{
	imat44 result = {};

	for(int index = 0; index < 16; index++)
	{
		result.f[index] = (this->f[index] - other.f[index]);
	}

	return result;
}

const imat44 imat44::operator*(const imat44 & other) const
{
	imat44 result = {};

	for(int column = 0; column < 4; column++)
	{
		for(int row = 0; row < 4; row++)
		{
			result.m[row][column] = 0;

			for(int inner = 0; inner < 4; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}