#include "fvec4.hpp"
#include "mat22.hpp"
#include "mat33.hpp"
#include "mat44.hpp"

mat44::mat44(const float m00, const float m01, const float m02, const float m03, const float m10, const float m11, const float m12, const float m13, const float m20, const float m21, const float m22, const float m23, const float m30, const float m31, const float m32, const float m33)
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

mat44::mat44()
{
	for(int i = 0; i < 16; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
}

mat44::mat44(const mat22& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = 0.0f;
	this->m[3][0] = 0.0f;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = 0.0f;
	this->m[3][1] = 0.0f;
	this->m[0][2] = 0.0f;
	this->m[1][2] = 0.0f;
	this->m[2][2] = 1.0f;
	this->m[3][2] = 0.0f;
	this->m[0][3] = 0.0f;
	this->m[1][3] = 0.0f;
	this->m[2][3] = 0.0f;
	this->m[3][3] = 1.0f;
}

mat44::mat44(const float value)
{
	for(int i = 0; i < 16; i++)
	{
		f[i] = 0.0f;
	}

	this->m[0][0] = value;
	this->m[1][1] = value;
	this->m[2][2] = value;
	this->m[3][3] = value;
}

mat44::mat44(const mat33& other)
{
	this->m[0][0] = other.m[0][0];
	this->m[1][0] = other.m[1][0];
	this->m[2][0] = other.m[2][0];
	this->m[3][0] = 0.0f;
	this->m[0][1] = other.m[0][1];
	this->m[1][1] = other.m[1][1];
	this->m[2][1] = other.m[2][1];
	this->m[3][1] = 0.0f;
	this->m[0][2] = other.m[0][2];
	this->m[1][2] = other.m[1][2];
	this->m[2][2] = other.m[2][2];
	this->m[3][2] = 0.0f;
	this->m[0][3] = 0.0f;
	this->m[1][3] = 0.0f;
	this->m[2][3] = 0.0f;
	this->m[3][3] = 1.0f;
}

mat44::mat44(const mat44& other)
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

const fvec4 mat44::operator*(const fvec4& other) const
{
	fvec4 newVector;

	newVector.x = ((this->m[0][0] * other.x) + (this->m[1][0] * other.y) + (this->m[2][0] * other.z) + (this->m[3][0] * other.w));
	newVector.y = ((this->m[0][1] * other.x) + (this->m[1][1] * other.y) + (this->m[2][1] * other.z) + (this->m[3][1] * other.w));
	newVector.z = ((this->m[0][2] * other.x) + (this->m[1][2] * other.y) + (this->m[2][2] * other.z) + (this->m[3][2] * other.w));
	newVector.w = ((this->m[0][3] * other.x) + (this->m[1][3] * other.y) + (this->m[2][3] * other.z) + (this->m[3][3] * other.w));

	return newVector;
}

const mat44 mat44::operator+(const mat44& other) const
{
	mat44 newMatrix;

	for(int i = 0; i < 16; i++)
	{
		newMatrix.f[i] = (this->f[i] + other.f[i]);
	}

	return newMatrix;
}

const mat44 mat44::operator-(const mat44& other) const
{
	mat44 newMatrix;

	for(int i = 0; i < 16; i++)
	{
		newMatrix.f[i] = (this->f[i] - other.f[i]);
	}

	return newMatrix;
}

const mat44 mat44::operator*(const mat44& other) const
{
	mat44 newMatrix(0.0f);

	for(int column = 0; column < 4; column++)
	{
		for(int row = 0; row < 4; row++)
		{
			for(int inner = 0; inner < 4; inner++)
			{
				newMatrix.m[row][column] += (this->m[inner][column] * other.m[row][inner]);
			}
		}
	}

	return newMatrix;
}