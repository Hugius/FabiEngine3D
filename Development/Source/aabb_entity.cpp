#include "aabb_entity.hpp"

#include <algorithm>

void AabbEntity::updateModelMatrix()
{
	// Temporary values
	Matrix44 translationMatrix;
	Matrix44 scalingMatrix;

	// Translation
	translationMatrix = Matrix44::createTranslation(_position.x, _position.y, _position.z);

	// Scaling
	scalingMatrix = Matrix44::createScaling(_size.x, _size.y, _size.z);

	// Final matrix
	_modelMatrix = translationMatrix * scalingMatrix;
}

void AabbEntity::setPosition(Vec3 value)
{
	_position = value;
}

void AabbEntity::setSize(Vec3 value)
{
	_size = Vec3(std::max(0.0f, value.x), std::max(0.0f, value.y), std::max(0.0f, value.z));
}

void AabbEntity::setParent(const string& ID, AabbParentType type)
{
	_parentID = ID;
	_parentType = type;
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

void AabbEntity::move(Vec3 value)
{
	_position += value;
}

void AabbEntity::scale(Vec3 value)
{
	_size += value;
	_size = Vec3(std::max(0.0f, _size.x), std::max(0.0f, _size.y), std::max(0.0f, _size.z));
}

void AabbEntity::setLocalPosition(Vec3 value)
{
	_localPosition = value;
}

void AabbEntity::setLocalSize(Vec3 value)
{
	_localSize = value;
	_localSize = Vec3(std::max(0.0f, _localSize.x), std::max(0.0f, _localSize.y), std::max(0.0f, _localSize.z));
}

const Matrix44 & AabbEntity::getModelMatrix() const
{
	return _modelMatrix;
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