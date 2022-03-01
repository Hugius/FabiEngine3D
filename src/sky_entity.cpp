#include "sky_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SkyEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void SkyEntity::updateTransformation()
{
	_transformation = Math::createRotationMatrixY(Math::convertToRadians(_rotation));
}

void SkyEntity::setCubeMapPaths(const array<string, 6>& value)
{
	_cubeMapPaths = value;
}

void SkyEntity::setColor(const fvec3& value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void SkyEntity::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeTextureBuffer = value;
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

void SkyEntity::setWireframeColor(const fvec3& value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

const shared_ptr<VertexBuffer> SkyEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const array<string, 6>& SkyEntity::getCubeMapPaths() const
{
	return _cubeMapPaths;
}

const mat44& SkyEntity::getTransformation() const
{
	return _transformation;
}

const fvec3& SkyEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3& SkyEntity::getColor() const
{
	return _color;
}

const shared_ptr<TextureBuffer> SkyEntity::getCubeTextureBuffer() const
{
	return _cubeTextureBuffer;
}

const float SkyEntity::getLightness() const
{
	return _lightness;
}

const float SkyEntity::getRotation() const
{
	return _rotation;
}

const bool SkyEntity::isWireframed() const
{
	return _isWireframed;
}