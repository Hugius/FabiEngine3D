#include "sky_entity.hpp"

void SkyEntity::updateRotationMatrix()
{
	if (_rotationSpeed != 0.0f)
	{
		_rotation += _rotationSpeed;
		_rotationMatrix = Matrix44::createRotationY(Math::degreesToRadians(_rotation));
	}
}

void SkyEntity::setDiffuseMapPaths(const array<string, 6>& value)
{
	_diffuseMapPaths = value;
}

void SkyEntity::setColor(Vec3 value)
{
	_color = value;
}

void SkyEntity::setCubeMap(GLuint value)
{
	_cubeMap = value;
}

void SkyEntity::setOriginalLightness(float value)
{
	_originalLightness = value;
}

void SkyEntity::setLightness(float value)
{
	_lightness = value;
}

void SkyEntity::setRotationSpeed(float value)
{
	_rotationSpeed = value;
}

const array<string, 6>& SkyEntity::getDiffuseMapPaths() const
{
	return _diffuseMapPaths;
}

const Matrix44 & SkyEntity::getRotationMatrix() const
{
	return _rotationMatrix;
}

const Vec3 SkyEntity::getColor() const
{
	return _color;
}

const GLuint SkyEntity::getCubeMap() const
{
	return _cubeMap;
}

const float SkyEntity::getOriginalLightness() const
{
	return _originalLightness;
}

const float SkyEntity::getLightness() const
{
	return _lightness;
}

const float SkyEntity::getRotationSpeed() const
{
	return _rotationSpeed;
}