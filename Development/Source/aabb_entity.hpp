#pragma once

#include "base_entity.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"

class AabbEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Updates
	void updateModelMatrix();

	// Setters
	void setLocalPosition(Vec3 value);
	void setLocalSize(Vec3 value);
	void setPosition(Vec3 value);
	void setSize(Vec3 value);
	void move(Vec3 value);
	void scale(Vec3 value);
	void setParent(const string& ID, AabbParentType type);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);

	// Getters
	const Matrix44& getModelMatrix() const;
	const Vec3 getLocalPosition() const;
	const Vec3 getLocalSize() const;
	const Vec3 getPosition() const;
	const Vec3 getSize() const;
	const string& getParentID() const;
	const AabbParentType getParentType() const;
	const Direction getCollisionDirection() const;
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	Vec3 _localPosition = Vec3(0.0f);
	Vec3 _localSize = Vec3(1.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _size = Vec3(1.0f);
	
	string _parentID = "";

	AabbParentType _parentType;
	Direction _collisionDirection;

	bool _isRaycastResponsive = false;
	bool _isCollisionResponsive = false;
	bool _hasCollided = false;
};