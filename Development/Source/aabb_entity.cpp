#include "aabb_entity.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>

void AabbEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _translation);
	_modelMatrix = glm::scale(_modelMatrix, _scaling);
}

void AabbEntity::setTranslation(vec3 val)
{
	_translation = val;
}

void AabbEntity::setScaling(vec3 val)
{
	_scaling = val;
}

void AabbEntity::setParent(const string& ID, AabbParentType type)
{
	_parentID = ID;
	_parentType = type;
}

void AabbEntity::setCollisionDirection(const CollisionDirection& direction)
{
	_collisionDirection = direction;
}

void AabbEntity::setResponsiveness(bool val)
{
	_responsive = val;
}

void AabbEntity::translate(vec3 val)
{
	_translation += val;
}

void AabbEntity::scale(vec3 val)
{
	_scaling += val;
}

void AabbEntity::setLocalTranslation(vec3 val)
{
	_localTranslation = val;
}

const mat4 & AabbEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const vec3 AabbEntity::getLocalTranslation() const
{
	return _localTranslation;
}

const vec3 AabbEntity::getTranslation() const
{
	return _translation;
}

const vec3 AabbEntity::getScaling() const
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

const CollisionDirection& AabbEntity::getCollisionDirection() const
{
	return _collisionDirection;
}

const bool AabbEntity::isResponsive() const
{
	return _responsive;
}
