#include "sky_entity.hpp"

#include <algorithm>

void SkyEntity::updateRotation()
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
	_color = Vec3(std::clamp(value.r, 0.0f, 1.0f), std::clamp(value.g, 0.0f, 1.0f), std::clamp(value.b, 0.0f, 1.0f));
}

void SkyEntity::setCubeMap(TextureID value)
{
	_cubeMap = value;
}

void SkyEntity::setOriginalLightness(float value)
{
	_originalLightness = std::max(0.0f, value);
}

void SkyEntity::setLightness(float value)
{
	_lightness = std::max(0.0f, value);
}

void SkyEntity::setRotationSpeed(float value)
{
	_rotationSpeed = value;
}

void SkyEntity::setWireFramed(bool value)
{
	_isWireFramed = value;
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

const TextureID SkyEntity::getCubeMap() const
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

const bool SkyEntity::hasCubeMap() const
{
	return (_cubeMap != 0);
}

const bool SkyEntity::isWireFramed() const
{
	return _isWireFramed;
}