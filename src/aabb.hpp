#pragma once

#include "vertex_buffer.hpp"
#include "direction_type.hpp"
#include "aabb_parent_type.hpp"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Aabb final
{
public:
	Aabb(const string & id);

	void updateTarget();
	void updateTransformation();
	void followModelParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize);
	void followModelParentVisibility(bool isParentVisible, const string & parentLevelOfDetailId, bool isParentLevelOfDetailed);
	void followQuad3dParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize);
	void followQuad3dParentVisibility(bool isParentVisible);
	void followText3dParentTransformation(const fvec3 & parentPosition, const fvec3 & parentRotation, const fvec3 & parentSize);
	void followText3dParentVisibility(bool isParentVisible);
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setLocalPosition(const fvec3 & value);
	void setLocalSize(const fvec3 & value);
	void setBasePosition(const fvec3 & value);
	void setBaseSize(const fvec3 & value);
	void moveBase(const fvec3 & value);
	void scaleBase(const fvec3 & value);
	void moveBaseTo(const fvec3 & target, float speed);
	void scaleBaseTo(const fvec3 & target, float speed);
	void moveLocal(const fvec3 & value);
	void scaleLocal(const fvec3 & value);
	void moveLocalTo(const fvec3 & target, float speed);
	void scaleLocalTo(const fvec3 & target, float speed);
	void setParentId(const string & value);
	void setParentType(AabbParentType value);
	void setRaycastResponsive(bool value);
	void setCollisionResponsive(bool value);
	void setColor(const fvec3 & value);
	void setCentered(bool value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setVisible(bool value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;

	const string & getId() const;
	const string & getParentId() const;

	const fmat44 & getTransformation() const;

	const fvec3 & getLocalPosition() const;
	const fvec3 & getLocalSize() const;
	const fvec3 & getBasePosition() const;
	const fvec3 & getBaseSize() const;
	const fvec3 & getColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const bool isVisible() const;
	const bool isCentered() const;
	const bool isRaycastResponsive() const;
	const bool isCollisionResponsive() const;

	const AabbParentType getParentType() const;

private:
	static inline constexpr float MIN_SIZE = 0.1f;

	const string _id;

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;

	string _parentId = "";

	fmat44 _transformation = fmat44(1.0f);

	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _localPosition = fvec3(0.0f);
	fvec3 _localSize = fvec3(1.0f);
	fvec3 _localPositionTarget = fvec3(0.0f);
	fvec3 _localSizeTarget = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	float _basePositionTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _localPositionTargetSpeed = 0.0f;
	float _localSizeTargetSpeed = 0.0f;

	bool _isCentered = false;
	bool _isRaycastResponsive = true;
	bool _isCollisionResponsive = true;
	bool _isVisible = true;

	AabbParentType _parentType = {};
};