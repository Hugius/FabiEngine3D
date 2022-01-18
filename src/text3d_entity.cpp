#include "text3d_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Text3dEntity::setMesh(shared_ptr<VertexBuffer> value)
{
	_mesh = value;
}

void Text3dEntity::setContent(const string& value)
{
}

void Text3dEntity::setFontMapPath(const string& value)
{
}

void Text3dEntity::setFontMap(shared_ptr<TextureBuffer> value)
{
}

void Text3dEntity::updateTransformation()
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
		if(fabsf(_positionTarget.z - _position.z) <= _positionTargetSpeed)
		{
			_position.z = _positionTarget.z;
		}
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = Math::calculateDifference(_rotation, _rotationTarget);
		fvec3 multiplier = fvec3(
			((difference.x < 180.0f) ? 1.0f : -1.0f),
			((difference.y < 180.0f) ? 1.0f : -1.0f),
			((difference.z < 180.0f) ? 1.0f : -1.0f));
		fvec3 speed = (fvec3(_rotationTargetSpeed) * multiplier);
		_rotation.x += ((_rotation.x < _rotationTarget.x) ? speed.x : (_rotation.x > _rotationTarget.x) ? -speed.x : 0.0f);
		_rotation.y += ((_rotation.y < _rotationTarget.y) ? speed.y : (_rotation.y > _rotationTarget.y) ? -speed.y : 0.0f);
		_rotation.z += ((_rotation.z < _rotationTarget.z) ? speed.z : (_rotation.z > _rotationTarget.z) ? -speed.z : 0.0f);

		_rotation = fvec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
		if(Math::calculateAngleDifference(_rotation.x, _rotationTarget.x) <= _rotationTargetSpeed)
		{
			_rotation.x = _rotationTarget.x;
		}
		if(Math::calculateAngleDifference(_rotation.y, _rotationTarget.y) <= _rotationTargetSpeed)
		{
			_rotation.y = _rotationTarget.y;
		}
		if(Math::calculateAngleDifference(_rotation.z, _rotationTarget.z) <= _rotationTargetSpeed)
		{
			_rotation.z = _rotationTarget.z;
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

void Text3dEntity::updateTransformationMatrix()
{
	_transformationMatrix = mat44(1.0f);

	auto translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, _position.z);
	_transformationMatrix = (_transformationMatrix * translationMatrix);

	if(!_isCentered)
	{
		auto rotationOriginMatrix = Math::createTranslationMatrix(0.0f, (_size.y / 2.0f), 0.0f);
		_transformationMatrix = (_transformationMatrix * rotationOriginMatrix);
	}

	auto rotationMatrix = Math::createRotationMatrix(
		Math::convertToRadians(_rotation.x),
		Math::convertToRadians(_rotation.y),
		Math::convertToRadians(_rotation.z), DirectionOrder::YXZ);
	_transformationMatrix = (_transformationMatrix * rotationMatrix);

	if(!_isCentered)
	{
		auto rotationOriginMatrix = Math::createTranslationMatrix(0.0f, -(_size.y / 2.0f), 0.0f);
		_transformationMatrix = (_transformationMatrix * rotationOriginMatrix);
	}

	auto scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, 1.0f);
	_transformationMatrix = (_transformationMatrix * scalingMatrix);
}

void Text3dEntity::setFacingCameraX(bool value)
{
	_isFacingCameraX = value;
}

void Text3dEntity::setFacingCameraY(bool value)
{
	_isFacingCameraY = value;
}

void Text3dEntity::setPosition(fvec3 value)
{
	_position = value;
	_positionTarget = value;
}

void Text3dEntity::setRotation(fvec3 value)
{
	_rotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_rotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void Text3dEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Text3dEntity::move(fvec3 value)
{
	_position += value;
	_positionTarget += value;
}

void Text3dEntity::rotate(fvec3 value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = fvec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Math::limitAngle(_rotationTarget.x), Math::limitAngle(_rotationTarget.y), Math::limitAngle(_rotationTarget.z));
}

void Text3dEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Text3dEntity::moveTo(fvec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Text3dEntity::rotateTo(fvec3 target, float speed)
{
	_rotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Text3dEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Text3dEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Text3dEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Text3dEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void Text3dEntity::setReflected(bool value)
{
	_isReflected = value;
}

void Text3dEntity::setBright(bool value)
{
	_isBright = value;
}

void Text3dEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void Text3dEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void Text3dEntity::setCentered(bool value)
{
	_isCentered = value;
}

void Text3dEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void Text3dEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void Text3dEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void Text3dEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void Text3dEntity::setFrozen(bool value)
{
	_isFrozen = value;
}

const shared_ptr<VertexBuffer> Text3dEntity::getMesh() const
{
	return _mesh;
}

const mat44& Text3dEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const fvec3 Text3dEntity::getPosition() const
{
	return _position;
}

const fvec3 Text3dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 Text3dEntity::getSize() const
{
	return _size;
}

const fvec2 Text3dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 Text3dEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 Text3dEntity::getColor() const
{
	return _color;
}

const fvec3 Text3dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const float Text3dEntity::getLightness() const
{
	return _lightness;
}

const float Text3dEntity::getTransparency() const
{
	return _transparency;
}

const float Text3dEntity::getMinHeight() const
{
	return _minHeight;
}

const float Text3dEntity::getMaxHeight() const
{
	return _maxHeight;
}

const bool Text3dEntity::isFacingCameraX() const
{
	return _isFacingCameraX;
}

const bool Text3dEntity::isFacingCameraY() const
{
	return _isFacingCameraY;
}

const bool Text3dEntity::isDepthMapIncluded() const
{
	return _isDepthMapIncluded;
}

const bool Text3dEntity::isShadowed() const
{
	return _isShadowed;
}

const bool Text3dEntity::isReflected() const
{
	return _isReflected;
}

const bool Text3dEntity::isBright() const
{
	return _isBright;
}

const bool Text3dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Text3dEntity::isCentered() const
{
	return _isCentered;
}

const bool Text3dEntity::isFrozen() const
{
	return _isFrozen;
}