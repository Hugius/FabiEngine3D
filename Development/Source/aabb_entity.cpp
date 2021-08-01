#include "aabb_entity.hpp"

#include <algorithm>

using std::max;

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
	_size = Vec3(max(0.0f, value.x), max(0.0f, value.y), max(0.0f, value.z));
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
	_size = Vec3(max(0.0f, _size.x), max(0.0f, _size.y), max(0.0f, _size.z));
}

void AabbEntity::setRenderBuffer(shared_ptr<RenderBuffer> value)
{
	_renderBuffer = value;
}

void AabbEntity::setLocalPosition(Vec3 value)
{
	_localPosition = value;
}

void AabbEntity::setLocalSize(Vec3 value)
{
	_localSize = value;
	_localSize = Vec3(max(0.0f, _localSize.x), max(0.0f, _localSize.y), max(0.0f, _localSize.z));
}

const shared_ptr<RenderBuffer> AabbEntity::getRenderBuffer()
{
	return _renderBuffer;
}

const Matrix44 & AabbEntity::getModelMatrix()
{
	return _modelMatrix;
}

const Vec3 AabbEntity::getLocalPosition()
{
	return _localPosition;
}

const Vec3 AabbEntity::getLocalSize()
{
	return _localSize;
}

const Vec3 AabbEntity::getPosition()
{
	return _position;
}

const Vec3 AabbEntity::getSize()
{
	return _size;
}

const string& AabbEntity::getParentID()
{
	return _parentID;
}

const AabbParentType AabbEntity::getParentType()
{
	return _parentType;
}

const Direction AabbEntity::getCollisionDirection()
{
	return _collisionDirection;
}

const bool AabbEntity::isRaycastResponsive()
{
	return _isRaycastResponsive;
}

const bool AabbEntity::isCollisionResponsive()
{
	return _isCollisionResponsive;
}

const bool AabbEntity::hasParent()
{
	return !_parentID.empty();
}

const bool AabbEntity::hasCollided()
{
	return _hasCollided;
}

const bool AabbEntity::hasRenderBuffer()
{
	return (_renderBuffer != nullptr);
}