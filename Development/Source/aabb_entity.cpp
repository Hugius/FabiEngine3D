#include "aabb_entity.hpp"

#include <algorithm>

void AabbEntity::updateModelMatrix()
{
	// Temporary values
	Matrix44 translationMatrix;
	Matrix44 scalingMatrix;

	// Translation
	translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, _translation.z);

	// Scaling
	scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, _scaling.z);

	// Final matrix
	_modelMatrix = translationMatrix * scalingMatrix;
}

void AabbEntity::setTranslation(Vec3 value)
{
	_translation = value;
}

void AabbEntity::setScaling(Vec3 value)
{
	_scaling = Vec3(std::max(0.0f, value.x), std::max(0.0f, value.y), std::max(0.0f, value.z));
}

void AabbEntity::setParent(const string& ID, AabbParentType type)
{
	_parentID = ID;
	_parentType = type;
}

void AabbEntity::setCollisionDirection(const Direction& value)
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

void AabbEntity::translate(Vec3 value)
{
	_translation += value;
}

void AabbEntity::scale(Vec3 value)
{
	_scaling += value;
	_scaling = Vec3(std::max(0.0f, _scaling.x), std::max(0.0f, _scaling.y), std::max(0.0f, _scaling.z));
}

void AabbEntity::setLocalTranslation(Vec3 value)
{
	_localTranslation = value;
}

void AabbEntity::setLocalScaling(Vec3 value)
{
	_localScaling = value;
	_localScaling = Vec3(std::max(0.0f, _localScaling.x), std::max(0.0f, _localScaling.y), std::max(0.0f, _localScaling.z));
}

const Matrix44 & AabbEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const Vec3 AabbEntity::getLocalTranslation() const
{
	return _localTranslation;
}

const Vec3 AabbEntity::getLocalScaling() const
{
	return _localScaling;
}

const Vec3 AabbEntity::getTranslation() const
{
	return _translation;
}

const Vec3 AabbEntity::getScaling() const
{
	return _scaling;
}

const string& AabbEntity::getParentID() const
{
	return _parentID;
}

const AabbParentType& AabbEntity::getParentType() const
{
	return _parentType;
}

const Direction& AabbEntity::getCollisionDirection() const
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