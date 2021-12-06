#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "direction.hpp"
#include "aabb_parent_entity_type.hpp"

#include <memory>

using std::shared_ptr;

class AabbEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// VOID
	void updateTransformation();
	void updateTransformationMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setLocalPosition(fvec3 value);
	void setLocalSize(fvec3 value);
	void setPosition(fvec3 value);
	void setSize(fvec3 value);
	void move(fvec3 value);
	void scale(fvec3 value);
	void moveTo(fvec3 target, float speed);
	void scaleTo(fvec3 target, float speed);
	void setParentEntityID(const string& value);
	void setParentEntityType(AabbParentEntityType value);
	void setFollowParentEntityTransformation(bool value);
	void setFollowParentEntityVisibility(bool value);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	void setColor(fvec3 value);

	// STRING
	const string& getParentEntityID() const;

	// MAT44
	const mat44& getTransformationMatrix() const;

	// FVEC3
	const fvec3 getLocalPosition() const;
	const fvec3 getLocalSize() const;
	const fvec3 getPosition() const;
	const fvec3 getSize() const;
	const fvec3 getColor() const;

	// BOOL
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;
	const bool hasRenderBuffer() const;
	const bool mustFollowParentEntityTransformation() const;
	const bool mustFollowParentEntityVisibility() const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const AabbParentEntityType getParentEntityType() const;
	const Direction getCollisionDirection() const;

private:
	// STRING
	string _parentEntityID = "";

	// MAT44
	mat44 _transformationMatrix = mat44(1.0f);

	// FVEC3
	fvec3 _localPosition = fvec3(0.0f);
	fvec3 _localSize = fvec3(1.0f);
	fvec3 _position = fvec3(0.0f);
	fvec3 _size = fvec3(1.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _sizeTarget = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	// FLOAT
	float _positionTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;

	// BOOL
	bool _mustFollowParentEntityTransformation = true;
	bool _mustFollowParentEntityVisibility = true;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	// MISCELLANEOUS
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	AabbParentEntityType _parentEntityType;
	Direction _collisionDirection;
};