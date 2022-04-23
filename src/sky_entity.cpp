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
	_transformation = Mathematics::createRotationMatrix(
		Mathematics::convertToRadians(_rotation.x),
		Mathematics::convertToRadians(_rotation.y),
		Mathematics::convertToRadians(_rotation.z), DirectionOrderType::YXZ);
}

void SkyEntity::setCubeMapPaths(const array<string, 6> & value)
{
	_cubeMapPaths = value;
}

void SkyEntity::setColor(const fvec3 & value)
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

void SkyEntity::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void SkyEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void SkyEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

const shared_ptr<VertexBuffer> SkyEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const array<string, 6> & SkyEntity::getCubeMapPaths() const
{
	return _cubeMapPaths;
}

const mat44 & SkyEntity::getTransformation() const
{
	return _transformation;
}

const fvec3 & SkyEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & SkyEntity::getColor() const
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

const fvec3 & SkyEntity::getRotation() const
{
	return _rotation;
}

const bool SkyEntity::isWireframed() const
{
	return _isWireframed;
}