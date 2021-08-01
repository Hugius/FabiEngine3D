#include "matrix44.hpp"

const float Matrix44::getDeterminant()
{
	float values[4];

	values[0] = this->m[0][0] * ((this->m[1][1] * ((this->m[2][2] * this->m[3][3]) - (this->m[2][3] * this->m[3][2]))) - (this->m[1][2] * ((this->m[2][1] * this->m[3][3]) - (this->m[2][3] * this->m[3][1]))) + (this->m[1][3] * ((this->m[2][1] * this->m[3][2]) - (this->m[2][2] * this->m[3][1]))));
	values[1] = this->m[0][1] * ((this->m[1][0] * ((this->m[2][2] * this->m[3][3]) - (this->m[2][3] * this->m[3][2]))) - (this->m[1][2] * ((this->m[2][0] * this->m[3][3]) - (this->m[2][3] * this->m[3][0]))) + (this->m[1][3] * ((this->m[2][0] * this->m[3][2]) - (this->m[2][2] * this->m[3][0]))));
	values[2] = this->m[0][2] * ((this->m[1][0] * ((this->m[2][1] * this->m[3][3]) - (this->m[2][3] * this->m[3][1]))) - (this->m[1][1] * ((this->m[2][0] * this->m[3][3]) - (this->m[2][3] * this->m[3][0]))) + (this->m[1][3] * ((this->m[2][0] * this->m[3][1]) - (this->m[2][1] * this->m[3][0]))));
	values[3] = this->m[0][3] * ((this->m[1][0] * ((this->m[2][1] * this->m[3][2]) - (this->m[2][2] * this->m[3][1]))) - (this->m[1][1] * ((this->m[2][0] * this->m[3][2]) - (this->m[2][2] * this->m[3][0]))) + (this->m[1][2] * ((this->m[2][0] * this->m[3][1]) - (this->m[2][1] * this->m[3][0]))));
	
	return (values[0] - values[1] + values[2] - values[3]);
}

