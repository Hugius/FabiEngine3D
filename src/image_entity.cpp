#include "image_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

ImageEntity::ImageEntity(const string& ID, bool isCentered, shared_ptr<RenderBuffer> renderBuffer)
	:
	BaseEntity(ID),
	_isCentered(isCentered),
	_renderBuffer(renderBuffer)
{

}

void ImageEntity::updateTransformation()
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

void ImageEntity::updateTransformationMatrix()
{
	mat44 translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, 0.0f);
	mat44 rotationMatrix = Math::createRotationMatrixX(Math::convertToRadians(_rotation));
	mat44 scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, 1.0f);

	_transformationMatrix = (translationMatrix * rotationMatrix * scalingMatrix);
}

void ImageEntity::setDiffuseMap(TextureID value)
{
	_diffuseMap = value;
}

void ImageEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void ImageEntity::setColor(fvec3 value)
{
	_color = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void ImageEntity::setMirroredHorizontally(bool value)
{
	_isMirroredHorizontally = value;
}

void ImageEntity::setMirroredVertically(bool value)
{
	_isMirroredVertically = value;
}

void ImageEntity::setTransparency(float value)
{
	_transparency = clamp(value, 0.0f, 1.0f);
}

void ImageEntity::setWireframeColor(fvec3 value)
{
	_wireframeColor = fvec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void ImageEntity::setPosition(fvec2 value)
{
	_position = value;
	_positionTarget = value;
}

void ImageEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
	_rotationTarget = Math::limitAngle(value);
}

void ImageEntity::setSize(fvec2 value)
{
	_size = fvec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void ImageEntity::move(fvec2 value)
{
	_position += value;
	_positionTarget += value;
}

void ImageEntity::rotate(float value)
{
	_rotation += value;
	_rotationTarget += value;
	_rotation = Math::limitAngle(_rotation);
	_rotationTarget = Math::limitAngle(_rotationTarget);
}

void ImageEntity::scale(fvec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = fvec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void ImageEntity::moveTo(fvec2 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void ImageEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Math::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void ImageEntity::scaleTo(fvec2 target, float speed)
{
	_sizeTarget = fvec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void ImageEntity::setMinPosition(fvec2 value)
{
	_minPosition = value;
}

void ImageEntity::setMaxPosition(fvec2 value)
{
	_maxPosition = value;
}

void ImageEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void ImageEntity::setMultiplierUV(fvec2 value)
{
	_multiplierUV = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

void ImageEntity::setAdderUV(fvec2 value)
{
	_adderUV = fvec2(max(0.0f, value.x), max(0.0f, value.y));
}

const shared_ptr<RenderBuffer> ImageEntity::getRenderBuffer() const
{
	return _renderBuffer;
}

const TextureID ImageEntity::getDiffuseMap() const
{
	return _diffuseMap;
}

const string& ImageEntity::getDiffuseMapPath() const
{
	return _diffuseMapPath;
}

const fvec3 ImageEntity::getWireframeColor() const
{
	return _wireframeColor;
}

const fvec3 ImageEntity::getColor() const
{
	return _color;
}

const float ImageEntity::getTransparency() const
{
	return _transparency;
}

const bool ImageEntity::isWireframed() const
{
	return _isWireframed;
}

const bool ImageEntity::isCentered() const
{
	return _isCentered;
}

const bool ImageEntity::isMirroredHorizonally() const
{
	return _isMirroredHorizontally;
}

const bool ImageEntity::isMirroredVertically() const
{
	return _isMirroredVertically;
}

const bool ImageEntity::hasDiffuseMap() const
{
	return (_diffuseMap != 0);
}

const mat44 ImageEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const fvec2 ImageEntity::getPosition() const
{
	return _position;
}

const float ImageEntity::getRotation() const
{
	return _rotation;
}

const fvec2 ImageEntity::getSize() const
{
	return _size;
}

const fvec2 ImageEntity::getMinPosition() const
{
	return _minPosition;
}

const fvec2 ImageEntity::getMaxPosition() const
{
	return _maxPosition;
}

const fvec2 ImageEntity::getMultiplierUV() const
{
	return _multiplierUV;
}

const fvec2 ImageEntity::getAdderUV() const
{
	return _adderUV;
}

const unsigned int ImageEntity::getDepth() const
{
	return _depth;
}

void ImageEntity::setPerspectiveDepthEntity(bool value)
{
	_isPerspectiveDepthEntity = value;
}

void ImageEntity::setWireframed(bool value)
{
	_isWireframed = value;
}

const bool ImageEntity::isPerspectiveDepthEntity() const
{
	return _isPerspectiveDepthEntity;
}