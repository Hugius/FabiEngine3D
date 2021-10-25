#include "mathematics.hpp"

const Matrix44 Math::createTranslationMatrixX(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[3][0] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createTranslationMatrixY(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[3][1] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createTranslationMatrixZ(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[3][2] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createTranslationMatrix(float x, float y, float z)
{
	// Result
	Matrix44 newMatrix;

	// Create
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

	// Create
	newMatrix.m[0][0] = x;
	newMatrix.m[1][1] = y;
	newMatrix.m[2][2] = z;

	// Return
	return newMatrix;
}

const Matrix44 Math::createScalingMatrixX(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[0][0] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createScalingMatrixY(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[1][1] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createScalingMatrixZ(float value)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[2][2] = value;

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrix(float x, float y, float z, DirectionOrder order)
{
	// Result
	Matrix44 newMatrix;

	// Create
	if (order == DirectionOrder::XYZ)
	{
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
	}
	else if (order == DirectionOrder::XZY)
	{
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixY(y));
	}
	else if (order == DirectionOrder::YXZ)
	{
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
	}
	else if (order == DirectionOrder::YZX)
	{
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixX(x));
	}
	else if (order == DirectionOrder::ZXY)
	{
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixY(y));
	}
	else if (order == DirectionOrder::ZYX)
	{
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixX(x));
	}

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrixX(float angle)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[1][1] = cos(angle);
	newMatrix.m[1][2] = sin(angle);
	newMatrix.m[2][1] = -sin(angle);
	newMatrix.m[2][2] = cos(angle);

	// Return
	return newMatrix;
}

const Matrix44 Math::createRotationMatrixY(float angle)
{
	// Result
	Matrix44 newMatrix;

	// Create
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

	// Create
	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[1][0] = -sin(angle);
	newMatrix.m[0][1] = sin(angle);
	newMatrix.m[1][1] = cos(angle);

	// Return
	return newMatrix;
}

const Matrix44 Math::createOrthoMatrix(float left, float right, float bottom, float top, float near, float far)
{
	// Result
	Matrix44 newMatrix;

	// Create
	newMatrix.m[0][0] = 2.0f / (right - left);
	newMatrix.m[1][1] = 2.0f / (top - bottom);
	newMatrix.m[2][2] = -2.0f / (far - near);
	newMatrix.m[3][0] = -((right + left) / (right - left));
	newMatrix.m[3][1] = -((top + bottom) / (top - bottom));
	newMatrix.m[3][2] = -((far + near) / (far - near));

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

const Matrix44 Math::createProjectionMatrix(float fov, float aspect, float near, float far)
{
	// Temporary values
	const float tanHalfFovY = tan(fov / 2.0f);

	// Create
	Matrix44 newMatrix(0.0f);
	newMatrix.m[0][0] = 1.0f / (aspect * tanHalfFovY);
	newMatrix.m[1][1] = 1.0f / tanHalfFovY;
	newMatrix.m[2][2] = -((far + near) / (far - near));
	newMatrix.m[2][3] = -1.0f;
	newMatrix.m[3][2] = -((2.0f * far * near) / (far - near));

	// Return
	return newMatrix;
}