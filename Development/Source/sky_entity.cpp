#include "sky_entity.hpp"

void SkyEntity::updateRotationMatrix()
{
	if (_rotationSpeed != 0.0f)
	{
		_rotation += _rotationSpeed;
		_rotationMatrix = Matrix44::createRotationY(Math::degreesToRadians(_rotation));
	}
}

void SkyEntity::setDiffuseMapPaths(const array<string, 6>& val)
{
	_diffuseMapPaths = val;
}

void SkyEntity::setColor(Vec3 val)
{
	_color = val;
}

void SkyEntity::setCubeMap(GLuint val)
{
	_cubeMap = val;
}

void SkyEntity::setOriginalLightness(float val)
{
	_originalLightness = val;
}

void SkyEntity::setLightness(float val)
{
	_lightness = val;
}

void SkyEntity::setRotationSpeed(float val)
{
	_rotationSpeed = val;
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