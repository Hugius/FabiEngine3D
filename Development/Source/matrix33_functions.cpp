#include "matrix33.hpp"

const float Matrix33::getDeterminant()
{
	float values[3];

	values[0] = (this->m[0][0] * ((this->m[1][1] * this->m[2][2]) - (this->m[2][1] * this->m[1][2])));
	values[1] = (this->m[1][0] * ((this->m[0][1] * this->m[2][2]) - (this->m[2][1] * this->m[0][2])));
	values[2] = (this->m[2][0] * ((this->m[0][1] * this->m[1][2]) - (this->m[1][1] * this->m[0][2])));

	return (values[0] - values[1] + values[2]);
}

const bool Matrix33::invert()
{
	// Calculate determinant
	auto determinant = this->getDeterminant();

	// Check if determinant is invalid
	if (determinant == 0.0f)
	{
		return false;
	}

	// Result
	Matrix33 newMatrix;

	// Calculate
	this->m[0][0] = ((this->m[1][1] * this->m[2][2]) - (this->m[2][1] * this->m[1][2]));
	this->m[0][1] = ((this->m[0][2] * this->m[2][1]) - (this->m[0][1] * this->m[2][2]));
	this->m[0][2] = ((this->m[0][1] * this->m[1][2]) - (this->m[0][2] * this->m[1][1]));
	this->m[1][0] = ((this->m[1][2] * this->m[2][0]) - (this->m[1][0] * this->m[2][2]));
	this->m[1][1] = ((this->m[0][0] * this->m[2][2]) - (this->m[0][2] * this->m[2][0]));
	this->m[1][2] = ((this->m[1][0] * this->m[0][2]) - (this->m[0][0] * this->m[1][2]));
	this->m[2][0] = ((this->m[1][0] * this->m[2][1]) - (this->m[2][0] * this->m[1][1]));
	this->m[2][1] = ((this->m[2][0] * this->m[0][1]) - (this->m[0][0] * this->m[2][1]));
	this->m[2][2] = ((this->m[0][0] * this->m[1][1]) - (this->m[1][0] * this->m[0][1]));

	// Multiply
	for (unsigned int i = 0; i < 9; i++)
	{
		this->f[i] = (newMatrix.f[i] * (1.0f / determinant));
	}

	// Return
	return true;
}

void Matrix33::transpose()
{
	// Copy current matrix to temporary matrix
	Matrix33 tempMatrix;
	for (unsigned int i = 0; i < 9; i++)
	{
		tempMatrix.f[i] = this->f[i];
	}

	// Swap rows and columns
	for (unsigned int r = 0; r < 3; r++)
	{
		for (unsigned c = 0; c < 3; c++)
		{
			this->m[r][c] = tempMatrix.m[c][r];
		}
	}
}