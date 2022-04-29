#include "aabb_entity.hpp"

#include <algorithm>

using std::max;
using std::clamp;

Aabb::Aabb(const string & id)
	:
	_id(id)
{
	if(id.empty())
	{
		abort();
	}
}

void Aabb::setVertexBuffer(shared_ptr<VertexBuffer> value)
{
	_vertexBuffer = value;
}

void Aabb::updateTarget()
{
	if(hasParent())
	{
		if(_localPosition != _localPositionTarget)
		{
			const auto speedMultiplier = Mathematics::normalize(_localPositionTarget - _localPosition);
			_localPosition += (speedMultiplier * _localPositionTargetSpeed);

			if(fabsf(_localPositionTarget.x - _localPosition.x) <= _localPositionTargetSpeed)
			{
				_localPosition.x = _localPositionTarget.x;
			}
			if(fabsf(_localPositionTarget.y - _localPosition.y) <= _localPositionTargetSpeed)
			{
				_localPosition.y = _localPositionTarget.y;
			}
			if(fabsf(_localPositionTarget.z - _localPosition.z) <= _localPositionTargetSpeed)
			{
				_localPosition.z = _localPositionTarget.z;
			}
		}

		if(_localSize != _localSizeTarget)
		{
			const auto speedMultiplier = Mathematics::normalize(_localSizeTarget - _localSize);
			_localSize += (speedMultiplier * _localSizeTargetSpeed);

			_localSize = fvec3(max(0.0f, _localSize.x), max(0.0f, _localSize.y), max(0.0f, _localSize.z));
			if(fabsf(_localSizeTarget.x - _localSize.x) <= _localSizeTargetSpeed)
			{
				_localSize.x = _localPositionTarget.x;
			}
			if(fabsf(_localSizeTarget.y - _localSize.y) <= _localSizeTargetSpeed)
			{
				_localSize.y = _localPositionTarget.y;
			}
			if(fabsf(_localSizeTarget.z - _localSize.z) <= _localSizeTargetSpeed)
			{
				_localSize.z = _localPositionTarget.z;
			}
		}
	}
	else
	{
		if(_basePosition != _basePositionTarget)
		{
			const auto speedMultiplier = Mathematics::normalize(_basePositionTarget - _basePosition);
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
			const auto speedMultiplier = Mathematics::normalize(_baseSizeTarget - _baseSize);
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
}

void Aabb::updateTransformation()
{
	auto translationMatrix = Mathematics::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);

	auto scalingMatrix = Mathematics::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);

	_transformation = (translationMatrix * scalingMatrix);
}

void Aabb::setCollisionDirection(DirectionType value)
{
	_collisionDirection = value;
}

void Aabb::setRaycastResponsive(bool value)
{
	_isRaycastResponsive = value;
}

void Aabb::setCollisionResponsive(bool value)
{
	_isCollisionResponsive = value;
}

void Aabb::setCollided(bool value)
{
	_hasCollided = value;
}

void Aabb::setColor(const fvec3 & value)
{
	_color = fvec3(clamp(value.x, 0.0f, 1.0f), clamp(value.y, 0.0f, 1.0f), clamp(value.z, 0.0f, 1.0f));
}

void Aabb::setCentered(bool value)
{
	_isCentered = value;
}

void Aabb::setMinClipPosition(const fvec3 & value)
{
	_minClipPosition = value;
}

void Aabb::setMaxClipPosition(const fvec3 & value)
{
	_maxClipPosition = value;
}

void Aabb::setBasePosition(const fvec3 & value)
{
	_basePosition = value;
	_basePositionTarget = value;
}

void Aabb::setBaseSize(const fvec3 & value)
{
	_baseSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_baseSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

void Aabb::moveBase(const fvec3 & value)
{
	_basePosition += value;
	_basePositionTarget += value;
}

void Aabb::scaleBase(const fvec3 & value)
{
	_baseSize += value;
	_baseSizeTarget += value;
	_baseSize = fvec3(max(0.0f, _baseSize.x), max(0.0f, _baseSize.y), max(0.0f, _baseSize.z));
	_baseSizeTarget = fvec3(max(0.0f, _baseSizeTarget.x), max(0.0f, _baseSizeTarget.y), max(0.0f, _baseSizeTarget.z));
}

void Aabb::moveBaseTo(const fvec3 & target, float speed)
{
	_basePositionTarget = target;
	_basePositionTargetSpeed = speed;
}

void Aabb::scaleBaseTo(const fvec3 & target, float speed)
{
	_baseSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_baseSizeTargetSpeed = speed;
}

void Aabb::moveLocal(const fvec3 & value)
{
	_localPosition += value;
	_localPositionTarget += value;
}

void Aabb::scaleLocal(const fvec3 & value)
{
	_localSize += value;
	_localSizeTarget += value;
	_localSize = fvec3(max(0.0f, _localSize.x), max(0.0f, _localSize.y), max(0.0f, _localSize.z));
	_localSizeTarget = fvec3(max(0.0f, _localSizeTarget.x), max(0.0f, _localSizeTarget.y), max(0.0f, _localSizeTarget.z));
}

void Aabb::moveLocalTo(const fvec3 & target, float speed)
{
	_localPositionTarget = target;
	_localPositionTargetSpeed = speed;
}

void Aabb::scaleLocalTo(const fvec3 & target, float speed)
{
	_localSizeTarget = fvec3(max(0.0f, target.x), max(0.0f, target.y), max(0.0f, target.z));
	_localSizeTargetSpeed = speed;
}

void Aabb::setParentId(const string & value)
{
	_parentId = value;
}

void Aabb::setParentType(AabbParentType value)
{
	_parentType = value;
}

void Aabb::setLocalPosition(const fvec3 & value)
{
	_localPosition = value;
}

void Aabb::setLocalSize(const fvec3 & value)
{
	_localSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
}

const shared_ptr<VertexBuffer> Aabb::getVertexBuffer()const
{
	return _vertexBuffer;
}

const mat44 & Aabb::getTransformation() const
{
	return _transformation;
}

const fvec3 & Aabb::getLocalPosition() const
{
	return _localPosition;
}

const fvec3 & Aabb::getLocalSize() const
{
	return _localSize;
}

const fvec3 & Aabb::getBasePosition() const
{
	return _basePosition;
}

const fvec3 & Aabb::getBaseSize() const
{
	return _baseSize;
}

const fvec3 & Aabb::getColor() const
{
	return _color;
}

const fvec3 & Aabb::getMinClipPosition() const
{
	return _minClipPosition;
}

const fvec3 & Aabb::getMaxClipPosition() const
{
	return _maxClipPosition;
}

const string & Aabb::getParentId() const
{
	return _parentId;
}

const AabbParentType Aabb::getParentType() const
{
	return _parentType;
}

const DirectionType Aabb::getCollisionDirection() const
{
	return _collisionDirection;
}

const bool Aabb::isCentered() const
{
	return _isCentered;
}

const bool Aabb::isRaycastResponsive() const
{
	return _isRaycastResponsive;
}

const bool Aabb::isCollisionResponsive() const
{
	return _isCollisionResponsive;
}

const bool Aabb::hasParent() const
{
	return !_parentId.empty();
}

const bool Aabb::hasCollided() const
{
	return _hasCollided;
}