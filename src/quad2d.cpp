#include "quad2d.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Quad2d::Quad2d(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Quad2d::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Quad2d::updateTarget()
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
		const auto difference = fabsf(_rotation - _rotationTarget);
		const auto  multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		const auto  speed = (_rotationTargetSpeed * multiplier);

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

void Quad2d::updateTransformation()
{
	const auto  translationMatrix = Mathematics::createTranslationMatrix(_position.x, _position.y, 0.0f);
	const auto  rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(_rotation));
	const auto  scalingMatrix = Mathematics::createScalingMatrix(_size.x, _size.y, 1.0f);

	_transformation = (translationMatrix * rotationMatrix * scalingMatrix);
}

void Quad2d::setDiffuseMap(shared_ptr<TextureBuffer> value)
{
	_diffuseTextureBuffer = value;
}

void Quad2d::setDiffuseMapPath(const string & value)
{
	_diffuseMapPath = value;
}

void Quad2d::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad2d::setHorizontallyFlipped(bool value)
{
	_isHorizontallyFlipped = value;
}

void Quad2d::setVerticallyFlipped(bool value)
{
	_isVerticallyFlipped = value;
}

void Quad2d::setOpacity(float value)
{
	_opacity = clamp(value, 0.0f, 1.0f);
}

void Quad2d::setWireframeColor(const fvec3 & value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void Quad2d::setPosition(const fvec2 & value)
{
	_position = value;
	_positionTarget = value;
}

void Quad2d::setRotation(float value)
{
	_rotation = Mathematics::limitAngle(value);
	_rotationTarget = Mathematics::limitAngle(value);
}

void Quad2d::setSize(const fvec2 & value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad2d::move(const fvec2 & change)
{
	_position += change;
	_positionTarget += change;
}

void Quad2d::rotate(float change)
{
	_rotation += change;
	_rotationTarget += change;
	_rotation = Mathematics::limitAngle(_rotation);
	_rotationTarget = Mathematics::limitAngle(_rotationTarget);
}

void Quad2d::scale(const fvec2 & change)
{
	_size += change;
	_sizeTarget += change;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void Quad2d::moveTo(const fvec2 & target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void Quad2d::rotateTo(float target, float speed)
{
	_rotationTarget = Mathematics::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void Quad2d::scaleTo(const fvec2 & target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void Quad2d::setMinClipPosition(const fvec2 & value)
{
	_minClipPosition = fvec2(clamp(value.x, -1.0f, 1.0f), clamp(value.y, -1.0f, 1.0f));
}

void Quad2d::setMaxClipPosition(const fvec2 & value)
{
	_maxClipPosition = fvec2(clamp(value.x, -1.0f, 1.0f), clamp(value.y, -1.0f, 1.0f));
}

void Quad2d::setDepth(int value)
{
	_depth = max(0, value);
}

void Quad2d::setUvMultiplier(const fvec2 & value)
{
	_uvMultiplier = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void Quad2d::setUvOffset(const fvec2 & value)
{
	_uvOffset = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

const shared_ptr<VertexBuffer> Quad2d::getVertexBuffer() const
{
	return _vertexBuffer;
}

const shared_ptr<TextureBuffer> Quad2d::getDiffuseTextureBuffer() const
{
	return _diffuseTextureBuffer;
}

const string & Quad2d::getId() const
{
	return _id;
}

const string & Quad2d::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const fvec3 & Quad2d::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 & Quad2d::getColor() const
{
	return _color;
}

const float Quad2d::getOpacity() const
{
	return _opacity;
}

const bool Quad2d::isVisible() const
{
	return _isVisible;
}

const bool Quad2d::isWireframed() const
{
	return _isWireframed;
}

const bool Quad2d::isCentered() const
{
	return _isCentered;
}

const bool Quad2d::isHorizontallyFlipped() const
{
	return _isHorizontallyFlipped;
}

const bool Quad2d::isVerticallyFlipped() const
{
	return _isVerticallyFlipped;
}

const mat44 & Quad2d::getTransformation() const
{
	return _transformation;
}

const fvec2 & Quad2d::getPosition() const
{
	return _position;
}

const float Quad2d::getRotation() const
{
	return _rotation;
}

const int Quad2d::getTextureRepeat() const
{
	return _textureRepeat;
}

const fvec2 & Quad2d::getSize() const
{
	return _size;
}

const fvec2 & Quad2d::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec2 & Quad2d::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const fvec2 & Quad2d::getUvMultiplier() const
{
	return _uvMultiplier;
}

const fvec2 & Quad2d::getUvOffset() const
{
	return _uvOffset;
}

const int Quad2d::getDepth() const
{
	return _depth;
}

void Quad2d::setWireframed(bool value)
{
	_isWireframed = value;
}

void Quad2d::setCentered(bool value)
{
	_isCentered = value;
}

void Quad2d::setTextureRepeat(int value)
{
	_textureRepeat = max(1, value);
}

void Quad2d::setVisible(bool value)
{
	_isVisible = value;
}