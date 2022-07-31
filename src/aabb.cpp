#include "aabb.hpp"

#include <algorithm>
#include <iostream>

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
	if(_parentId.empty())
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
	else
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
}

void Aabb::updateTransformation()
{
	auto translationMatrix = Mathematics::createTranslationMatrix(_basePosition.x, _basePosition.y, _basePosition.z);
	auto scalingMatrix = Mathematics::createScalingMatrix(_baseSize.x, _baseSize.y, _baseSize.z);

	_transformation = (translationMatrix * scalingMatrix);
}

void Aabb::setRaycastResponsive(bool value)
{
	_isRaycastResponsive = value;
}

void Aabb::setCollisionResponsive(bool value)
{
	_isCollisionResponsive = value;
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

void Aabb::setVisible(bool value)
{
	_isVisible = value;
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
	_localPositionTarget = value;
}

void Aabb::setLocalSize(const fvec3 & value)
{
	_localSize = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
	_localSizeTarget = fvec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
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

const string & Aabb::getId() const
{
	return _id;
}

const string & Aabb::getParentId() const
{
	return _parentId;
}

const AabbParentType Aabb::getParentType() const
{
	return _parentType;
}

const bool Aabb::isVisible() const
{
	return _isVisible;
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

void Aabb::followModelParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::MODEL)
	{
		abort();
	}

	const auto newAabbSize = (_localSize * parentSize);

	float rotation;
	DirectionType rotationDirection;

	if((parentRotation.x > parentRotation.y) && (parentRotation.x > parentRotation.z))
	{
		rotation = parentRotation.x;
		rotationDirection = DirectionType::X;
	}
	else if((parentRotation.y > parentRotation.x) && (parentRotation.y > parentRotation.z))
	{
		rotation = parentRotation.y;
		rotationDirection = DirectionType::Y;
	}
	else if((parentRotation.z > parentRotation.x) && (parentRotation.z > parentRotation.y))
	{
		rotation = parentRotation.z;
		rotationDirection = DirectionType::Z;
	}
	else
	{
		rotation = 0.0f;
	}

	const auto is90Degrees = ((rotation > 45.0f) && (rotation < 135.0f));
	const auto is180Degrees = ((rotation >= 135.0f) && (rotation <= 225.0f));
	const auto is270Degrees = ((rotation > 225.0f) && (rotation < 315.0f));
	const auto roundedRotation = (is90Degrees ? 90.0f : is180Degrees ? 180.0f : is270Degrees ? 270.0f : 0.0f);

	if(is90Degrees || is270Degrees)
	{
		switch(rotationDirection)
		{
			case DirectionType::X:
			{
				setBaseSize(fvec3(newAabbSize.x, newAabbSize.z, newAabbSize.y));

				break;
			}
			case DirectionType::Y:
			{
				setBaseSize(fvec3(newAabbSize.z, newAabbSize.y, newAabbSize.x));

				break;
			}
			case DirectionType::Z:
			{
				setBaseSize(fvec3(newAabbSize.y, newAabbSize.x, newAabbSize.z));

				break;
			}
		}
	}
	else
	{
		setBaseSize(newAabbSize);
	}

	if((roundedRotation == 0.0f) || _isCentered)
	{
		const auto localPosition = (_localPosition * parentSize);

		setBasePosition(parentPosition + localPosition);
	}
	else
	{
		fvec3 localPosition;

		if(rotationDirection == DirectionType::Y)
		{
			localPosition = (_localPosition * parentSize);
		}
		else
		{
			const auto offset = fvec3(0.0f, (_localPosition.y * 0.5f), 0.0f);

			localPosition = ((_localPosition + offset) * parentSize);
		}

		mat44 rotationMatrix;
		fvec3 rotationOffset;

		if(rotationDirection == DirectionType::X)
		{
			rotationMatrix = Mathematics::createRotationMatrixX(Mathematics::convertToRadians(roundedRotation));
			rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.z) * 0.5f), 0.0f);
		}
		else if(rotationDirection == DirectionType::Y)
		{
			rotationMatrix = Mathematics::createRotationMatrixY(Mathematics::convertToRadians(roundedRotation));
			rotationOffset = fvec3(0.0f);
		}
		else if(rotationDirection == DirectionType::Z)
		{
			rotationMatrix = Mathematics::createRotationMatrixZ(Mathematics::convertToRadians(roundedRotation));
			rotationOffset = fvec3(0.0f, -((is180Degrees ? newAabbSize.y : newAabbSize.x) * 0.5f), 0.0f);
		}

		auto rotatedLocalPosition = (rotationMatrix * fvec4(localPosition.x, localPosition.y, localPosition.z, 1.0f));

		rotatedLocalPosition += rotationOffset;

		setBasePosition(parentPosition + rotatedLocalPosition);
	}
}

void Aabb::followModelParentVisibility(bool isParentVisible, const string & parentLevelOfDetailId, bool isParentLevelOfDetailed)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::MODEL)
	{
		abort();
	}

	if(isParentVisible)
	{
		if(parentLevelOfDetailId.empty())
		{
			setRaycastResponsive(true);
			setCollisionResponsive(true);
		}
		else
		{
			setRaycastResponsive(!isParentLevelOfDetailed);
			setCollisionResponsive(!isParentLevelOfDetailed);
		}
	}
	else
	{
		setVisible(false);
		setRaycastResponsive(false);
		setCollisionResponsive(false);
	}
}

