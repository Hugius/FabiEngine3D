#include "mat22.hpp"
#include "mat33.hpp"

mat22::mat22(const float m00, const float m01, const float m10, const float m11)
{
	this->m[0][0] = m00;
	this->m[1][0] = m10;
	this->m[0][1] = m01;
	this->m[1][1] = m11;
}

mat22::mat22()
{
	for(int i = 0; i < 4; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
}

mat22::mat22(const mat33& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
}

mat22::mat22(const mat44& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
}

mat22::mat22(const float value)
{
	for(int i = 0; i < 4; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
}

const mat22 mat22::operator+(const mat22& other) const
{
	mat22 newMatrix;

	for(int i = 0; i < 4; i++)
	{
		newMatrix.f[i] = (this->f[i] + other.f[i]);
	}

	return newMatrix;
}

const mat22 mat22::operator-(const mat22& other) const
{
	mat22 newMatrix;

	for(int i = 0; i < 4; i++)
	{
		newMatrix.f[i] = (this->f[i] - other.f[i]);
	}

	return newMatrix;
}

const mat22 mat22::operator*(const mat22& other) const
{
	mat22 newMatrix(0.0f);

	for(int column = 0; column < 2; column++)
	{
		for(int row = 0; row < 2; row++)
		{
			for(int inner = 0; inner < 2; inner++)
			{
				newMatrix.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return newMatrix;
}

const fvec2 mat22::operator*(const fvec2& other) const
{
	fvec2 newVector;

	newVector.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y));
	newVector.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y));

	return newVector;
}