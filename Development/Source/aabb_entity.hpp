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
	void translate(vec3 val);
	void scale(vec3 val);

	// Setters
	void setLocalTranslation(vec3 val);
	void setLocalScaling(vec3 val);
	void setTranslation(vec3 val);
	void setScaling(vec3 val);
	void setParent(const string& ID, AabbParentType type);
	void setCollisionDirection(const Direction& direction);
	void setResponsiveness(bool val);

	// Getters
	const mat4 & getModelMatrix() const;
	const vec3 getLocalTranslation() const;
	const vec3 getLocalScaling() const;
	const vec3 getTranslation() const;
	const vec3 getScaling() const;
	const string& getParentID() const;
	const AabbParentType& getParentType() const;
	const Direction& getCollisionDirection() const;
	const bool isResponsive() const;

private:
	mat4 _modelMatrix = mat4(1.0f);

	vec3 _localTranslation = vec3(0.0f);
	vec3 _localScaling = vec3(1.0f);
	vec3 _translation = vec3(0.0f);
	vec3 _scaling     = vec3(1.0f);
	
	string _parentID = "";

	AabbParentType _parentType = AabbParentType::NONE;
	Direction _collisionDirection = Direction::NONE;

	bool _responsive = false;
};