void Aabb::followQuad3dParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::QUAD3D)
	{
		abort();
	}

	auto refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
	auto refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
	auto refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);

	refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
	refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
	refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

	fvec3 newAabbSize;

	if(refRotationX > refRotationY && refRotationX > refRotationZ)
	{
		const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
		const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));

		newAabbSize.x = max(MIN_SIZE, parentSize.x);
		newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
		newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
	}
	else if(refRotationY > refRotationX && refRotationY > refRotationZ)
	{
		const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
		const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));

		newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
		newAabbSize.y = max(MIN_SIZE, parentSize.y);
		newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
	}
	else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
	{
		const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
		const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));

		newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
		newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
		newAabbSize.z = MIN_SIZE;
	}
	else
	{
		newAabbSize.x = max(MIN_SIZE, parentSize.x);
		newAabbSize.y = max(MIN_SIZE, parentSize.y);
		newAabbSize.z = MIN_SIZE;
	}

	auto newAabbPosition = (parentPosition + _localPosition);

	if(!_isCentered)
	{
		newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
	}

	setBasePosition(newAabbPosition);
	setBaseSize(newAabbSize);
}

void Aabb::followQuad3dParentVisibility(bool isParentVisible)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::QUAD3D)
	{
		abort();
	}

	if(isParentVisible)
	{
		setRaycastResponsive(true);
		setCollisionResponsive(true);
	}
	else
	{
		setVisible(false);
		setRaycastResponsive(false);
		setCollisionResponsive(false);
	}
}

void Aabb::followText3dParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::TEXT3D)
	{
		abort();
	}

	float refRotationX = Mathematics::calculateReferenceAngle(parentRotation.x);
	float refRotationY = Mathematics::calculateReferenceAngle(parentRotation.y);
	float refRotationZ = Mathematics::calculateReferenceAngle(parentRotation.z);

	refRotationX = ((refRotationX <= 45.0f) ? refRotationX : (refRotationX == 90.0f) ? 90.0f : (90.0f - refRotationX));
	refRotationY = ((refRotationY <= 45.0f) ? refRotationY : (refRotationY == 90.0f) ? 90.0f : (90.0f - refRotationY));
	refRotationZ = ((refRotationZ <= 45.0f) ? refRotationZ : (refRotationZ == 90.0f) ? 90.0f : (90.0f - refRotationZ));

	fvec3 newAabbSize;

	if(refRotationX > refRotationY && refRotationX > refRotationZ)
	{
		const auto xSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.x)));
		const auto xCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.x)));

		newAabbSize.x = max(MIN_SIZE, parentSize.x);
		newAabbSize.y = max(MIN_SIZE, (xCosRotation * parentSize.y));
		newAabbSize.z = max(MIN_SIZE, (xSinRotation * parentSize.y));
	}
	else if(refRotationY > refRotationX && refRotationY > refRotationZ)
	{
		const auto ySinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.y)));
		const auto yCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.y)));

		newAabbSize.x = max(MIN_SIZE, (yCosRotation * parentSize.x));
		newAabbSize.y = max(MIN_SIZE, parentSize.y);
		newAabbSize.z = max(MIN_SIZE, (ySinRotation * parentSize.x));
	}
	else if(refRotationZ > refRotationX && refRotationZ > refRotationY)
	{
		const auto zSinRotation = fabsf(sinf(Mathematics::convertToRadians(parentRotation.z)));
		const auto zCosRotation = fabsf(cosf(Mathematics::convertToRadians(parentRotation.z)));

		newAabbSize.x = max(MIN_SIZE, ((zCosRotation * parentSize.x) + (zSinRotation * parentSize.y)));
		newAabbSize.y = max(MIN_SIZE, ((zSinRotation * parentSize.x) + (zCosRotation * parentSize.y)));
		newAabbSize.z = MIN_SIZE;
	}
	else
	{
		newAabbSize.x = max(MIN_SIZE, parentSize.x);
		newAabbSize.y = max(MIN_SIZE, parentSize.y);
		newAabbSize.z = MIN_SIZE;
	}

	auto newAabbPosition = (parentPosition + _localPosition);

	if(!_isCentered)
	{
		newAabbPosition.y -= ((newAabbSize.y - parentSize.y) * 0.5f);
	}

	setBasePosition(newAabbPosition);
	setBaseSize(newAabbSize);
}

void Aabb::followText3dParentVisibility(bool isParentVisible)
{
	if(_parentId.empty())
	{
		abort();
	}

	if(_parentType != AabbParentType::TEXT3D)
	{
		abort();
	}

	if(isParentVisible)
	{
		setRaycastResponsive(true);
		setCollisionResponsive(true);
	}
	else
	{
		setVisible(false);
		setRaycastResponsive(false);
		setCollisionResponsive(false);
	}
}