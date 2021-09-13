#include "image_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ImageEntity::updateTransformation()
{
	// Position target
	if (_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalizeVector(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
		if (fabsf(_positionTarget.x - _position.x) <= _positionTargetSpeed)
		{
			_position.x = _positionTarget.x;
		}
		if (fabsf(_positionTarget.y - _position.y) <= _positionTargetSpeed)
		{
			_position.y = _positionTarget.y;
		}
	}

	// Rotation target
	if (_rotation != _rotationTarget)
	{
		// Update rotation
		auto difference = fabsf(_rotation - _rotationTarget);
		float multiplier = ((difference < 180.0f) ? 1.0f : -1.0f);
		float speed = (_rotationTargetSpeed * multiplier);
		_rotation += ((_rotation < _rotationTarget) ? speed : (_rotation > _rotationTarget) ? -speed : 0.0f);

		// Correct rotation
		_rotation = Math::limitAngle(_rotation);
		if (Math::calculateAngleDifference(_rotation, _rotationTarget) <= _rotationTargetSpeed)
		{
			_rotation = _rotationTarget;
		}
	}

	// Size target
	if (_size != _sizeTarget)
	{
		// Update size
		auto speedMultiplier = Math::normalizeVector(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		// Correct size
		_size = Vec2(max(0.0f, _size.x), max(0.0f, _size.y));
		if (fabsf(_sizeTarget.x - _size.x) <= _sizeTargetSpeed)
		{
			_size.x = _positionTarget.x;
		}
		if (fabsf(_sizeTarget.y - _size.y) <= _sizeTargetSpeed)
		{
			_size.y = _positionTarget.y;
		}
	}
}

void ImageEntity::updateTransformationMatrix()
{
	Matrix44 translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, 0.0f);
	Matrix44 rotationMatrix = Math::createRotationMatrixX(Math::convertToRadians(_rotation));
	Matrix44 scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, 1.0f);

	_transformationMatrix = (translationMatrix * rotationMatrix * scalingMatrix);
}

void ImageEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void ImageEntity::setDiffuseMap(TextureID value)
{
	_diffuseMap = value;
}

void ImageEntity::setDiffuseMapPath(const string& value)
{
	_diffuseMapPath = value;
}

void ImageEntity::setColor(Vec3 value)
{
	_color = Vec3(clamp(value.r, 0.0f, 1.0f), clamp(value.g, 0.0f, 1.0f), clamp(value.b, 0.0f, 1.0f));
}

void ImageEntity::setMirroredHorizontally(bool value)
{
	_isMirroredHorizontally = value;
}

void ImageEntity::setMirroredVertically(bool value)
{
	_isMirroredVertically = value;
}

void ImageEntity::setAlpha(float value)
{
	_alpha = clamp(value, 0.0f, 1.0f);
}

void ImageEntity::setPosition(Vec2 value)
{
	_position = value;
	_positionTarget = value;
}

void ImageEntity::setRotation(float value)
{
	_rotation = Math::limitAngle(value);
	_rotationTarget = Math::limitAngle(value);
}

void ImageEntity::setSize(Vec2 value)
{
	_size = Vec2(max(0.0f, value.x), max(0.0f, value.y));
	_sizeTarget = Vec2(max(0.0f, value.x), max(0.0f, value.y));
}

void ImageEntity::move(Vec2 value)
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

void ImageEntity::scale(Vec2 value)
{
	_size += value;
	_sizeTarget += value;
	_size = Vec2(max(0.0f, _size.x), max(0.0f, _size.y));
	_sizeTarget = Vec2(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y));
}

