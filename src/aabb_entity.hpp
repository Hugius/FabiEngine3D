#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "direction.hpp"
#include "aabb_parent_type.hpp"

#include <memory>

using std::shared_ptr;

class AabbEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setMesh(shared_ptr<VertexBuffer> value);
	void updateTarget();
	void updateTransformation();
	void setLocalPosition(const fvec3& value);
	void setLocalSize(const fvec3& value);
	void setBasePosition(const fvec3& value);
	void setBaseSize(const fvec3& value);
	void moveBase(const fvec3& value);
	void scaleBase(const fvec3& value);
	void moveBaseTo(const fvec3& target, float speed);
	void scaleBaseTo(const fvec3& target, float speed);
	void setParentId(const string& value);
	void setParentType(AabbParentType value);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	void setColor(const fvec3& value);
	void setCentered(bool value);

	const string& getParentId() const;

	const mat44& getTransformation() const;

	const fvec3& getLocalPosition() const;
	const fvec3& getLocalSize() const;
	const fvec3& getBasePosition() const;
	const fvec3& getBaseSize() const;
	const fvec3& getColor() const;

	const bool isCentered() const;
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;

	const shared_ptr<VertexBuffer> getMesh() const;
	const AabbParentType getParentType() const;
	const Direction getCollisionDirection() const;

private:
	string _parentId = "";

	mat44 _transformation = mat44(1.0f);

	fvec3 _localPosition = fvec3(0.0f);
	fvec3 _localSize = fvec3(1.0f);
	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	float _basePositionTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;

	bool _isCentered = false;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	shared_ptr<VertexBuffer> _mesh = nullptr;
	AabbParentType _parentType = AabbParentType::MODEL;
	Direction _collisionDirection = Direction::X;
};