#include "mathematics.hpp"

const mat44 Math::createTranslationMatrixX(float value)
{
	mat44 newMatrix;

	newMatrix.m[3][0] = value;

	return newMatrix;
}

const mat44 Math::createTranslationMatrixY(float value)
{
	mat44 newMatrix;

	newMatrix.m[3][1] = value;

	return newMatrix;
}

const mat44 Math::createTranslationMatrixZ(float value)
{
	mat44 newMatrix;

	newMatrix.m[3][2] = value;

	return newMatrix;
}

const mat44 Math::createTranslationMatrix(float x, float y, float z)
{
	mat44 newMatrix;

	newMatrix.m[3][0] = x;
	newMatrix.m[3][1] = y;
	newMatrix.m[3][2] = z;

	return newMatrix;
}

const mat44 Math::createScalingMatrix(float x, float y, float z)
{
	mat44 newMatrix;

	newMatrix.m[0][0] = x;
	newMatrix.m[1][1] = y;
	newMatrix.m[2][2] = z;

	return newMatrix;
}

const mat44 Math::createScalingMatrixX(float value)
{
	mat44 newMatrix;

	newMatrix.m[0][0] = value;

	return newMatrix;
}

const mat44 Math::createScalingMatrixY(float value)
{
	mat44 newMatrix;

	newMatrix.m[1][1] = value;

	return newMatrix;
}

const mat44 Math::createScalingMatrixZ(float value)
{
	mat44 newMatrix;

	newMatrix.m[2][2] = value;

	return newMatrix;
}

const mat44 Math::createRotationMatrix(float x, float y, float z, DirectionOrder order)
{
	mat44 newMatrix;

	if(order == DirectionOrder::XYZ)
	{
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
	}
	else if(order == DirectionOrder::XZY)
	{
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixY(y));
	}
	else if(order == DirectionOrder::YXZ)
	{
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
	}
	else if(order == DirectionOrder::YZX)
	{
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixX(x));
	}
	else if(order == DirectionOrder::ZXY)
	{
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixX(x));
		newMatrix = (newMatrix * createRotationMatrixY(y));
	}
	else if(order == DirectionOrder::ZYX)
	{
		newMatrix = (newMatrix * createRotationMatrixZ(z));
		newMatrix = (newMatrix * createRotationMatrixY(y));
		newMatrix = (newMatrix * createRotationMatrixX(x));
	}

	return newMatrix;
}

const mat44 Math::createRotationMatrixX(float angle)
{
	mat44 newMatrix;

	newMatrix.m[1][1] = cos(angle);
	newMatrix.m[1][2] = sin(angle);
	newMatrix.m[2][1] = -sin(angle);
	newMatrix.m[2][2] = cos(angle);

	return newMatrix;
}

const mat44 Math::createRotationMatrixY(float angle)
{
	mat44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[0][2] = -sin(angle);
	newMatrix.m[2][0] = sin(angle);
	newMatrix.m[2][2] = cos(angle);

	return newMatrix;
}

const mat44 Math::createRotationMatrixZ(float angle)
{
	mat44 newMatrix;

	newMatrix.m[0][0] = cos(angle);
	newMatrix.m[1][0] = -sin(angle);
	newMatrix.m[0][1] = sin(angle);
	newMatrix.m[1][1] = cos(angle);

	return newMatrix;
}

const mat44 Math::createOrthographicProjectionMatrix(float left, float right, float bottom, float top, float near, float far)
{
	mat44 newMatrix;

	newMatrix.m[0][0] = 2.0f / (right - left);
	newMatrix.m[1][1] = 2.0f / (top - bottom);
	newMatrix.m[2][2] = -2.0f / (far - near);
	newMatrix.m[3][0] = -((right + left) / (right - left));
	newMatrix.m[3][1] = -((top + bottom) / (top - bottom));
	newMatrix.m[3][2] = -((far + near) / (far - near));

	return newMatrix;
};

const mat44 Math::createViewMatrix(fvec3 eye, fvec3 center, fvec3 up)
{
	fvec3 frontVector = normalize(center - eye);
	fvec3 rightVector = normalize(calculateCrossProduct(frontVector, up));
	fvec3 upVector = calculateCrossProduct(rightVector, frontVector);

	mat44 newMatrix(1.0f);

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

	return newMatrix;
}

const mat44 Math::createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far)
{
	const float tanHalfFovY = tan(fov / 2.0f);

	mat44 newMatrix(0.0f);
	newMatrix.m[0][0] = 1.0f / (aspect * tanHalfFovY);
	newMatrix.m[1][1] = 1.0f / tanHalfFovY;
	newMatrix.m[2][2] = -((far + near) / (far - near));
	newMatrix.m[2][3] = -1.0f;
	newMatrix.m[3][2] = -((2.0f * far * near) / (far - near));

	return newMatrix;
}