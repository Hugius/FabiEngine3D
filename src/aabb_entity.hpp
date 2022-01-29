#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "direction.hpp"
#include "aabb_parent_entity_type.hpp"

#include <memory>

using std::shared_ptr;

class AabbEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setMesh(shared_ptr<VertexBuffer> value);
	void updateTransformation();
	void updateTransformationMatrix();
	void setLocalPosition(const fvec3& value);
	void setLocalSize(const fvec3& value);
	void setPosition(const fvec3& value);
	void setSize(const fvec3& value);
	void move(const fvec3& value);
	void scale(const fvec3& value);
	void moveTo(const fvec3& target, float speed);
	void scaleTo(const fvec3& target, float speed);
	void setParentEntityId(const string& value);
	void setParentEntityType(AabbParentEntityType value);
	void setCollisionDirection(Direction value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setCollided(bool value);
	void setColor(const fvec3& value);
	void setCentered(bool value);

	const string& getParentEntityId() const;

	const mat44& getTransformationMatrix() const;

	const fvec3& getLocalPosition() const;
	const fvec3& getLocalSize() const;
	const fvec3& getPosition() const;
	const fvec3& getSize() const;
	const fvec3& getColor() const;

	const bool isCentered() const;
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;
	const bool hasParent() const;
	const bool hasCollided() const;

	const shared_ptr<VertexBuffer> getMesh() const;
	const AabbParentEntityType getParentEntityType() const;
	const Direction getCollisionDirection() const;

private:
	string _parentEntityId = "";

	mat44 _transformationMatrix = mat44(1.0f);

	fvec3 _localPosition = fvec3(0.0f);
	fvec3 _localSize = fvec3(1.0f);
	fvec3 _position = fvec3(0.0f);
	fvec3 _size = fvec3(1.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _sizeTarget = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	float _positionTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;

	bool _isCentered = false;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _hasCollided = false;

	shared_ptr<VertexBuffer> _mesh = nullptr;
	AabbParentEntityType _parentEntityType = AabbParentEntityType::MODEL;
	Direction _collisionDirection = Direction::X;
};