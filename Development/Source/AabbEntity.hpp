#pragma once

#include <GLM/glm.hpp>

using glm::vec3;
using glm::mat4;

#include "Entity.hpp"

enum class CollisionDir 
{ 
	NONE, 
	X, 
	Y, 
	Z 
};

class AabbEntity final: public Entity
{
public:
	AabbEntity()  = default;
	~AabbEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(vec3 val, float delta);
	void rotate(vec3 val, float delta);
	void scale(vec3 val, float delta);

	// Setters
	void setTranslation(vec3 val);
	void setRotation(vec3 val);
	void setScaling(vec3 val);
	void setParentID(const string & ID);
	void setCollisionDirection(const CollisionDir& direction);
	void setResponsiveness(bool val);

	// Getters
	const mat4 & getModelMatrix() const;
	const vec3 getTranslation() const;
	const vec3 getRotation() const;
	const vec3 getScaling() const;
	const string & getParentID() const;
	const CollisionDir& getCollisionDirection() const;
	const bool isResponsive() const;

private:
	mat4 p_modelMatrix = mat4(1.0f);

	vec3 p_translation = vec3(0.0f, 0.0f, 0.0f);
	vec3 p_rotation    = vec3(0.0f, 0.0f, 0.0f);
	vec3 p_scaling     = vec3(1.0f, 1.0f, 1.0f);
	
	string p_parentID = "";

	CollisionDir p_collisionDirection = CollisionDir::NONE;

	bool p_responsive = false;
};