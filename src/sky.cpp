#include "sky.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Sky::Sky(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Sky::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Sky::updateTarget()
{
	if(_rotation != _rotationTarget)
	{
		const auto difference = Mathematics::calculateDifference(_rotation, _rotationTarget);
		const auto multiplier = fvec3(((difference.x < 180.0f) ? 1.0f : -1.0f), ((difference.y < 180.0f) ? 1.0f : -1.0f), ((difference.z < 180.0f) ? 1.0f : -1.0f));
		const auto speed = (fvec3(_rotationTargetSpeed) * multiplier);

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

void Sky::updateTransformation()
{
	_transformation = Mathematics::createRotationMatrix(
		Mathematics::convertToRadians(_rotation.x),
		Mathematics::convertToRadians(_rotation.y),
		Mathematics::convertToRadians(_rotation.z), _rotationOrder);
}

void Sky::setCubeMapPaths(const array<string, 6> & value)
{
	_cubeMapPaths = value;
}

void Sky::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Sky::setCubeMap(shared_ptr<TextureBuffer> value)
{
	_cubeTextureBuffer = value;
}

void Sky::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void Sky::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Sky::rotate(const fvec3 & change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void Sky::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Sky::setWireframed(bool value)
{
	_isWireframed = value;
}

void Sky::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Sky::setRotationOrder(DirectionOrderType value)
{
	_rotationOrder = value;
}

const shared_ptr<VertexBuffer> Sky::getVertexBuffer() const
{
	return _vertexBuffer;
}

const array<string, 6> & Sky::getCubeMapPaths() const
{
	return _cubeMapPaths;
}

const fmat44 & Sky::getTransformation() const
{
	return _transformation;
}

const fvec3 & Sky::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Sky::getColor() const
{
	return _color;
}

const shared_ptr<TextureBuffer> Sky::getCubeTextureBuffer() const
{
	return _cubeTextureBuffer;
}

const string & Sky::getId() const
{
	return _id;
}

const float Sky::getLightness() const
{
	return _lightness;
}

const fvec3 & Sky::getRotation() const
{
	return _rotation;
}

const bool Sky::isWireframed() const
{
	return _isWireframed;
}

const DirectionOrderType Sky::getRotationOrder() const
{
	return _rotationOrder;
}