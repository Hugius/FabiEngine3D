#pragma once

#include "base_entity.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"

class AabbEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~AabbEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(Vec3 value);
	void scale(Vec3 value);

	// Setters
	void setLocalTranslation(Vec3 value);
	void setLocalScaling(Vec3 value);
	void setTranslation(Vec3 value);
	void setScaling(Vec3 value);
	void swapScaling(Direction direction);
	void setParent(const string& ID, AabbParentType type);
	void setCollisionDirection(const Direction& direction);
	void setResponsive(bool value);

	// Getters
	const Matrix44 & getModelMatrix() const;
	const Vec3 getLocalTranslation() const;
	const Vec3 getLocalScaling() const;
	const Vec3 getTranslation() const;
	const Vec3 getScaling() const;
	const string& getParentID() const;
	const AabbParentType& getParentType() const;
	const Direction& getCollisionDirection() const;
	const bool isResponsive() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	Vec3 _localTranslation = Vec3(0.0f);
	Vec3 _localScaling = Vec3(1.0f);
	Vec3 _translation = Vec3(0.0f);
	Vec3 _scaling     = Vec3(1.0f);
	
	string _parentID = "";

	AabbParentType _parentType = AabbParentType::NONE;
	Direction _collisionDirection = Direction::NONE;
	Direction _swapScaling = Direction::NONE;

	bool _responsive = false;
};