#pragma once

#include "base_entity.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

enum class AabbParentType
{
	NONE,
	GAME_ENTITY,
	BILLBOARD_ENTITY
};

enum class CollisionDirection 
{
	NONE, 
	X, 
	Y, 
	Z 
};

class AabbEntity final: public BaseEntity
{
public:
	AabbEntity()  = default;
	~AabbEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(vec3 val);
	void scale(vec3 val);

	// Setters
	void setOriginalTranslation(vec3 val);
	void setOriginalScaling(vec3 val);
	void setTranslation(vec3 val);
	void setScaling(vec3 val);
	void setParent(const string& ID, AabbParentType type);
	void setCollisionDirection(const CollisionDirection& direction);
	void setResponsiveness(bool val);

	// Getters
	const mat4 & getModelMatrix() const;
	const vec3 getOriginalTranslation() const;
	const vec3 getOriginalScaling() const;
	const vec3 getTranslation() const;
	const vec3 getScaling() const;
	const string& getParentID() const;
	const AabbParentType& getParentType() const;
	const CollisionDirection& getCollisionDirection() const;
	const bool isResponsive() const;

private:
	mat4 _modelMatrix = mat4(1.0f);

	vec3 _originalTranslation = vec3(0.0f);
	vec3 _originalScaling	  = vec3(0.0f);
	vec3 _translation = vec3(0.0f, 0.0f, 0.0f);
	vec3 _scaling     = vec3(1.0f, 1.0f, 1.0f);
	
	string _parentID = "";

	AabbParentType _parentType = AabbParentType::NONE;
	CollisionDirection _collisionDirection = CollisionDirection::NONE;

	bool _responsive = false;
};