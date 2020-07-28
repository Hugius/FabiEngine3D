#include "aabb_entity.hpp"

#include <GLM\\gtc\\matrix_transform.hpp>

void AabbEntity::updateModelMatrix()
{
	_modelMatrix = mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, _translation);
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	_modelMatrix = glm::rotate(_modelMatrix, glm::radians(_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, _scaling);
}

void AabbEntity::setTranslation(vec3 val)
{
	_translation = val;
}

void AabbEntity::setRotation(vec3 val)
{
	_rotation = val;
}

void AabbEntity::setScaling(vec3 val)
{
	_scaling = val;
}

void AabbEntity::setParentID(const string& ID)
{
	_parentID = ID;
}

void AabbEntity::setCollisionDirection(const CollisionDir& direction)
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

void AabbEntity::rotate(vec3 val)
{
	_rotation += val;
}

void AabbEntity::scale(vec3 val)
{
	_scaling += val;
}

const mat4 & AabbEntity::getModelMatrix() const
{
	return _modelMatrix;
}

const vec3 AabbEntity::getTranslation() const
{
	return _translation;
}

const vec3 AabbEntity::getRotation() const
{
	return _rotation;
}

const vec3 AabbEntity::getScaling() const
{
	return _scaling;
}

const string& AabbEntity::getParentID() const
{
	return _parentID;
}

const CollisionDir& AabbEntity::getCollisionDirection() const
{
	return _collisionDirection;
}

const bool AabbEntity::isResponsive() const
{
	return _responsive;
}
