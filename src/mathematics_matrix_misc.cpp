#include "mathematics.hpp"

const mat22 Math::invertMatrix(const mat22& matrix)
{
	auto determinant = calculateDeterminant(matrix);
	if(determinant == 0.0f)
	{
		return mat22(0.0f);
	}

	mat22 tempMatrix;
	tempMatrix.f[0] = matrix.f[3];
	tempMatrix.f[1] = -matrix.f[1];
	tempMatrix.f[2] = -matrix.f[2];
	tempMatrix.f[3] = matrix.f[0];

	mat22 newMatrix;
	for(unsigned int i = 0; i < 4; i++)
	{
		newMatrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return newMatrix;
}

const mat33 Math::invertMatrix(const mat33& matrix)
{
	auto determinant = calculateDeterminant(matrix);

	if(determinant == 0.0f)
	{
		return mat33(0.0f);
	}

	mat33 tempMatrix;
	tempMatrix.f[0] = ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2]));
	tempMatrix.f[1] = ((matrix.m[0][2] * matrix.m[2][1]) - (matrix.m[0][1] * matrix.m[2][2]));
	tempMatrix.f[2] = ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[0][2] * matrix.m[1][1]));
	tempMatrix.f[3] = ((matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[1][0] * matrix.m[2][2]));
	tempMatrix.f[4] = ((matrix.m[0][0] * matrix.m[2][2]) - (matrix.m[0][2] * matrix.m[2][0]));
	tempMatrix.f[5] = ((matrix.m[1][0] * matrix.m[0][2]) - (matrix.m[0][0] * matrix.m[1][2]));
	tempMatrix.f[6] = ((matrix.m[1][0] * matrix.m[2][1]) - (matrix.m[2][0] * matrix.m[1][1]));
	tempMatrix.f[7] = ((matrix.m[2][0] * matrix.m[0][1]) - (matrix.m[0][0] * matrix.m[2][1]));
	tempMatrix.f[8] = ((matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[1][0] * matrix.m[0][1]));

	mat33 newMatrix;
	for(unsigned int i = 0; i < 9; i++)
	{
		newMatrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return newMatrix;
}

