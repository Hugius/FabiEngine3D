#include "aabb_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

void AabbEntity::setMesh(shared_ptr<VertexBuffer> value)
{
	_mesh = value;
}

void AabbEntity::updateTarget()
{
	if(_basePosition != _basePositionTarget)
	{
		auto speedMultiplier = Math::normalize(_basePositionTarget - _basePosition);
		_basePosition += (speedMultiplier * _basePositionTargetSpeed);

		if(fabsf(_basePositionTarget.x - _basePosition.x) <= _basePositionTargetSpeed)
		{
			_basePosition.x = _basePositionTarget.x;
		}
		if(fabsf(_basePositionTarget.y - _basePosition.y) <= _basePositionTargetSpeed)
		{
			_basePosition.y = _basePositionTarget.y;
		}
		if(fabsf(_basePositionTarget.z - _basePosition.z) <= _basePositionTargetSpeed)
		{
			_basePosition.z = _basePositionTarget.z;
		}
	}

	if(_baseSize != _baseSizeTarget)
	{
		auto speedMultiplier = Math::normalize(_baseSizeTarget - _baseSize);
		_baseSize += (speedMultiplier * _baseSizeTargetSpeed);

		_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
		if(fabsf(_baseSizeTarget.x - _baseSize.x) <= _baseSizeTargetSpeed)
		{
			_baseSize.x = _basePositionTarget.x;
		}
		if(fabsf(_baseSizeTarget.y - _baseSize.y) <= _baseSizeTargetSpeed)
		{
			_baseSize.y = _basePositionTarget.y;
		}
		if(fabsf(_baseSizeTarget.z - _baseSize.z) <= _baseSizeTargetSpeed)
		{
			_baseSize.z = _basePositionTarget.z;
		}
	}
}

void AabbEntity::updateTransformation()
{
	auto translationMatrix = Math::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);

	auto scalingMatrix = Math::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);

	_transformation = (translationMatrix * scalingMatrix);
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

void AabbEntity::setColor(const fvec3& value)
{
	_color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void AabbEntity::setCentered(bool value)
{
	_isCentered = value;
}

void AabbEntity::setBasePosition(const fvec3& value)
{
	_basePosition = value;
	_basePositionTarget = value;
}

void AabbEntity::setBaseSize(const fvec3& value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void AabbEntity::moveBase(const fvec3& value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void AabbEntity::scaleBase(const fvec3& value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void AabbEntity::moveBaseTo(const fvec3& target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = speed;
}

void AabbEntity::scaleBaseTo(const fvec3& target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = speed;
}

void AabbEntity::setParentId(const string& value)
{
	_parentId = value;
}

void AabbEntity::setParentType(AabbParentType value)
{
	_parentType = value;
}

void AabbEntity::setLocalPosition(const fvec3& value)
{
	_localPosition = value;
}

void AabbEntity::setLocalSize(const fvec3& value)
{
	_localSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

const shared_ptr<VertexBuffer> AabbEntity::getMesh()const
{
	return _mesh;
}

const mat44& AabbEntity::getTransformation() const
{
	return _transformation;
}

const fvec3& AabbEntity::getLocalPosition() const
{
	return _localPosition;
}

const fvec3& AabbEntity::getLocalSize() const
{
	return _localSize;
}

const fvec3& AabbEntity::getBasePosition() const
{
	return _basePosition;
}

const fvec3& AabbEntity::getBaseSize() const
{
	return _baseSize;
}

const fvec3& AabbEntity::getColor() const
{
	return _color;
}

const string& AabbEntity::getParentId() const
{
	return _parentId;
}

const AabbParentType AabbEntity::getParentType() const
{
	return _parentType;
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
	return !_parentId.empty();
}

const bool AabbEntity::hasCollided() const
{
	return _hasCollided;
}