#include "sky_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void SkyEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void SkyEntity::updateTarget()
{
	if(_rotation != _rotationTarget)
	{
		auto difference = Mathematics::calculateDifference(_rotation, _rotationTarget);
		auto multiplier = fvec3(((difference.x < 180.0f) ? 1.0f : -1.0f), ((difference.y < 180.0f) ? 1.0f : -1.0f), ((difference.z < 180.0f) ? 1.0f : -1.0f));
		auto speed = (fvec3(_rotationTargetSpeed) * multiplier);

		_rotation.x += ((_rotation.x < _rotationTarget.x) ? speed.x : (_rotation.x > _rotationTarget.x) ? -speed.x : 0.0f);
		_rotation.y += ((_rotation.y < _rotationTarget.y) ? speed.y : (_rotation.y > _rotationTarget.y) ? -speed.y : 0.0f);
		_rotation.z += ((_rotation.z < _rotationTarget.z) ? speed.z : (_rotation.z > _rotationTarget.z) ? -speed.z : 0.0f);

		_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));

		if(Mathematics::calculateAngleDifference(_rotation.x, _rotationTarget.x) <= _rotationTargetSpeed)
		{
			_rotation.x = _rotationTarget.x;
		}
		if(Mathematics::calculateAngleDifference(_rotation.y, _rotationTarget.y) <= _rotationTargetSpeed)
		{
			_rotation.y = _rotationTarget.y;
		}
		if(Mathematics::calculateAngleDifference(_rotation.z, _rotationTarget.z) <= _rotationTargetSpeed)
		{
			_rotation.z = _rotationTarget.z;
		}
	}
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

void SkyEntity::rotate(const fvec3 & value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void SkyEntity::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
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