void ImageEntity::moveTo(Vec2 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void ImageEntity::rotateTo(float target, float speed)
{
	_rotationTarget = Math::limitAngle(target);
	_rotationTargetSpeed = speed;
}

void ImageEntity::scaleTo(Vec2 target, float speed)
{
	_sizeTarget = Vec2(max(0.0f, target.x), max(0.0f, target.y));
	_sizeTargetSpeed = speed;
}

void ImageEntity::setMinPosition(Vec2 value)
{
	_minPosition = value;
}

void ImageEntity::setMaxPosition(Vec2 value)
{
	_maxPosition = value;
}

void ImageEntity::setDepth(unsigned int value)
{
	_depth = value;
}

void ImageEntity::startSpriteAnimation(int loops)
{
	if (_isSpriteAnimationStarted)
	{
		Logger::throwError("ImageEntity::startSpriteAnimation::1");
	}
	if (loops < -1)
	{
		Logger::throwError("ImageEntity::startSpriteAnimation::2");
	}

	_isSpriteAnimationStarted = true;
	_passedSpriteAnimationFrames = 0;
	_spriteAnimationLoops = 0;
	_maxSpriteAnimationLoops = loops;
}

void ImageEntity::pauseSpriteAnimation()
{
	if (!_isSpriteAnimationStarted)
	{
		Logger::throwError("ImageEntity::pauseSpriteAnimation::1");
	}
	else if (_isSpriteAnimationPaused)
	{
		Logger::throwError("ImageEntity::pauseSpriteAnimation::2");
	}

	_isSpriteAnimationPaused = true;
}

void ImageEntity::resumeSpriteAnimation()
{
	if (!_isSpriteAnimationPaused)
	{
		Logger::throwError("ImageEntity::resumeSpriteAnimation");
	}

	_isSpriteAnimationPaused = false;
}

void ImageEntity::stopSpriteAnimationAnimation()
{
	if (!_isSpriteAnimationStarted)
	{
		Logger::throwError("ImageEntity::stopSpriteAnimation");
	}

	_isSpriteAnimationStarted = false;
}

void ImageEntity::setSpriteAnimationRowIndex(unsigned int value)
{
	_spriteAnimationRowIndex = value;
}

void ImageEntity::setSpriteAnimationColumnIndex(unsigned int value)
{
	_spriteAnimationColumnIndex = value;
}

void ImageEntity::setTotalSpriteAnimationRows(unsigned int value)
{
	_totalSpriteAnimationRows = value;
}

void ImageEntity::setTotalSpriteAnimationColumns(unsigned int value)
{
	_totalSpriteAnimationColumns = value;
}

void ImageEntity::setMaxSpriteAnimationFramestep(unsigned int value)
{
	_maxSpriteAnimationFramestep = value;
}

void ImageEntity::increasePassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames++;
}

void ImageEntity::resetPassedSpriteAnimationFrames()
{
	_passedSpriteAnimationFrames = 0;
}

void ImageEntity::increaseSpriteAnimationLoops()
{
	_spriteAnimationLoops++;
}

const bool ImageEntity::isSpriteAnimationStarted()
{
	return _isSpriteAnimationStarted;
}

const bool ImageEntity::isSpriteAnimationPaused()
{
	return _isSpriteAnimationPaused;
}

const int ImageEntity::getMaxSpriteAnimationLoops()
{
	return _maxSpriteAnimationLoops;
}

const unsigned int ImageEntity::getPassedSpriteAnimationFrames()
{
	return _passedSpriteAnimationFrames;
}

const unsigned int ImageEntity::getMaxSpriteAnimationFramestep()
{
	return _maxSpriteAnimationFramestep;
}

const unsigned int ImageEntity::getTotalSpriteAnimationRows()
{
	return _totalSpriteAnimationRows;
}

const unsigned int ImageEntity::getTotalSpriteAnimationColumns()
{
	return _totalSpriteAnimationColumns;
}

const unsigned int ImageEntity::getSpriteAnimationRowIndex()
{
	return _spriteAnimationRowIndex;
}

const unsigned int ImageEntity::getSpriteAnimationColumnIndex()
{
	return _spriteAnimationColumnIndex;
}

const unsigned int ImageEntity::getSpriteAnimationLoops()
{
	return _spriteAnimationLoops;
}

const bool ImageEntity::hasRenderBuffer()
{
	return (_renderBuffer != nullptr);
}

const shared_ptr<RenderBuffer> ImageEntity::getRenderBuffer()
{
	return _renderBuffer;
}

const TextureID ImageEntity::getDiffuseMap()
{
	return _diffuseMap;
}

const string& ImageEntity::getDiffuseMapPath()
{
	return _diffuseMapPath;
}

const Vec3 ImageEntity::getColor()
{
	return _color;
}

const float ImageEntity::getAlpha()
{
	return _alpha;
}

const bool ImageEntity::isMirroredHorizonally()
{
	return _isMirroredHorizontally;
}

const bool ImageEntity::isMirroredVertically()
{
	return _isMirroredVertically;
}

const bool ImageEntity::hasDiffuseMap()
{
	return (_diffuseMap != 0);
}

const Matrix44 ImageEntity::getTransformationMatrix()
{
	return _transformationMatrix;
}

const Vec2 ImageEntity::getPosition()
{
	return _position;
}

const float ImageEntity::getRotation()
{
	return _rotation;
}

const Vec2 ImageEntity::getSize()
{
	return _size;
}

const Vec2 ImageEntity::getMinPosition()
{
	return _minPosition;
}

const Vec2 ImageEntity::getMaxPosition()
{
	return _maxPosition;
}

const unsigned int ImageEntity::getDepth()
{
	return _depth;
}

void ImageEntity::setPerspectiveDepthEntity(bool value)
{
	_isPerspectiveDepthEntity = value;
}

const bool ImageEntity::isPerspectiveDepthEntity()
{
	return _isPerspectiveDepthEntity;
}