#include "quad3d_entity.hpp"

#include <algorithm>

using std::clamp;
using std::max;

void Quad3dEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Quad3dEntity::updateTarget()
{
	if(_position != _positionTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_positionTarget - _position);

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

	if(_size != _sizeTarget)
	{
		const auto speedMultiplier = Mathematics::normalize(_sizeTarget - _size);

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

void Quad3dEntity::updateTransformation()
{
	_transformation = mat44(1.0f);

	auto translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y, _position.z);
	_transformation = (_transformation * translationMatrix);

	if(!_isCentered)
	{
		auto rotationOriginMatrix = Mathematics::createTranslationMatrix(0.0f, (_size.y * 0.5f), 0.0f);
		_transformation = (_transformation * rotationOriginMatrix);
	}

	auto rotationMatrix = Mathematics::createRotationMatrix(
		Mathematics::convertToRadians(_rotation.x),
		Mathematics::convertToRadians(_rotation.y),
		Mathematics::convertToRadians(_rotation.z), DirectionOrderType::YXZ);
	_transformation = (_transformation * rotationMatrix);

	if(!_isCentered)
	{
		auto rotationOriginMatrix = Mathematics::createTranslationMatrix(0.0f, -(_size.y * 0.5f), 0.0f);
		_transformation = (_transformation * rotationOriginMatrix);
	}

	auto scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y, 1.0f);
	_transformation = (_transformation * scalingMatrix);
}

void Quad3dEntity::setFacingCameraHorizontally(bool value)
{
	_isFacingCameraHorizontally = value;
}

void Quad3dEntity::setFacingCameraVertically(bool value)
{
	_isFacingCameraVertically = value;
}

void Quad3dEntity::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void Quad3dEntity::setEmissionMap(shared_ptr<TextureBuffer> value)
{
	_emissionTextureBuffer = value;
}

void Quad3dEntity::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Quad3dEntity::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Quad3dEntity::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3dEntity::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Quad3dEntity::rotate(const fvec3 & change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void Quad3dEntity::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Quad3dEntity::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Quad3dEntity::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Quad3dEntity::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Quad3dEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad3dEntity::setUvMultiplier(const fvec2 & value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3dEntity::setUvOffset(const fvec2 & value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3dEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad3dEntity::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void Quad3dEntity::setEmissionMapPath(const string & value)
{
	_emissionMapPath = value;
}

void Quad3dEntity::setReflected(bool value)
{
	_isReflected = value;
}

void Quad3dEntity::setBright(bool value)
{
	_isBright = value;
}

void Quad3dEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void Quad3dEntity::setShadowed(bool value)
{
	_isShadowed = value;
}

void Quad3dEntity::setCentered(bool value)
{
	_isCentered = value;
}

void Quad3dEntity::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void Quad3dEntity::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);
}

void Quad3dEntity::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Quad3dEntity::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Quad3dEntity::setTextureRepeat(unsigned int value)
{
	_textureRepeat = max(unsigned int(1), value);
}

void Quad3dEntity::setEmissionIntensity(float value)
{
	_emissionIntensity = value;
}

void Quad3dEntity::setFrozen(bool value)
{
	_isFrozen = value;
}

void Quad3dEntity::setMinTextureAlpha(float value)
{
	_minTextureAlpha = value;
}

void Quad3dEntity::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;
}

void Quad3dEntity::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;
}

const shared_ptr<VertexBuffer> Quad3dEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const mat44 & Quad3dEntity::getTransformation() const
{
	return _transformation;
}

const shared_ptr<TextureBuffer> Quad3dEntity::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Quad3dEntity::getEmissionTextureBuffer() const
{
	return _emissionTextureBuffer;
}

const fvec3 & Quad3dEntity::getPosition() const
{
	return _position;
}

const fvec3 & Quad3dEntity::getRotation() const
{
	return _rotation;
}

const fvec2 & Quad3dEntity::getSize() const
{
	return _size;
}

const fvec2 & Quad3dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Quad3dEntity::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 & Quad3dEntity::getColor() const
{
	return _color;
}

const fvec3 & Quad3dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Quad3dEntity::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Quad3dEntity::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const string & Quad3dEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string & Quad3dEntity::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const float Quad3dEntity::getLightness() const
{
	return _lightness;
}

const float Quad3dEntity::getOpacity() const
{
	return _opacity;
}

const unsigned int Quad3dEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const float Quad3dEntity::getEmissionIntensity() const
{
	return _emissionIntensity;
}

const float Quad3dEntity::getMinTextureAlpha() const
{
	return _minTextureAlpha;
}

const bool Quad3dEntity::isFacingCameraHorizontally() const
{
	return _isFacingCameraHorizontally;
}

const bool Quad3dEntity::isFacingCameraVertically() const
{
	return _isFacingCameraVertically;
}

const bool Quad3dEntity::isShadowed() const
{
	return _isShadowed;
}

const bool Quad3dEntity::isReflected() const
{
	return _isReflected;
}

const bool Quad3dEntity::isBright() const
{
	return _isBright;
}

const bool Quad3dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Quad3dEntity::isCentered() const
{
	return _isCentered;
}

const bool Quad3dEntity::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Quad3dEntity::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const bool Quad3dEntity::isFrozen() const
{
	return _isFrozen;
}