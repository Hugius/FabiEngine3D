#include "mathematics.hpp"

const mat22 Math::invertMatrix(mat22 matrix)
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

	for(unsigned int i = 0; i < 4; i++)
	{
		matrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return matrix;
}

const mat33 Math::invertMatrix(mat33 matrix)
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

	for(unsigned int i = 0; i < 9; i++)
	{
		matrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return matrix;
}

const mat44 Math::invertMatrix(mat44 matrix)
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

	for(unsigned int i = 0; i < 16; i++)
	{
		matrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	return matrix;
}

const mat33 Math::transposeMatrix(mat33 matrix)
{
	mat33 tempMatrix;
	for(unsigned int i = 0; i < 9; i++)
	{
		tempMatrix.f[i] = matrix.f[i];
	}

	for(unsigned int r = 0; r < 3; r++)
	{
		for(unsigned c = 0; c < 3; c++)
		{
			matrix.m[r][c] = tempMatrix.m[c][r];
		}
	}

	return matrix;
}

const mat44 Math::transposeMatrix(mat44 matrix)
{
	mat44 tempMatrix;
	for(int i = 0; i < 16; i++)
	{
		tempMatrix.f[i] = matrix.f[i];
	}

	for(unsigned int r = 0; r < 4; r++)
	{
		for(unsigned int c = 0; c < 4; c++)
		{
			matrix.m[r][c] = tempMatrix.m[c][r];
		}
	}

	return matrix;
}

const float Math::calculateDeterminant(mat22 matrix)
{
	float values[2] = {};

	values[0] = (matrix.m[0][0] * matrix.m[1][1]);
	values[1] = (matrix.m[1][0] * matrix.m[0][1]);

	return (values[0] - values[1]);
}

const float Math::calculateDeterminant(mat33 matrix)
{
	float values[3] = {};

	values[0] = (matrix.m[0][0] * ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2])));
	values[1] = (matrix.m[1][0] * ((matrix.m[0][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[0][2])));
	values[2] = (matrix.m[2][0] * ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[1][1] * matrix.m[0][2])));

	return (values[0] - values[1] + values[2]);
}

const float Math::calculateDeterminant(mat44 matrix)
{
	float values[4] = {};

	values[0] = matrix.m[0][0] * ((matrix.m[1][1] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) + (matrix.m[1][3] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))));
	values[1] = matrix.m[0][1] * ((matrix.m[1][0] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))));
	values[2] = matrix.m[0][2] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));
	values[3] = matrix.m[0][3] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))) + (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));

	return (values[0] - values[1] + values[2] - values[3]);
}