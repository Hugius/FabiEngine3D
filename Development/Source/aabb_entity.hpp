#pragma once

#include "base_entity.hpp"

#include <GLM\\glm.hpp>

using glm::vec3;
using glm::mat4;

enum class CollisionDir 
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
	void rotate(vec3 val);
	void scale(vec3 val);

	// Setters
	void setTranslation(vec3 val);
	void setRotation(vec3 val);
	void setScaling(vec3 val);
	void setParentID(const string& ID);
	void setCollisionDirection(const CollisionDir& direction);
	void setResponsiveness(bool val);

	// Getters
	const mat4 & getModelMatrix() const;
	const vec3 getTranslation() const;
	const vec3 getRotation() const;
	const vec3 getScaling() const;
	const string& getParentID() const;
	const CollisionDir& getCollisionDirection() const;
	const bool isResponsive() const;

private:
	mat4 _modelMatrix = mat4(1.0f);

	vec3 _translation = vec3(0.0f, 0.0f, 0.0f);
	vec3 _rotation    = vec3(0.0f, 0.0f, 0.0f);
	vec3 _scaling     = vec3(1.0f, 1.0f, 1.0f);
	
	string _parentID = "";

	CollisionDir _collisionDirection = CollisionDir::NONE;

	bool _responsive = false;
};