const bool Matrix44::invert()
{
	// Calculate determinant
	float determinant = this->getDeterminant();

	// Check if determinant is invalid
	if (determinant == 0.0f)
	{
		return false;
	}

	// Result
	Matrix44 newMatrix;

	// Calculate
	newMatrix.f[0] =
		this->f[5] * this->f[10] * this->f[15] -
		this->f[5] * this->f[11] * this->f[14] -
		this->f[9] * this->f[6] * this->f[15] +
		this->f[9] * this->f[7] * this->f[14] +
		this->f[13] * this->f[6] * this->f[11] -
		this->f[13] * this->f[7] * this->f[10];
	newMatrix.f[4] =
		-this->f[4] * this->f[10] * this->f[15] +
		this->f[4] * this->f[11] * this->f[14] +
		this->f[8] * this->f[6] * this->f[15] -
		this->f[8] * this->f[7] * this->f[14] -
		this->f[12] * this->f[6] * this->f[11] +
		this->f[12] * this->f[7] * this->f[10];
	newMatrix.f[8] =
		this->f[4] * this->f[9] * this->f[15] -
		this->f[4] * this->f[11] * this->f[13] -
		this->f[8] * this->f[5] * this->f[15] +
		this->f[8] * this->f[7] * this->f[13] +
		this->f[12] * this->f[5] * this->f[11] -
		this->f[12] * this->f[7] * this->f[9];
	newMatrix.f[12] =
		-this->f[4] * this->f[9] * this->f[14] +
		this->f[4] * this->f[10] * this->f[13] +
		this->f[8] * this->f[5] * this->f[14] -
		this->f[8] * this->f[6] * this->f[13] -
		this->f[12] * this->f[5] * this->f[10] +
		this->f[12] * this->f[6] * this->f[9];
	newMatrix.f[1] =
		-this->f[1] * this->f[10] * this->f[15] +
		this->f[1] * this->f[11] * this->f[14] +
		this->f[9] * this->f[2] * this->f[15] -
		this->f[9] * this->f[3] * this->f[14] -
		this->f[13] * this->f[2] * this->f[11] +
		this->f[13] * this->f[3] * this->f[10];
	newMatrix.f[5] =
		this->f[0] * this->f[10] * this->f[15] -
		this->f[0] * this->f[11] * this->f[14] -
		this->f[8] * this->f[2] * this->f[15] +
		this->f[8] * this->f[3] * this->f[14] +
		this->f[12] * this->f[2] * this->f[11] -
		this->f[12] * this->f[3] * this->f[10];
	newMatrix.f[9] =
		-this->f[0] * this->f[9] * this->f[15] +
		this->f[0] * this->f[11] * this->f[13] +
		this->f[8] * this->f[1] * this->f[15] -
		this->f[8] * this->f[3] * this->f[13] -
		this->f[12] * this->f[1] * this->f[11] +
		this->f[12] * this->f[3] * this->f[9];
	newMatrix.f[13] =
		this->f[0] * this->f[9] * this->f[14] -
		this->f[0] * this->f[10] * this->f[13] -
		this->f[8] * this->f[1] * this->f[14] +
		this->f[8] * this->f[2] * this->f[13] +
		this->f[12] * this->f[1] * this->f[10] -
		this->f[12] * this->f[2] * this->f[9];
	newMatrix.f[2] =
		this->f[1] * this->f[6] * this->f[15] -
		this->f[1] * this->f[7] * this->f[14] -
		this->f[5] * this->f[2] * this->f[15] +
		this->f[5] * this->f[3] * this->f[14] +
		this->f[13] * this->f[2] * this->f[7] -
		this->f[13] * this->f[3] * this->f[6];
	newMatrix.f[6] =
		-this->f[0] * this->f[6] * this->f[15] +
		this->f[0] * this->f[7] * this->f[14] +
		this->f[4] * this->f[2] * this->f[15] -
		this->f[4] * this->f[3] * this->f[14] -
		this->f[12] * this->f[2] * this->f[7] +
		this->f[12] * this->f[3] * this->f[6];
	newMatrix.f[10] =
		this->f[0] * this->f[5] * this->f[15] -
		this->f[0] * this->f[7] * this->f[13] -
		this->f[4] * this->f[1] * this->f[15] +
		this->f[4] * this->f[3] * this->f[13] +
		this->f[12] * this->f[1] * this->f[7] -
		this->f[12] * this->f[3] * this->f[5];
	newMatrix.f[14] =
		-this->f[0] * this->f[5] * this->f[14] +
		this->f[0] * this->f[6] * this->f[13] +
		this->f[4] * this->f[1] * this->f[14] -
		this->f[4] * this->f[2] * this->f[13] -
		this->f[12] * this->f[1] * this->f[6] +
		this->f[12] * this->f[2] * this->f[5];
	newMatrix.f[3] =
		-this->f[1] * this->f[6] * this->f[11] +
		this->f[1] * this->f[7] * this->f[10] +
		this->f[5] * this->f[2] * this->f[11] -
		this->f[5] * this->f[3] * this->f[10] -
		this->f[9] * this->f[2] * this->f[7] +
		this->f[9] * this->f[3] * this->f[6];
	newMatrix.f[7] =
		this->f[0] * this->f[6] * this->f[11] -
		this->f[0] * this->f[7] * this->f[10] -
		this->f[4] * this->f[2] * this->f[11] +
		this->f[4] * this->f[3] * this->f[10] +
		this->f[8] * this->f[2] * this->f[7] -
		this->f[8] * this->f[3] * this->f[6];
	newMatrix.f[11] =
		-this->f[0] * this->f[5] * this->f[11] +
		this->f[0] * this->f[7] * this->f[9] +
		this->f[4] * this->f[1] * this->f[11] -
		this->f[4] * this->f[3] * this->f[9] -
		this->f[8] * this->f[1] * this->f[7] +
		this->f[8] * this->f[3] * this->f[5];
	newMatrix.f[15] =
		this->f[0] * this->f[5] * this->f[10] -
		this->f[0] * this->f[6] * this->f[9] -
		this->f[4] * this->f[1] * this->f[10] +
		this->f[4] * this->f[2] * this->f[9] +
		this->f[8] * this->f[1] * this->f[6] -
		this->f[8] * this->f[2] * this->f[5];

	// Multiply
	for (unsigned int i = 0; i <  16; i++)
	{
		this->f[i] = (newMatrix.f[i] * (1.0f / determinant));
	}

	// Return
	return true;
}

