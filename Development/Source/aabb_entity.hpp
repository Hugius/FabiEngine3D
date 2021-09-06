#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"

#include <memory>

using std::shared_ptr;

class AabbEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void updateTransformationMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setLocalPosition(Vec3 value);
	void setLocalSize(Vec3 value);
	void setPosition(Vec3 value);
	void setSize(Vec3 value);
	void move(Vec3 value);
	void scale(Vec3 value);
	void moveTo(Vec3 target, float speed);
	void scaleTo(Vec3 target, float speed);
	void setParent(const string& ID, AabbParentType value);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	
	// Strings
	const string& getParentID();

	// Matrices
	const Matrix44& getTransformationMatrix();

	// Vectors
	const Vec3 getLocalPosition();
	const Vec3 getLocalSize();
	const Vec3 getPosition();
	const Vec3 getSize();

	// Booleans
	const bool isRaycastResponsive();
	const bool isCollisionResponsive();
	const bool hasParent();
	const bool hasCollided();
	const bool hasRenderBuffer();

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer();
	const AabbParentType getParentType();
	const Direction getCollisionDirection();

private:
	// Instances
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;

	// Strings
	string _parentID = "";

	// Matrices
	Matrix44 _transformationMatrix = Matrix44(1.0f);

	// Vectors
	Vec3 _localPosition = Vec3(0.0f);
	Vec3 _localSize = Vec3(1.0f);
	Vec3 _position = Vec3(0.0f);
	Vec3 _size = Vec3(1.0f);
	Vec3 _positionTarget = Vec3(0.0f);
	Vec3 _sizeTarget = Vec3(1.0f);

	// Floats
	float _positionTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;

	// Booleans
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	// Miscellaneous
	AabbParentType _parentType;
	Direction _collisionDirection;
};