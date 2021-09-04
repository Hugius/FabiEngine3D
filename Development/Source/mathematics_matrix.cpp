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

const Matrix44 Math::createTranslationMatrix(float x, float y, float z)
{
	// Result
	Matrix44 newMatrix;

	newMatrix.m[3][0] = x;
	newMatrix.m[3][1] = y;
	newMatrix.m[3][2] = z;

	// Return
	return newMatrix;
}

const Matrix44 Math::createScalingMatrix(float x, float y, float z)
{
	// Result
	Matrix44 newMatrix;

	newMatrix.m[0][0] = x;
	newMatrix.m[1][1] = y;
	newMatrix.m[2][2] = z;

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrix(float x, float y, float z)
{
	// Result
	Matrix44 newMatrix;

	newMatrix = (newMatrix * createRotationMatrixY(y));
	newMatrix = (newMatrix * createRotationMatrixX(x));
	newMatrix = (newMatrix * createRotationMatrixZ(z));

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrixX(float angle)
{
	// Result
	Matrix44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[1][0] = -sin(angle);
	newMatrix.m[0][1] = sin(angle);
	newMatrix.m[1][1] = cos(angle);

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrixY(float angle)
{
	// Result
	Matrix44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[0][2] = -sin(angle);
	newMatrix.m[2][0] = sin(angle);
	newMatrix.m[2][2] = cos(angle);

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrixZ(float angle)
{
	// Result
	Matrix44 newMatrix;

	newMatrix.m[1][1] = cos(angle);
	newMatrix.m[1][2] = sin(angle);
	newMatrix.m[2][1] = -sin(angle);
	newMatrix.m[2][2] = cos(angle);

	// Return
	return newMatrix;
}

const Matrix44 Math::createOrthoMatrix(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[0][0] = 2.0f / (right - left);
	newMatrix.m[1][1] = 2.0f / (top - bottom);
	newMatrix.m[2][2] = -2.0f / (farZ - nearZ);
	newMatrix.m[3][0] = -((right + left) / (right - left));
	newMatrix.m[3][1] = -((top + bottom) / (top - bottom));
	newMatrix.m[3][2] = -((farZ + nearZ) / (farZ - nearZ));

	// Return
	return newMatrix;
};

const Matrix44 Math::createViewMatrix(Vec3 eye, Vec3 center, Vec3 up)
{
	// Temporary values
	Vec3 frontVector = normalizeVector(center - eye);
	Vec3 rightVector = normalizeVector(calculateCrossProduct(frontVector, up));
	Vec3 upVector = calculateCrossProduct(rightVector, frontVector);

	// Result
	Matrix44 newMatrix(1.0f);

	// Create
	newMatrix.m[0][0] = rightVector.x;
	newMatrix.m[1][0] = rightVector.y;
	newMatrix.m[2][0] = rightVector.z;
	newMatrix.m[0][1] = upVector.x;
	newMatrix.m[1][1] = upVector.y;
	newMatrix.m[2][1] = upVector.z;
	newMatrix.m[0][2] = -(frontVector.x);
	newMatrix.m[1][2] = -(frontVector.y);
	newMatrix.m[2][2] = -(frontVector.z);
	newMatrix.m[3][0] = -(calculateDotProduct(rightVector, eye));
	newMatrix.m[3][1] = -(calculateDotProduct(upVector, eye));
	newMatrix.m[3][2] = calculateDotProduct(frontVector, eye);

	// Return
	return newMatrix;
}

const Matrix44 Math::createProjectionMatrix(float fovY, float aspect, float nearZ, float farZ)
{
	// Temporary values
	const float tanHalfFov = tan(fovY / 2.0f);

	// Create
	Matrix44 newMatrix(0.0f);
	newMatrix.m[0][0] = 1.0f / (aspect * tanHalfFov);
	newMatrix.m[1][1] = 1.0f / tanHalfFov;
	newMatrix.m[2][2] = -((farZ + nearZ) / (farZ - nearZ));
	newMatrix.m[2][3] = -1.0f;
	newMatrix.m[3][2] = -((2.0f * farZ * nearZ) / (farZ - nearZ));

	// Return
	return newMatrix;
}