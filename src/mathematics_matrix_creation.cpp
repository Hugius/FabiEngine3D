#include "mathematics.hpp"

const mat44 Math::createTranslationMatrixX(float value)
{
	mat44 result;

	result.m[3][0] = value;

	return result;
}

const mat44 Math::createTranslationMatrixY(float value)
{
	mat44 result;

	result.m[3][1] = value;

	return result;
}

const mat44 Math::createTranslationMatrixZ(float value)
{
	mat44 result;

	result.m[3][2] = value;

	return result;
}

const mat44 Math::createTranslationMatrix(float x, float y, float z)
{
	mat44 result;

	result.m[3][0] = x;
	result.m[3][1] = y;
	result.m[3][2] = z;

	return result;
}

const mat44 Math::createScalingMatrix(float x, float y, float z)
{
	mat44 result;

	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;

	return result;
}

const mat44 Math::createScalingMatrixX(float value)
{
	mat44 result;

	result.m[0][0] = value;

	return result;
}

const mat44 Math::createScalingMatrixY(float value)
{
	mat44 result;

	result.m[1][1] = value;

	return result;
}

const mat44 Math::createScalingMatrixZ(float value)
{
	mat44 result;

	result.m[2][2] = value;

	return result;
}

const mat44 Math::createRotationMatrix(float x, float y, float z, DirectionOrder order)
{
	mat44 result;

	if(order == DirectionOrder::XYZ)
	{
		result = (result * createRotationMatrixX(x));
		result = (result * createRotationMatrixY(y));
		result = (result * createRotationMatrixZ(z));
	}
	else if(order == DirectionOrder::XZY)
	{
		result = (result * createRotationMatrixX(x));
		result = (result * createRotationMatrixZ(z));
		result = (result * createRotationMatrixY(y));
	}
	else if(order == DirectionOrder::YXZ)
	{
		result = (result * createRotationMatrixY(y));
		result = (result * createRotationMatrixX(x));
		result = (result * createRotationMatrixZ(z));
	}
	else if(order == DirectionOrder::YZX)
	{
		result = (result * createRotationMatrixY(y));
		result = (result * createRotationMatrixZ(z));
		result = (result * createRotationMatrixX(x));
	}
	else if(order == DirectionOrder::ZXY)
	{
		result = (result * createRotationMatrixZ(z));
		result = (result * createRotationMatrixX(x));
		result = (result * createRotationMatrixY(y));
	}
	else if(order == DirectionOrder::ZYX)
	{
		result = (result * createRotationMatrixZ(z));
		result = (result * createRotationMatrixY(y));
		result = (result * createRotationMatrixX(x));
	}

	return result;
}

const mat44 Math::createRotationMatrixX(float angle)
{
	mat44 result;

	result.m[1][1] = cos(angle);
	result.m[1][2] = sin(angle);
	result.m[2][1] = -sin(angle);
	result.m[2][2] = cos(angle);

	return result;
}

const mat44 Math::createRotationMatrixY(float angle)
{
	mat44 result;

	result.m[0][0] = cos(angle);
	result.m[0][2] = -sin(angle);
	result.m[2][0] = sin(angle);
	result.m[2][2] = cos(angle);

	return result;
}

const mat44 Math::createRotationMatrixZ(float angle)
{
	mat44 result;

	result.m[0][0] = cos(angle);
	result.m[1][0] = -sin(angle);
	result.m[0][1] = sin(angle);
	result.m[1][1] = cos(angle);

	return result;
}

const mat44 Math::createOrthographicProjectionMatrix(float leftX, float rightX, float bottomY, float topY, float nearZ, float farZ)
{
	mat44 result;

	result.m[0][0] = 2.0f / (rightX - leftX);
	result.m[1][1] = 2.0f / (topY - bottomY);
	result.m[2][2] = -2.0f / (farZ - nearZ);
	result.m[3][0] = -((rightX + leftX) / (rightX - leftX));
	result.m[3][1] = -((topY + bottomY) / (topY - bottomY));
	result.m[3][2] = -((farZ + nearZ) / (farZ - nearZ));

	return result;
};

const mat44 Math::createViewMatrix(const fvec3& eye, const fvec3& center, const fvec3& up)
{
	fvec3 frontVector = normalize(center - eye);
	fvec3 rightVector = normalize(calculateCrossProduct(frontVector, up));
	fvec3 upVector = calculateCrossProduct(rightVector, frontVector);

	mat44 result(1.0f);
	result.m[0][0] = rightVector.x;
	result.m[1][0] = rightVector.y;
	result.m[2][0] = rightVector.z;
	result.m[0][1] = upVector.x;
	result.m[1][1] = upVector.y;
	result.m[2][1] = upVector.z;
	result.m[0][2] = -(frontVector.x);
	result.m[1][2] = -(frontVector.y);
	result.m[2][2] = -(frontVector.z);
	result.m[3][0] = -(calculateDotProduct(rightVector, eye));
	result.m[3][1] = -(calculateDotProduct(upVector, eye));
	result.m[3][2] = calculateDotProduct(frontVector, eye);

	return result;
}

const mat44 Math::createPerspectiveProjectionMatrix(float fov, float aspect, float near, float far)
{
	const float tanHalfFovY = tan(fov * 0.5f);

	mat44 result(0.0f);
	result.m[0][0] = 1.0f / (aspect * tanHalfFovY);
	result.m[1][1] = 1.0f / tanHalfFovY;
	result.m[2][2] = -((far + near) / (far - near));
	result.m[2][3] = -1.0f;
	result.m[3][2] = -((2.0f * far * near) / (far - near));

	return result;
}