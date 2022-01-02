#include "quad_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void QuadEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void QuadEntity::updateTransformation()
{
	if(_position != _positionTarget)
	{
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		if(fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if(fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = fabsf(_rotation - _rotationTarget);
		float multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		float speed = (_rotationTargetSpeed * multiplier);
		_rotation += ((_rotation < _rotationTarget) ? speed : (_rotation > _rotationTarget) ? -speed : 0.0f);

		_rotation = Math::limitAngle(_rotation);
		if(Math::calculateAngleDifference(_rotation, _rotationTarget) <= _rotationTargetSpeed)
		{
			_rotation = _rotationTarget;
		}
	}

	if(_size != _sizeTarget)
	{
		auto speedMultiplier = Math::normalize(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
		if(fabsf(_sizeTarget.x - _size.x) <= _sizeTargetSpeed)
		{
			_size.x = _positionTarget.x;
		}
		if(fabsf(_sizeTarget.y - _size.y) <= _sizeTargetSpeed)
		{
			_size.y = _positionTarget.y;
		}
	}
}

void QuadEntity::updateTransformationMatrix()
{
	auto translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, 0.0f);
	auto rotationMatrix = Math::createRotationMatrixX(Math::convertToRadians(_rotation));
	auto scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, 1.0f);

	_transformationMatrix = (translationMatrix * rotationMatrix * scalingMatrix);
}

void QuadEntity::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseMap = value;
}

void QuadEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void QuadEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void QuadEntity::setMirroredHorizontally(bool value)
{
	_isMirroredHorizontally = value;
}

void QuadEntity::setMirroredVertically(bool value)
{
	_isMirroredVertically = value;
}

void QuadEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void QuadEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void QuadEntity::setPosition(fvec2 value)
{
	_position = value;
	_positionTarget = value;
}

void QuadEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
	_rotationTarget = Math::limitAngle(value);
}

void QuadEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void QuadEntity::move(fvec2 value)
{
	_position += value;
	_positionTarget += value;
}

void QuadEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Math::limitAngle(_rotation);
	_rotationTarget = Math::limitAngle(_rotationTarget);
}

void QuadEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void QuadEntity::moveTo(fvec2 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void QuadEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Math::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void QuadEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void QuadEntity::setMinPosition(fvec2 value)
{
	_minPosition = value;
}

void QuadEntity::setMaxPosition(fvec2 value)
{
	_maxPosition = value;
}

void QuadEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void QuadEntity::setUvMultiplier(fvec2 value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void QuadEntity::setUvOffset(fvec2 value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

const shared_ptr<VertexBuffer> QuadEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> QuadEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const string& QuadEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const fvec3 QuadEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 QuadEntity::getColor() const
{
	return _color;
}

const float QuadEntity::getTransparency() const
{
	return _transparency;
}

const bool QuadEntity::isWireframed() const
{
	return _isWireframed;
}

const bool QuadEntity::isCentered() const
{
	return _isCentered;
}

const bool QuadEntity::isMirroredHorizonally() const
{
	return _isMirroredHorizontally;
}

const bool QuadEntity::isMirroredVertically() const
{
	return _isMirroredVertically;
}

const bool QuadEntity::hasDiffuseMap() const
{
	return (_diffuseMap != 0);
}

const mat44 QuadEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const fvec2 QuadEntity::getPosition() const
{
	return _position;
}

const float QuadEntity::getRotation() const
{
	return _rotation;
}

const fvec2 QuadEntity::getSize() const
{
	return _size;
}

const fvec2 QuadEntity::getMinPosition() const
{
	return _minPosition;
}

const fvec2 QuadEntity::getMaxPosition() const
{
	return _maxPosition;
}

const fvec2 QuadEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 QuadEntity::getUvOffset() const
{
	return _uvOffset;
}

const unsigned int QuadEntity::getDepth() const
{
	return _depth;
}

void QuadEntity::setPerspectiveDepthEntity(bool value)
{
	_isPerspectiveDepthEntity = value;
}

void QuadEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void QuadEntity::setCentered(bool value)
{
	_isCentered = value;
}

const bool QuadEntity::isPerspectiveDepthEntity() const
{
	return _isPerspectiveDepthEntity;
}