void Matrix44::transpose()
{
	// Copy current matrix to temporary matrix
	Matrix44 tempMatrix;
	for (int i = 0; i < 16; i++)
	{
		tempMatrix.f[i] = this->f[i];
	}

	// Swap rows and columns
	for (unsigned int r = 0; r < 4; r++)
	{
		for (unsigned int c = 0; c < 4; c++)
		{
			this->m[r][c] = tempMatrix.m[c][r];
		}
	}
}

const Matrix44 Matrix44::createTranslation(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix.m[3][0] = x;
	newMatrix.m[3][1] = y;
	newMatrix.m[3][2] = z;

	return newMatrix;
}

const Matrix44 Matrix44::createScaling(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = x;
	newMatrix.m[1][1] = y;
	newMatrix.m[2][2] = z;

	return newMatrix;
}

const Matrix44 Matrix44::createRotation(float x, float y, float z)
{
	Matrix44 newMatrix;

	newMatrix = newMatrix * createRotationY(y);
	newMatrix = newMatrix * createRotationX(x);
	newMatrix = newMatrix * createRotationZ(z);

	return newMatrix;
}

const Matrix44 Matrix44::createRotationX(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[1][0] = -sin(angle);
	newMatrix.m[0][1] = sin(angle);
	newMatrix.m[1][1] = cos(angle);

	return newMatrix;
}

const Matrix44 Matrix44::createRotationY(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[0][2] = -sin(angle);
	newMatrix.m[2][0] = sin(angle);
	newMatrix.m[2][2] = cos(angle);

	return newMatrix;
}

const Matrix44 Matrix44::createRotationZ(float angle)
{
	Matrix44 newMatrix;

	newMatrix.m[1][1] = cos(angle);
	newMatrix.m[1][2] = sin(angle);
	newMatrix.m[2][1] = -sin(angle);
	newMatrix.m[2][2] = cos(angle);

	return newMatrix;
}

const Matrix44 Matrix44::createOrtho(float left, float right, float bottom, float top, float nearZ, float farZ)
{
	Matrix44 newMatrix;

	newMatrix.m[0][0] = 2.0f / (right - left);
	newMatrix.m[1][1] = 2.0f / (top - bottom);
	newMatrix.m[2][2] = -2.0f / (farZ - nearZ);
	newMatrix.m[3][0] = -((right + left) / (right - left));
	newMatrix.m[3][1] = -((top + bottom) / (top - bottom));
	newMatrix.m[3][2] = -((farZ + nearZ) / (farZ - nearZ));

	return newMatrix;
};

const Matrix44 Matrix44::createProjection(float fovY, float aspect, float nearZ, float farZ)
{
	// Pre-calculate
	float tanHalfFov = tan(fovY / 2.0f);

	// Create projection matrix
	Matrix44 newMatrix(0.0f);
	newMatrix.m[0][0] = 1.0f / (aspect * tanHalfFov);
	newMatrix.m[1][1] = 1.0f / tanHalfFov;
	newMatrix.m[2][2] = -((farZ + nearZ) / (farZ - nearZ));
	newMatrix.m[2][3] = -1.0f;
	newMatrix.m[3][2] = -((2.0f * farZ * nearZ) / (farZ - nearZ));
	return newMatrix;
}

const Matrix44 Matrix44::createView
(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	// Calculate direction vectors
	Vec3 frontVector = (center - eye);
	frontVector.normalize();
	Vec3 rightVector = frontVector.cross(up);
	rightVector.normalize();
	Vec3 upVector = rightVector.cross(frontVector);

	// Create view matrix
	Matrix44 newMatrix(1.0f);
	newMatrix.m[0][0] = rightVector.x;
	newMatrix.m[1][0] = rightVector.y;
	newMatrix.m[2][0] = rightVector.z;
	newMatrix.m[0][1] = upVector.x;
	newMatrix.m[1][1] = upVector.y;
	newMatrix.m[2][1] = upVector.z;
	newMatrix.m[0][2] = -frontVector.x;
	newMatrix.m[1][2] = -frontVector.y;
	newMatrix.m[2][2] = -frontVector.z;
	newMatrix.m[3][0] = -(rightVector.dot(eye));
	newMatrix.m[3][1] = -(upVector.dot(eye));
	newMatrix.m[3][2] = frontVector.dot(eye);
	return newMatrix;
}