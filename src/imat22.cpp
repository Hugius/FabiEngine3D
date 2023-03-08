#include "ivec2.hpp"
#include "imat22.hpp"
#include "imat33.hpp"
#include "imat44.hpp"
#include "fmat22.hpp"
#include "fmat33.hpp"
#include "fmat44.hpp"

imat22::imat22(const int m00, const int m01, const int m10, const int m11)
{
	this->m[0][0] = m00;
	this->m[1][0] = m10;
	this->m[0][1] = m01;
	this->m[1][1] = m11;
}

imat22::imat22()
{
	for(int index = 0; index < 4; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = 1;
	this->m[1][1] = 1;
}

imat22::imat22(const fmat22 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
}

imat22::imat22(const fmat33 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
}

imat22::imat22(const fmat44 & other)
{
	this->m[0][0] = static_cast<int>(other.m[0][0]);
	this->m[1][0] = static_cast<int>(other.m[1][0]);
	this->m[0][1] = static_cast<int>(other.m[0][1]);
	this->m[1][1] = static_cast<int>(other.m[1][1]);
}

imat22::imat22(const imat22 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
}

imat22::imat22(const imat33 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
}

imat22::imat22(const imat44 & other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
}

imat22::imat22(const int value)
{
	for(int index = 0; index < 4; index++)
	{
		f[index] = 0;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
}

const imat22 imat22::operator+(const imat22 & other) const
{
	imat22 result = {};

	for(int index = 0; index < 4; index++)
	{
		result.f[index] = (this->f[index] + other.f[index]);
	}

	return result;
}

const imat22 imat22::operator-(const imat22 & other) const
{
	imat22 result = {};

	for(int index = 0; index < 4; index++)
	{
		result.f[index] = (this->f[index] - other.f[index]);
	}

	return result;
}

const imat22 imat22::operator*(const imat22 & other) const
{
	imat22 result = {};

	for(int column = 0; column < 2; column++)
	{
		for(int row = 0; row < 2; row++)
		{
			result.m[row][column] = 0;

			for(int inner = 0; inner < 2; inner++)
			{
				result.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return result;
}

const ivec2 imat22::operator*(const ivec2 & other) const
{
	ivec2 result = {};

	result.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y));
	result.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y));

	return result;
}