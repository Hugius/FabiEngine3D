#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"

#include <memory>

using std::shared_ptr;

class AabbEntity final : public BaseEntity
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
	void setParent(const string& parentID, AabbParentType parentType);
	void setFollowParentTransformation(bool mustFollow);
	void setFollowParentVisibility(bool mustFollow);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	void setColor(Vec3 value);

	// Strings
	const string& getParentID() const;

	// Matrices
	const Matrix44& getTransformationMatrix() const;

	// Vectors
	const Vec3 getLocalPosition() const;
	const Vec3 getLocalSize() const;
	const Vec3 getPosition() const;
	const Vec3 getSize() const;
	const Vec3 getColor() const;

	// Booleans
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;
	const bool hasRenderBuffer() const;
	const bool mustFollowParentTransformation() const;
	const bool mustFollowParentVisibility() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const AabbParentType getParentType() const;
	const Direction getCollisionDirection() const;

private:
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
	Vec3 _color = Vec3(1.0f);

	// Decimals
	float _positionTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;

	// Booleans
	bool _mustFollowParentTransformation = true;
	bool _mustFollowParentVisibility = true;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	AabbParentType _parentType;
	Direction _collisionDirection;
};