#include "aabb_entity.hpp"

void AabbEntity::updateModelMatrix()
{
	Matrix44 translationMatrix = Matrix44::createTranslation(_translation.x, _translation.y, _translation.z);
	Matrix44 scalingMatrix = Matrix44::createScaling(_scaling.x, _scaling.y, _scaling.z);

	_modelMatrix = translationMatrix * scalingMatrix;
}

void AabbEntity::setTranslation(Vec3 val)
{
	_translation = val;
}

void AabbEntity::setScaling(Vec3 val)
{
	_scaling = val;
}

void AabbEntity::setParent(const string& ID, AabbParentType type)
{
	_parentID = ID;
	_parentType = type;
}

void AabbEntity::setCollisionDirection(const Direction& direction)
{
	_collisionDirection = direction;
}

void AabbEntity::setResponsiveness(bool val)
{
	_responsive = val;
}

void AabbEntity::translate(Vec3 val)
{
	_translation += val;
}

void AabbEntity::scale(Vec3 val)
{
	_scaling += val;
}

void AabbEntity::setLocalTranslation(Vec3 val)
{
	_localTranslation = val;
}

void AabbEntity::setLocalScaling(Vec3 val)
{
	_localScaling = val;
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

const bool AabbEntity::isResponsive() const
{
	return _responsive;
}
