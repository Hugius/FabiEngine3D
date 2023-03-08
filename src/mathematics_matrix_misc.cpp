#include "mathematics.hpp"

const fmat22 Mathematics::invertMatrix(const fmat22 & matrix)
{
	const auto determinant = calculateDeterminant(matrix);

	if(determinant == 0.0f)
	{
		return fmat22(0.0f);
	}

	fmat22 tempMatrix;
	tempMatrix.f[0] = matrix.f[3];
	tempMatrix.f[1] = -matrix.f[1];
	tempMatrix.f[2] = -matrix.f[2];
	tempMatrix.f[3] = matrix.f[0];

	fmat22 result;
	for(int index = 0; index < 4; index++)
	{
		result.f[index] = (tempMatrix.f[index] * (1.0f / determinant));
	}

	return result;
}

const fmat22 Mathematics::transposeMatrix(const fmat22 & matrix)
{
	fmat22 result = {};

	for(int rowIndex = 0; rowIndex < 2; rowIndex++)
	{
		for(unsigned columnIndex = 0; columnIndex < 2; columnIndex++)
		{
			result.m[rowIndex][columnIndex] = matrix.m[columnIndex][rowIndex];
		}
	}

	return result;
}

const fmat33 Mathematics::invertMatrix(const fmat33 & matrix)
{
	const auto determinant = calculateDeterminant(matrix);

	if(determinant == 0.0f)
	{
		return fmat33(0.0f);
	}

	fmat33 tempMatrix;
	tempMatrix.f[0] = ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2]));
	tempMatrix.f[1] = ((matrix.m[0][2] * matrix.m[2][1]) - (matrix.m[0][1] * matrix.m[2][2]));
	tempMatrix.f[2] = ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[0][2] * matrix.m[1][1]));
	tempMatrix.f[3] = ((matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[1][0] * matrix.m[2][2]));
	tempMatrix.f[4] = ((matrix.m[0][0] * matrix.m[2][2]) - (matrix.m[0][2] * matrix.m[2][0]));
	tempMatrix.f[5] = ((matrix.m[1][0] * matrix.m[0][2]) - (matrix.m[0][0] * matrix.m[1][2]));
	tempMatrix.f[6] = ((matrix.m[1][0] * matrix.m[2][1]) - (matrix.m[2][0] * matrix.m[1][1]));
	tempMatrix.f[7] = ((matrix.m[2][0] * matrix.m[0][1]) - (matrix.m[0][0] * matrix.m[2][1]));
	tempMatrix.f[8] = ((matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[1][0] * matrix.m[0][1]));

	fmat33 result;
	for(int index = 0; index < 9; index++)
	{
		result.f[index] = (tempMatrix.f[index] * (1.0f / determinant));
	}

	return result;
}

const fmat44 Mathematics::invertMatrix(const fmat44 & matrix)
{
	const auto determinant = calculateDeterminant(matrix);

	if(determinant == 0.0f)
	{
		return fmat44(0.0f);
	}

	fmat44 tempMatrix;
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

	fmat44 result;
	for(int index = 0; index < 16; index++)
	{
		result.f[index] = (tempMatrix.f[index] * (1.0f / determinant));
	}

	return result;
}

const fmat33 Mathematics::transposeMatrix(const fmat33 & matrix)
{
	fmat33 result = {};

	for(int rowIndex = 0; rowIndex < 3; rowIndex++)
	{
		for(unsigned columnIndex = 0; columnIndex < 3; columnIndex++)
		{
			result.m[rowIndex][columnIndex] = matrix.m[columnIndex][rowIndex];
		}
	}

	return result;
}

const fmat44 Mathematics::transposeMatrix(const fmat44 & matrix)
{
	fmat44 result = {};

	for(int rowIndex = 0; rowIndex < 4; rowIndex++)
	{
		for(int columnIndex = 0; columnIndex < 4; columnIndex++)
		{
			result.m[rowIndex][columnIndex] = matrix.m[columnIndex][rowIndex];
		}
	}

	return result;
}

const float Mathematics::calculateDeterminant(const fmat22 & matrix)
{
	float values[2] = {};

	values[0] = (matrix.m[0][0] * matrix.m[1][1]);
	values[1] = (matrix.m[1][0] * matrix.m[0][1]);

	return (values[0] - values[1]);
}

const float Mathematics::calculateDeterminant(const fmat33 & matrix)
{
	float values[3] = {};

	values[0] = (matrix.m[0][0] * ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2])));
	values[1] = (matrix.m[1][0] * ((matrix.m[0][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[0][2])));
	values[2] = (matrix.m[2][0] * ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[1][1] * matrix.m[0][2])));

	return (values[0] - values[1] + values[2]);
}

const float Mathematics::calculateDeterminant(const fmat44 & matrix)
{
	float values[4] = {};

	values[0] = matrix.m[0][0] * ((matrix.m[1][1] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) + (matrix.m[1][3] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))));
	values[1] = matrix.m[0][1] * ((matrix.m[1][0] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))));
	values[2] = matrix.m[0][2] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));
	values[3] = matrix.m[0][3] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))) + (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));

	return (values[0] - values[1] + values[2] - values[3]);
}