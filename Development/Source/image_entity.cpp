#include "image_entity.hpp"
#include "logger.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void ImageEntity::updateTransformationMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_position.x, _position.y, 0.0f);
	Matrix44 rotationMatrix = Matrix44::createRotationX(Math::convertToRadians(_rotation));
	Matrix44 scalingMatrix = Matrix44::createScaling(_size.x, _size.y, 1.0f);

	_transformationMatrix = translationMatrix * rotationMatrix * scalingMatrix;
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
	_alpha = max(0.0f, value);
}

void ImageEntity::setPosition(Vec2 value)
{
	_position = value;
}

void ImageEntity::setRotation(float value)
{
	_rotation = value;

	// Limit rotation
	_rotation = fmodf(_rotation, 360.0f);
}

void ImageEntity::setSize(Vec2 value)
{
	_size = Vec2(max(0.0f, value.x), max(0.0f, value.y));
}

void ImageEntity::move(Vec2 value)
{
	_position += value;
}

void ImageEntity::rotate(float value)
{
	_rotation += value;

	// Limit rotation
	_rotation = fmodf(_rotation, 360.0f);
}

void ImageEntity::scale(Vec2 value)
{
	_size += value;
	_size = Vec2(max(0.0f, _size.x), max(0.0f, _size.y));
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

void ImageEntity::setSpriteAnimationRowIndex(int value)
{
	_spriteAnimationRowIndex = max(0, value);
}

void ImageEntity::setSpriteAnimationColumnIndex(int value)
{
	_spriteAnimationColumnIndex = max(0, value);
}

void ImageEntity::setTotalSpriteAnimationRows(int value)
{
	_totalSpriteAnimationRows = max(0, value);
}

void ImageEntity::setTotalSpriteAnimationColumns(int value)
{
	_totalSpriteAnimationColumns = max(0, value);
}

void ImageEntity::setMaxSpriteAnimationFramestep(int value)
{
	_maxSpriteAnimationFramestep = max(0, value);
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

const int ImageEntity::getPassedSpriteAnimationFrames()
{
	return _passedSpriteAnimationFrames;
}

const int ImageEntity::getMaxSpriteAnimationFramestep()
{
	return _maxSpriteAnimationFramestep;
}

const int ImageEntity::getTotalSpriteAnimationRows()
{
	return _totalSpriteAnimationRows;
}

const int ImageEntity::getTotalSpriteAnimationColumns()
{
	return _totalSpriteAnimationColumns;
}

const int ImageEntity::getSpriteAnimationRowIndex()
{
	return _spriteAnimationRowIndex;
}

const int ImageEntity::getSpriteAnimationColumnIndex()
{
	return _spriteAnimationColumnIndex;
}

const int ImageEntity::getSpriteAnimationLoops()
{
	return _spriteAnimationLoops;
}

const int ImageEntity::getMaxSpriteAnimationLoops()
{
	return _maxSpriteAnimationLoops;
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