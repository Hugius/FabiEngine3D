#include "aabb_entity.hpp"

#include <algorithm>

using std::max;

void AabbEntity::updateTransformation()
{
	// Position target
	if(_position != _positionTarget)
	{
		// Update position
		auto speedMultiplier = Math::normalize(_positionTarget - _position);
		_position += (speedMultiplier * _positionTargetSpeed);

		// Correct position
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

	// Size target
	if(_size != _sizeTarget)
	{
		// Update size
		auto speedMultiplier = Math::normalize(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		// Correct size
		_size = Vec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
		if(fabsf(_sizeTarget.x - _size.x) <= _sizeTargetSpeed)
		{
			_size.x = _positionTarget.x;
		}
		if(fabsf(_sizeTarget.y - _size.y) <= _sizeTargetSpeed)
		{
			_size.y = _positionTarget.y;
		}
		if(fabsf(_sizeTarget.z - _size.z) <= _sizeTargetSpeed)
		{
			_size.z = _positionTarget.z;
		}
	}
}

void AabbEntity::updateTransformationMatrix()
{
	// Translation
	Matrix44 translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, _position.z);

	// Scaling
	Matrix44 scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, _size.z);

	// Final matrix
	_transformationMatrix = (translationMatrix * scalingMatrix);
}

void AabbEntity::setParent(const string& parentID, AabbParentType parentType)
{
	_parentID = parentID;
	_parentType = parentType;
}

void AabbEntity::setFollowParentTransformation(bool mustFollow)
{
	_mustFollowParentTransformation = mustFollow;
}

void AabbEntity::setFollowParentVisibility(bool mustFollow)
{
	_mustFollowParentVisibility = mustFollow;
}

void AabbEntity::setCollisionDirection(Direction value)
{
	_collisionDirection = value;
}

void AabbEntity::setRaycastResponsive(bool value)
{
	_isRaycastResponsive = value;
}

void AabbEntity::setCollisionResponsive(bool value)
{
	_isCollisionResponsive = value;
}

void AabbEntity::setCollided(bool value)
{
	_hasCollided = value;
}

void AabbEntity::setPosition(Vec3 value)
{
	_position = value;
	_positionTarget = value;
}

void AabbEntity::setSize(Vec3 value)
{
	_size = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_sizeTarget = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void AabbEntity::move(Vec3 value)
{
	_position += value;
	_positionTarget += value;
}

void AabbEntity::scale(Vec3 value)
{
	_size += value;
	_sizeTarget += value;
	_size = Vec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
	_sizeTarget = Vec3(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y), max(0.0f, _sizeTarget.z));
}

void AabbEntity::moveTo(Vec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void AabbEntity::scaleTo(Vec3 target, float speed)
{
	_sizeTarget = Vec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_sizeTargetSpeed = speed;
}

void AabbEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void AabbEntity::setLocalPosition(Vec3 value)
{
	_localPosition = value;
}

void AabbEntity::setLocalSize(Vec3 value)
{
	_localSize = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

const shared_ptr<RenderBuffer> AabbEntity::getRenderBuffer()const
{
	return _renderBuffer;
}

const Matrix44& AabbEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const Vec3 AabbEntity::getLocalPosition() const
{
	return _localPosition;
}

const Vec3 AabbEntity::getLocalSize() const
{
	return _localSize;
}

const Vec3 AabbEntity::getPosition() const
{
	return _position;
}

const Vec3 AabbEntity::getSize() const
{
	return _size;
}

const string& AabbEntity::getParentID() const
{
	return _parentID;
}
 
const AabbParentType AabbEntity::getParentType() const
{
	return _parentType;
}

const Direction AabbEntity::getCollisionDirection() const
{
	return _collisionDirection;
}

const bool AabbEntity::isRaycastResponsive() const
{
	return _isRaycastResponsive;
}

const bool AabbEntity::isCollisionResponsive() const
{
	return _isCollisionResponsive;
}

const bool AabbEntity::hasParent() const
{
	return !_parentID.empty();
}

const bool AabbEntity::hasCollided() const
{
	return _hasCollided;
}

const bool AabbEntity::hasRenderBuffer() const
{
	return (_renderBuffer != nullptr);
}

const bool AabbEntity::mustFollowParentTransformation() const
{
	return _mustFollowParentTransformation;
}

const bool AabbEntity::mustFollowParentVisibility() const
{
	return _mustFollowParentVisibility;
}