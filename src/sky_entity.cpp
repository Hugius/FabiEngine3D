#include "sky_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SkyEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void SkyEntity::updateRotationMatrix()
{
	_rotationMatrix = Math::createRotationMatrixY(Math::convertToRadians(_rotation));
}

void SkyEntity::setDiffuseMapPaths(const array<string, 6>& value)
{
	_diffuseMapPaths = value;
}

void SkyEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void SkyEntity::setCubeMap(TextureID value)
{
	_diffuseMap = value;
}

void SkyEntity::setInitialLightness(float value)
{
	_initialLightness = max(0.0f, value);
}

void SkyEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void SkyEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
}

void SkyEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

const shared_ptr<RenderBuffer> SkyEntity::getRenderBuffer() const
{
	return _renderBuffer;
}

const array<string, 6>& SkyEntity::getDiffuseMapPaths() const
{
	return _diffuseMapPaths;
}

const Matrix44& SkyEntity::getRotationMatrix() const
{
	return _rotationMatrix;
}

const Vec3 SkyEntity::getColor() const
{
	return _color;
}

const TextureID SkyEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const float SkyEntity::getInitialLightness() const
{
	return _initialLightness;
}

const float SkyEntity::getLightness() const
{
	return _lightness;
}

const float SkyEntity::getRotation() const
{
	return _rotation;
}

const bool SkyEntity::hasCubeMap() const
{
	return (_diffuseMap != 0);
}

const bool SkyEntity::isWireframed() const
{
	return _isWireframed;
}

const bool SkyEntity::hasRenderBuffer() const
{
	return (_renderBuffer != nullptr);
}