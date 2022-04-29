#include "quad3d_entity.hpp"

#include <algorithm>

using std::clamp;
using std::max;

Quad3d::Quad3d(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Quad3d::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Quad3d::updateTarget()
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

void Quad3d::updateTransformation()
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
		Mathematics::convertToRadians(_rotation.z), _rotationOrder);
	_transformation = (_transformation * rotationMatrix);

	if(!_isCentered)
	{
		auto rotationOriginMatrix = Mathematics::createTranslationMatrix(0.0f, -(_size.y * 0.5f), 0.0f);
		_transformation = (_transformation * rotationOriginMatrix);
	}

	auto scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y, 1.0f);
	_transformation = (_transformation * scalingMatrix);
}

void Quad3d::setFacingCameraHorizontally(bool value)
{
	_isFacingCameraHorizontally = value;
}

void Quad3d::setFacingCameraVertically(bool value)
{
	_isFacingCameraVertically = value;
}

void Quad3d::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void Quad3d::setEmissionMap(shared_ptr<TextureBuffer> value)
{
	_emissionTextureBuffer = value;
}

void Quad3d::setPosition(const fvec3 & value)
{
	_position = value;
	_positionTarget = value;
}

void Quad3d::setRotation(const fvec3 & value)
{
	_rotation = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(value.x), Mathematics::limitAngle(value.y), Mathematics::limitAngle(value.z));
}

void Quad3d::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3d::move(const fvec3 & change)
{
	_position += change;
	_positionTarget += change;
}

void Quad3d::rotate(const fvec3 & change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = fvec3(Mathematics::limitAngle(_rotation.x), Mathematics::limitAngle(_rotation.y), Mathematics::limitAngle(_rotation.z));
	_rotationTarget = fvec3(Mathematics::limitAngle(_rotationTarget.x), Mathematics::limitAngle(_rotationTarget.y), Mathematics::limitAngle(_rotationTarget.z));
}

void Quad3d::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Quad3d::moveTo(const fvec3 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Quad3d::rotateTo(const fvec3 & target, float speed)
{
	_rotationTarget = fvec3(Mathematics::limitAngle(target.x), Mathematics::limitAngle(target.y), Mathematics::limitAngle(target.z));
	_rotationTargetSpeed = speed;
}

void Quad3d::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Quad3d::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad3d::setUvMultiplier(const fvec2 & value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3d::setUvOffset(const fvec2 & value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad3d::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad3d::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void Quad3d::setEmissionMapPath(const string & value)
{
	_emissionMapPath = value;
}

void Quad3d::setReflected(bool value)
{
	_isReflected = value;
}

void Quad3d::setBright(bool value)
{
	_isBright = value;
}

void Quad3d::setWireframed(bool value)
{
	_isWireframed = value;
}

void Quad3d::setShadowed(bool value)
{
	_isShadowed = value;
}

void Quad3d::setCentered(bool value)
{
	_isCentered = value;
}

void Quad3d::setLightness(float value)
{
	_lightness = max(0.0f, value);
}

void Quad3d::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);
}

void Quad3d::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Quad3d::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Quad3d::setTextureRepeat(int value)
{
	_textureRepeat = max(1, value);
}

void Quad3d::setEmissionIntensity(float value)
{
	_emissionIntensity = value;
}

void Quad3d::setFrozen(bool value)
{
	_isFrozen = value;
}

void Quad3d::setMinTextureAlpha(float value)
{
	_minTextureAlpha = value;
}

void Quad3d::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;
}

void Quad3d::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;
}

void Quad3d::setRotationOrder(DirectionOrderType value)
{
	_rotationOrder = value;
}

const shared_ptr<VertexBuffer> Quad3d::getVertexBuffer() const
{
	return _vertexBuffer;
}

const mat44 & Quad3d::getTransformation() const
{
	return _transformation;
}

const shared_ptr<TextureBuffer> Quad3d::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const shared_ptr<TextureBuffer> Quad3d::getEmissionTextureBuffer() const
{
	return _emissionTextureBuffer;
}

const fvec3 & Quad3d::getPosition() const
{
	return _position;
}

const fvec3 & Quad3d::getRotation() const
{
	return _rotation;
}

const fvec2 & Quad3d::getSize() const
{
	return _size;
}

const fvec2 & Quad3d::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Quad3d::getUvOffset() const
{
	return _uvOffset;
}

const fvec3 & Quad3d::getColor() const
{
	return _color;
}

const fvec3 & Quad3d::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Quad3d::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Quad3d::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const string & Quad3d::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const string & Quad3d::getEmissionMapPath() const
{
	return _emissionMapPath;
}

const float Quad3d::getLightness() const
{
	return _lightness;
}

const float Quad3d::getOpacity() const
{
	return _opacity;
}

const int Quad3d::getTextureRepeat() const
{
	return _textureRepeat;
}

const float Quad3d::getEmissionIntensity() const
{
	return _emissionIntensity;
}

const float Quad3d::getMinTextureAlpha() const
{
	return _minTextureAlpha;
}

const bool Quad3d::isFacingCameraHorizontally() const
{
	return _isFacingCameraHorizontally;
}

const bool Quad3d::isFacingCameraVertically() const
{
	return _isFacingCameraVertically;
}

const bool Quad3d::isShadowed() const
{
	return _isShadowed;
}

const bool Quad3d::isReflected() const
{
	return _isReflected;
}

const bool Quad3d::isBright() const
{
	return _isBright;
}

const bool Quad3d::isWireframed() const
{
	return _isWireframed;
}

const bool Quad3d::isCentered() const
{
	return _isCentered;
}

const bool Quad3d::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Quad3d::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const DirectionOrderType Quad3d::getRotationOrder() const
{
	return _rotationOrder;
}

const bool Quad3d::isFrozen() const
{
	return _isFrozen;
}