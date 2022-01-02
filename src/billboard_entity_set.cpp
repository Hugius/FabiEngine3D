#include "billboard_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void BillboardEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void BillboardEntity::updateTransformation()
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

void BillboardEntity::updateTransformationMatrix()
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

void BillboardEntity::setFacingCameraX(bool value)
{
	_isFacingCameraX = value;
}

void BillboardEntity::setFacingCameraY(bool value)
{
	_isFacingCameraY = value;
}

void BillboardEntity::setDiffuseMap(shared_ptr<TextureBuffer> value, bool isTextual)
{
	_diffuseMap = value;
	_isTextual = isTextual;
}

void BillboardEntity::setEmissionMap(shared_ptr<TextureBuffer> value)
{
	_emissionMap = value;
}

void BillboardEntity::setPosition(fvec3 value)
{
	_position = value;
	_positionTarget = value;
}

void BillboardEntity::setRotation(fvec3 value)
{
	_rotation = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
	_rotationTarget = fvec3(Math::limitAngle(value.x), Math::limitAngle(value.y), Math::limitAngle(value.z));
}

void BillboardEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void BillboardEntity::move(fvec3 value)
{
	_position += value;
	_positionTarget += value;
}

void BillboardEntity::rotate(fvec3 value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = fvec3(Math::limitAngle(_rotation.x), Math::limitAngle(_rotation.y), Math::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Math::limitAngle(_rotationTarget.x), Math::limitAngle(_rotationTarget.y), Math::limitAngle(_rotationTarget.z));
}

void BillboardEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void BillboardEntity::moveTo(fvec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void BillboardEntity::rotateTo(fvec3 target, float speed)
{
	_rotationTarget = fvec3(Math::limitAngle(target.x), Math::limitAngle(target.y), Math::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void BillboardEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void BillboardEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void BillboardEntity::setUvMultiplier(fvec2 value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void BillboardEntity::setUvOffset(fvec2 value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void BillboardEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void BillboardEntity::setTextContent(const string& value)
{
	_textContent = value;
}

void BillboardEntity::setFontPath(const string& value)
{
	_fontPath = value;
}

void BillboardEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void BillboardEntity::setEmissionMapPath(const string& value)
{
	_emissionMapPath = value;
}

void BillboardEntity::setDepthMapIncluded(bool value)
{
	_isDepthMapIncluded = value;
}

void BillboardEntity::setReflected(bool value)
{
	_isReflected = value;
}

void BillboardEntity::setBright(bool value)
{
	_isBright = value;
}

void BillboardEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void BillboardEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void BillboardEntity::setCentered(bool value)
{
	_isCentered = value;
}

void BillboardEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void BillboardEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void BillboardEntity::setMinHeight(float value)
{
	_minHeight = value;
}

void BillboardEntity::setMaxHeight(float value)
{
	_maxHeight = value;
}

void BillboardEntity::setTextureRepeat(float value)
{
	_textureRepeat = max(0.0f, value);
}

void BillboardEntity::setEmissionIntensity(float value)
{
	_emissionIntensity = value;
}

void BillboardEntity::setFrozen(bool value)
{
	_isFrozen = value;
}