#include "aabb_entity.hpp"

#include <algorithm>

using std::max;

void AabbEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void AabbEntity::updateTransformation()
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

	if(_size != _sizeTarget)
	{
		auto speedMultiplier = Math::normalize(_sizeTarget - _size);
		_size += (speedMultiplier * _sizeTargetSpeed);

		_size = fvec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
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
	auto translationMatrix = Math::createTranslationMatrix(_position.x, _position.y, _position.z);

	auto scalingMatrix = Math::createScalingMatrix(_size.x, _size.y, _size.z);

	_transformationMatrix = (translationMatrix * scalingMatrix);
}

void AabbEntity::setFollowParentEntityTransformation(bool value)
{
	_mustFollowParentEntityTransformation = value;
}

void AabbEntity::setFollowParentEntityVisibility(bool value)
{
	_mustFollowParentEntityVisibility = value;
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

void AabbEntity::setColor(fvec3 value)
{
	_color = value;
}

void AabbEntity::setCentered(bool value)
{
	_isCentered = value;
}

void AabbEntity::setPosition(fvec3 value)
{
	_position = value;
	_positionTarget = value;
}

void AabbEntity::setSize(fvec3 value)
{
	_size = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_sizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void AabbEntity::move(fvec3 value)
{
	_position += value;
	_positionTarget += value;
}

void AabbEntity::scale(fvec3 value)
{
	_size += value;
	_sizeTarget += value;
	_size = fvec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
	_sizeTarget = fvec3(max(0.0f, _sizeTarget.x), max(0.0f, _sizeTarget.y), max(0.0f, _sizeTarget.z));
}

void AabbEntity::moveTo(fvec3 target, float speed)
{
	_positionTarget = target;
	_positionTargetSpeed = speed;
}

void AabbEntity::scaleTo(fvec3 target, float speed)
{
	_sizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_sizeTargetSpeed = speed;
}

void AabbEntity::setParentEntityID(const string& value)
{
	_parentEntityID = value;
}

void AabbEntity::setParentEntityType(AabbParentEntityType value)
{
	_parentEntityType = value;
}

void AabbEntity::setLocalPosition(fvec3 value)
{
	_localPosition = value;
}

void AabbEntity::setLocalSize(fvec3 value)
{
	_localSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

const shared_ptr<RenderBuffer> AabbEntity::getRenderBuffer()const
{
	return _renderBuffer;
}

const mat44& AabbEntity::getTransformationMatrix() const
{
	return _transformationMatrix;
}

const fvec3 AabbEntity::getLocalPosition() const
{
	return _localPosition;
}

const fvec3 AabbEntity::getLocalSize() const
{
	return _localSize;
}

const fvec3 AabbEntity::getPosition() const
{
	return _position;
}

const fvec3 AabbEntity::getSize() const
{
	return _size;
}

const fvec3 AabbEntity::getColor() const
{
	return _color;
}

const string& AabbEntity::getParentEntityID() const
{
	return _parentEntityID;
}

const AabbParentEntityType AabbEntity::getParentEntityType() const
{
	return _parentEntityType;
}

const Direction AabbEntity::getCollisionDirection() const
{
	return _collisionDirection;
}

const bool AabbEntity::isCentered() const
{
	return _isCentered;
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
	return !_parentEntityID.empty();
}

const bool AabbEntity::hasCollided() const
{
	return _hasCollided;
}

const bool AabbEntity::mustFollowParentEntityTransformation() const
{
	return _mustFollowParentEntityTransformation;
}

const bool AabbEntity::mustFollowParentEntityVisibility() const
{
	return _mustFollowParentEntityVisibility;
}