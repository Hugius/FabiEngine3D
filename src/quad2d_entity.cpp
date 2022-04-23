#include "quad2d_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void Quad2dEntity::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Quad2dEntity::updateTarget()
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
	}

	if(_rotation != _rotationTarget)
	{
		auto difference = fabsf(_rotation - _rotationTarget);
		float multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		float speed = (_rotationTargetSpeed * multiplier);
		_rotation += ((_rotation < _rotationTarget) ? speed : (_rotation > _rotationTarget) ? -speed : 0.0f);

		_rotation = Mathematics::limitAngle(_rotation);
		if(Mathematics::calculateAngleDifference(_rotation, _rotationTarget) <= _rotationTargetSpeed)
		{
			_rotation = _rotationTarget;
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

void Quad2dEntity::updateTransformation()
{
	auto translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y, 0.0f);
	auto rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(_rotation));
	auto scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y, 1.0f);

	_transformation = (translationMatrix * rotationMatrix * scalingMatrix);
}

void Quad2dEntity::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void Quad2dEntity::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void Quad2dEntity::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad2dEntity::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;
}

void Quad2dEntity::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;
}

void Quad2dEntity::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);
}

void Quad2dEntity::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad2dEntity::setPosition(const fvec2 & value)
{
	_position = value;
	_positionTarget = value;
}

void Quad2dEntity::setRotation(float value)
{
	_rotation = Mathematics::limitAngle(value);
	_rotationTarget = Mathematics::limitAngle(value);
}

void Quad2dEntity::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad2dEntity::move(const fvec2 & value)
{
	_position += value;
	_positionTarget += value;
}

void Quad2dEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Mathematics::limitAngle(_rotation);
	_rotationTarget = Mathematics::limitAngle(_rotationTarget);
}

void Quad2dEntity::scale(const fvec2 & value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Quad2dEntity::moveTo(const fvec2 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Quad2dEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Mathematics::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void Quad2dEntity::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Quad2dEntity::setMinClippingPosition(const fvec2 & value)
{
	_minClippingPosition = value;
}

void Quad2dEntity::setMaxClippingPosition(const fvec2 & value)
{
	_maxClippingPosition = value;
}

void Quad2dEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void Quad2dEntity::setUvMultiplier(const fvec2 & value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad2dEntity::setUvOffset(const fvec2 & value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

const shared_ptr<VertexBuffer> Quad2dEntity::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Quad2dEntity::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const string & Quad2dEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const fvec3 & Quad2dEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Quad2dEntity::getColor() const
{
	return _color;
}

const float Quad2dEntity::getOpacity() const
{
	return _opacity;
}

const bool Quad2dEntity::isWireframed() const
{
	return _isWireframed;
}

const bool Quad2dEntity::isCentered() const
{
	return _isCentered;
}

const bool Quad2dEntity::isFlippedHorizonally() const
{
	return _isHorizontallyFlipped;
}

const bool Quad2dEntity::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const mat44 & Quad2dEntity::getTransformation() const
{
	return _transformation;
}

const fvec2 & Quad2dEntity::getPosition() const
{
	return _position;
}

const float Quad2dEntity::getRotation() const
{
	return _rotation;
}

const unsigned int Quad2dEntity::getTextureRepeat() const
{
	return _textureRepeat;
}

const fvec2 & Quad2dEntity::getSize() const
{
	return _size;
}

const fvec2 & Quad2dEntity::getMinClippingPosition() const
{
	return _minClippingPosition;
}

const fvec2 & Quad2dEntity::getMaxClippingPosition() const
{
	return _maxClippingPosition;
}

const fvec2 & Quad2dEntity::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Quad2dEntity::getUvOffset() const
{
	return _uvOffset;
}

const unsigned int Quad2dEntity::getDepth() const
{
	return _depth;
}

void Quad2dEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

void Quad2dEntity::setCentered(bool value)
{
	_isCentered = value;
}

void Quad2dEntity::setTextureRepeat(unsigned int value)
{
	_textureRepeat = max(unsigned int(1), value);
}