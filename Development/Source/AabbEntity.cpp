#include <GLM/gtc/matrix_transform.hpp>

#include <WE3D/AabbEntity.hpp>

void AabbEntity::updateModelMatrix()
{
	p_modelMatrix = mat4(1.0f);
	p_modelMatrix = glm::translate(p_modelMatrix, p_translation);
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.z), vec3(0.0f, 0.0f, 1.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.y), vec3(0.0f, 1.0f, 0.0f));
	p_modelMatrix = glm::rotate(p_modelMatrix, glm::radians(p_rotation.x), vec3(1.0f, 0.0f, 0.0f));
	p_modelMatrix = glm::scale(p_modelMatrix, p_scaling);
}

void AabbEntity::setTranslation(vec3 val)
{
	p_translation = val;
}

void AabbEntity::setRotation(vec3 val)
{
	p_rotation = val;
}

void AabbEntity::setScaling(vec3 val)
{
	p_scaling = val;
}

void AabbEntity::setParentID(const string & ID)
{
	p_parentID = ID;
}

void AabbEntity::setCollisionDirection(const CollisionDir& direction)
{
	p_collisionDirection = direction;
}

void AabbEntity::setResponsiveness(bool val)
{
	p_responsive = val;
}

void AabbEntity::translate(vec3 val, float delta)
{
	p_translation += val * delta;
}

void AabbEntity::rotate(vec3 val, float delta)
{
	p_rotation += val * delta;
}

void AabbEntity::scale(vec3 val, float delta)
{
	p_scaling += val * delta;
}

const mat4 & AabbEntity::getModelMatrix() const
{
	return p_modelMatrix;
}

const vec3 AabbEntity::getTranslation() const
{
	return p_translation;
}

const vec3 AabbEntity::getRotation() const
{
	return p_rotation;
}

const vec3 AabbEntity::getScaling() const
{
	return p_scaling;
}

const string& AabbEntity::getParentID() const
{
	return p_parentID;
}

const CollisionDir& AabbEntity::getCollisionDirection() const
{
	return p_collisionDirection;
}

const bool AabbEntity::isResponsive() const
{
	return p_responsive;
}