const mat44 Math::invertMatrix(const mat44& matrix)
{
	auto determinant = calculateDeterminant(matrix);
	if(determinant == 0.0f)
	{
		return mat44(0.0f);
	}

	mat44 tempMatrix;
	tempMatrix.f[0] =
		matrix.f[5] * matrix.f[10] * matrix.f[15] -
		matrix.f[5] * matrix.f[11] * matrix.f[14] -
		matrix.f[9] * matrix.f[6] * matrix.f[15] +
		matrix.f[9] * matrix.f[7] * matrix.f[14] +
		matrix.f[13] * matrix.f[6] * matrix.f[11] -
		matrix.f[13] * matrix.f[7] * matrix.f[10];
	tempMatrix.f[4] =
		-matrix.f[4] * matrix.f[10] * matrix.f[15] +
		matrix.f[4] * matrix.f[11] * matrix.f[14] +
		matrix.f[8] * matrix.f[6] * matrix.f[15] -
		matrix.f[8] * matrix.f[7] * matrix.f[14] -
		matrix.f[12] * matrix.f[6] * matrix.f[11] +
		matrix.f[12] * matrix.f[7] * matrix.f[10];
	tempMatrix.f[8] =
		matrix.f[4] * matrix.f[9] * matrix.f[15] -
		matrix.f[4] * matrix.f[11] * matrix.f[13] -
		matrix.f[8] * matrix.f[5] * matrix.f[15] +
		matrix.f[8] * matrix.f[7] * matrix.f[13] +
		matrix.f[12] * matrix.f[5] * matrix.f[11] -
		matrix.f[12] * matrix.f[7] * matrix.f[9];
	tempMatrix.f[12] =
		-matrix.f[4] * matrix.f[9] * matrix.f[14] +
		matrix.f[4] * matrix.f[10] * matrix.f[13] +
		matrix.f[8] * matrix.f[5] * matrix.f[14] -
		matrix.f[8] * matrix.f[6] * matrix.f[13] -
		matrix.f[12] * matrix.f[5] * matrix.f[10] +
		matrix.f[12] * matrix.f[6] * matrix.f[9];
	tempMatrix.f[1] =
		-matrix.f[1] * matrix.f[10] * matrix.f[15] +
		matrix.f[1] * matrix.f[11] * matrix.f[14] +
		matrix.f[9] * matrix.f[2] * matrix.f[15] -
		matrix.f[9] * matrix.f[3] * matrix.f[14] -
		matrix.f[13] * matrix.f[2] * matrix.f[11] +
		matrix.f[13] * matrix.f[3] * matrix.f[10];
	tempMatrix.f[5] =
		matrix.f[0] * matrix.f[10] * matrix.f[15] -
		matrix.f[0] * matrix.f[11] * matrix.f[14] -
		matrix.f[8] * matrix.f[2] * matrix.f[15] +
		matrix.f[8] * matrix.f[3] * matrix.f[14] +
		matrix.f[12] * matrix.f[2] * matrix.f[11] -
		matrix.f[12] * matrix.f[3] * matrix.f[10];
	tempMatrix.f[9] =
		-matrix.f[0] * matrix.f[9] * matrix.f[15] +
		matrix.f[0] * matrix.f[11] * matrix.f[13] +
		matrix.f[8] * matrix.f[1] * matrix.f[15] -
		matrix.f[8] * matrix.f[3] * matrix.f[13] -
		matrix.f[12] * matrix.f[1] * matrix.f[11] +
		matrix.f[12] * matrix.f[3] * matrix.f[9];
	tempMatrix.f[13] =
		matrix.f[0] * matrix.f[9] * matrix.f[14] -
		matrix.f[0] * matrix.f[10] * matrix.f[13] -
		matrix.f[8] * matrix.f[1] * matrix.f[14] +
		matrix.f[8] * matrix.f[2] * matrix.f[13] +
		matrix.f[12] * matrix.f[1] * matrix.f[10] -
		matrix.f[12] * matrix.f[2] * matrix.f[9];
	tempMatrix.f[2] =
		matrix.f[1] * matrix.f[6] * matrix.f[15] -
		matrix.f[1] * matrix.f[7] * matrix.f[14] -
		matrix.f[5] * matrix.f[2] * matrix.f[15] +
		matrix.f[5] * matrix.f[3] * matrix.f[14] +
		matrix.f[13] * matrix.f[2] * matrix.f[7] -
		matrix.f[13] * matrix.f[3] * matrix.f[6];
	tempMatrix.f[6] =
		-matrix.f[0] * matrix.f[6] * matrix.f[15] +
		matrix.f[0] * matrix.f[7] * matrix.f[14] +
		matrix.f[4] * matrix.f[2] * matrix.f[15] -
		matrix.f[4] * matrix.f[3] * matrix.f[14] -
		matrix.f[12] * matrix.f[2] * matrix.f[7] +
		matrix.f[12] * matrix.f[3] * matrix.f[6];
	tempMatrix.f[10] =
		matrix.f[0] * matrix.f[5] * matrix.f[15] -
		matrix.f[0] * matrix.f[7] * matrix.f[13] -
		matrix.f[4] * matrix.f[1] * matrix.f[15] +
		matrix.f[4] * matrix.f[3] * matrix.f[13] +
		matrix.f[12] * matrix.f[1] * matrix.f[7] -
		matrix.f[12] * matrix.f[3] * matrix.f[5];
	tempMatrix.f[14] =
		-matrix.f[0] * matrix.f[5] * matrix.f[14] +
		matrix.f[0] * matrix.f[6] * matrix.f[13] +
		matrix.f[4] * matrix.f[1] * matrix.f[14] -
		matrix.f[4] * matrix.f[2] * matrix.f[13] -
		matrix.f[12] * matrix.f[1] * matrix.f[6] +
		matrix.f[12] * matrix.f[2] * matrix.f[5];
	tempMatrix.f[3] =
		-matrix.f[1] * matrix.f[6] * matrix.f[11] +
		matrix.f[1] * matrix.f[7] * matrix.f[10] +
		matrix.f[5] * matrix.f[2] * matrix.f[11] -
		matrix.f[5] * matrix.f[3] * matrix.f[10] -
		matrix.f[9] * matrix.f[2] * matrix.f[7] +
		matrix.f[9] * matrix.f[3] * matrix.f[6];
	tempMatrix.f[7] =
		matrix.f[0] * matrix.f[6] * matrix.f[11] -
		matrix.f[0] * matrix.f[7] * matrix.f[10] -
		matrix.f[4] * matrix.f[2] * matrix.f[11] +
		matrix.f[4] * matrix.f[3] * matrix.f[10] +
		matrix.f[8] * matrix.f[2] * matrix.f[7] -
		matrix.f[8] * matrix.f[3] * matrix.f[6];
	tempMatrix.f[11] =
		-matrix.f[0] * matrix.f[5] * matrix.f[11] +
		matrix.f[0] * matrix.f[7] * matrix.f[9] +
		matrix.f[4] * matrix.f[1] * matrix.f[11] -
		matrix.f[4] * matrix.f[3] * matrix.f[9] -
		matrix.f[8] * matrix.f[1] * matrix.f[7] +
		matrix.f[8] * matrix.f[3] * matrix.f[5];
	tempMatrix.f[15] =
		matrix.f[0] * matrix.f[5] * matrix.f[10] -
		matrix.f[0] * matrix.f[6] * matrix.f[9] -
		matrix.f[4] * matrix.f[1] * matrix.f[10] +
		matrix.f[4] * matrix.f[2] * matrix.f[9] +
		matrix.f[8] * matrix.f[1] * matrix.f[6] -
		matrix.f[8] * matrix.f[2] * matrix.f[5];

	mat44 newMatrix;
	for(unsigned int i = 0; i < 16; i++)
	{
		newMatrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return newMatrix;
}

const mat33 Math::transposeMatrix(const mat33& matrix)
{
	mat33 newMatrix;

	for(unsigned int r = 0; r < 3; r++)
	{
		for(unsigned c = 0; c < 3; c++)
		{
			newMatrix.m[r][c] = matrix.m[c][r];
		}
	}

	return newMatrix;
}

const mat44 Math::transposeMatrix(const mat44& matrix)
{
	mat44 newMatrix;

	for(unsigned int r = 0; r < 4; r++)
	{
		for(unsigned int c = 0; c < 4; c++)
		{
			newMatrix.m[r][c] = matrix.m[c][r];
		}
	}

	return newMatrix;
}

const float Math::calculateDeterminant(const mat22& matrix)
{
	float values[2] = {};

	values[0] = (matrix.m[0][0] * matrix.m[1][1]);
	values[1] = (matrix.m[1][0] * matrix.m[0][1]);

	return (values[0] - values[1]);
}

const float Math::calculateDeterminant(const mat33& matrix)
{
	float values[3] = {};

	values[0] = (matrix.m[0][0] * ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2])));
	values[1] = (matrix.m[1][0] * ((matrix.m[0][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[0][2])));
	values[2] = (matrix.m[2][0] * ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[1][1] * matrix.m[0][2])));

	return (values[0] - values[1] + values[2]);
}

const float Math::calculateDeterminant(const mat44& matrix)
{
	float values[4] = {};

	values[0] = matrix.m[0][0] * ((matrix.m[1][1] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) + (matrix.m[1][3] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))));
	values[1] = matrix.m[0][1] * ((matrix.m[1][0] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))));
	values[2] = matrix.m[0][2] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));
	values[3] = matrix.m[0][3] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))) + (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));

	return (values[0] - values[1] + values[2] - values[3]);
}