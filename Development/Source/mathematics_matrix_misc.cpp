#include "mathematics.hpp"

const Matrix33 Math::invertMatrix(Matrix33 matrix)
{
	// Calculate determinant
	auto determinant = calculateDeterminant(matrix);

	// Check if determinant is invalid
	if (determinant == 0.0f)
	{
		return Matrix33(0.0f);
	}

	// Result
	Matrix33 tempMatrix;

	// Calculate
	tempMatrix.f[0] = ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2]));
	tempMatrix.f[1] = ((matrix.m[0][2] * matrix.m[2][1]) - (matrix.m[0][1] * matrix.m[2][2]));
	tempMatrix.f[2] = ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[0][2] * matrix.m[1][1]));
	tempMatrix.f[3] = ((matrix.m[1][2] * matrix.m[2][0]) - (matrix.m[1][0] * matrix.m[2][2]));
	tempMatrix.f[4] = ((matrix.m[0][0] * matrix.m[2][2]) - (matrix.m[0][2] * matrix.m[2][0]));
	tempMatrix.f[5] = ((matrix.m[1][0] * matrix.m[0][2]) - (matrix.m[0][0] * matrix.m[1][2]));
	tempMatrix.f[6] = ((matrix.m[1][0] * matrix.m[2][1]) - (matrix.m[2][0] * matrix.m[1][1]));
	tempMatrix.f[7] = ((matrix.m[2][0] * matrix.m[0][1]) - (matrix.m[0][0] * matrix.m[2][1]));
	tempMatrix.f[8] = ((matrix.m[0][0] * matrix.m[1][1]) - (matrix.m[1][0] * matrix.m[0][1]));

	// Multiply
	for (unsigned int i = 0; i < 9; i++)
	{
		matrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	// Return
	return matrix;
}

const Matrix44 Math::invertMatrix(Matrix44 matrix)
{
	// Calculate determinant
	auto determinant = calculateDeterminant(matrix);

	// Check if determinant is invalid
	if (determinant == 0.0f)
	{
		return Matrix44(0.0f);
	}

	// Result
	Matrix44 tempMatrix;

	// Calculate
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

	// Multiply
	for (unsigned int i = 0; i < 16; i++)
	{
		matrix.f[i] = (tempMatrix.f[i] * (1.0f / determinant));
	}

	// Return
	return matrix;
}

const Matrix33 Math::transposeMatrix(Matrix33 matrix)
{
	// Copy current matrix to temporary matrix
	Matrix33 tempMatrix;
	for (unsigned int i = 0; i < 9; i++)
	{
		tempMatrix.f[i] = matrix.f[i];
	}

	// Swap rows and columns
	for (unsigned int r = 0; r < 3; r++)
	{
		for (unsigned c = 0; c < 3; c++)
		{
			matrix.m[r][c] = tempMatrix.m[c][r];
		}
	}

	// Return
	return matrix;
}

const Matrix44 Math::transposeMatrix(Matrix44 matrix)
{
	// Copy current matrix to temporary matrix
	Matrix44 tempMatrix;
	for (int i = 0; i < 16; i++)
	{
		tempMatrix.f[i] = matrix.f[i];
	}

	// Swap rows and columns
	for (unsigned int r = 0; r < 4; r++)
	{
		for (unsigned int c = 0; c < 4; c++)
		{
			matrix.m[r][c] = tempMatrix.m[c][r];
		}
	}

	// Return
	return matrix;
}

const float Math::calculateDeterminant(Matrix33 matrix)
{
	// Result
	float values[3];

	// Calculate
	values[0] = (matrix.m[0][0] * ((matrix.m[1][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[1][2])));
	values[1] = (matrix.m[1][0] * ((matrix.m[0][1] * matrix.m[2][2]) - (matrix.m[2][1] * matrix.m[0][2])));
	values[2] = (matrix.m[2][0] * ((matrix.m[0][1] * matrix.m[1][2]) - (matrix.m[1][1] * matrix.m[0][2])));

	// Return
	return (values[0] - values[1] + values[2]);
}

const float Math::calculateDeterminant(Matrix44 matrix)
{
	// Result
	float values[4];

	// Calculate
	values[0] = matrix.m[0][0] * ((matrix.m[1][1] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) + (matrix.m[1][3] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))));
	values[1] = matrix.m[0][1] * ((matrix.m[1][0] * ((matrix.m[2][2] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][2]))) - (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))));
	values[2] = matrix.m[0][2] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][3]) - (matrix.m[2][3] * matrix.m[3][0]))) + (matrix.m[1][3] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));
	values[3] = matrix.m[0][3] * ((matrix.m[1][0] * ((matrix.m[2][1] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][1]))) - (matrix.m[1][1] * ((matrix.m[2][0] * matrix.m[3][2]) - (matrix.m[2][2] * matrix.m[3][0]))) + (matrix.m[1][2] * ((matrix.m[2][0] * matrix.m[3][1]) - (matrix.m[2][1] * matrix.m[3][0]))));

	// Return
	return (values[0] - values[1] + values[2] - values[3]);
}