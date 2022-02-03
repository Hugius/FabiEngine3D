#pragma once

#include "model_entity_part.hpp"

class ModelEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void createPart(const string& id);
	void deleteParts();
	void updateTarget();
	void updateTransformation();
	void setShadowed(bool value);
	void setReflected(bool value);
	void setFrozen(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setLevelOfDetailSize(const fvec3& value);
	void setLevelOfDetailEntityId(const string& value);
	void setPreviousReflectionEntityId(const string& value);
	void setCurrentReflectionEntityId(const string& value);
	void setCubeReflectionMixValue(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setLevelOfDetailDistance(float value);
	void setBright(const string& partId, bool value);
	void setMesh(const string& partId, shared_ptr<VertexBuffer> value);
	void setDiffuseMap(const string& partId, shared_ptr<TextureBuffer> value);
	void setEmissionMap(const string& partId, shared_ptr<TextureBuffer> value);
	void setSpecularMap(const string& partId, shared_ptr<TextureBuffer> value);
	void setReflectionMap(const string& partId, shared_ptr<TextureBuffer> value);
	void setNormalMap(const string& partId, shared_ptr<TextureBuffer> value);
	void setBasePosition(const fvec3& value);
	void setBaseRotation(const fvec3& value);
	void setBaseRotationOrigin(const fvec3& value);
	void setBaseSize(const fvec3& value);
	void setPartPosition(const string& partId, const fvec3& value);
	void setPartRotation(const string& partId, const fvec3& value);
	void setPartRotationOrigin(const string& partId, const fvec3& value);
	void setPartSize(const string& partId, const fvec3& value);
	void moveBase(const fvec3& value);
	void rotateBase(const fvec3& value);
	void scaleBase(const fvec3& value);
	void movePart(const string& partId, const fvec3& value);
	void rotatePart(const string& partId, const fvec3& value);
	void scalePart(const string& partId, const fvec3& value);
	void moveBaseTo(const fvec3& target, float speed);
	void rotateBaseTo(const fvec3& target, float speed);
	void scaleBaseTo(const fvec3& target, float speed);
	void movePartTo(const string& partId, const fvec3& target, float speed);
	void rotatePartTo(const string& partId, const fvec3& target, float speed);
	void scalePartTo(const string& partId, const fvec3& target, float speed);
	void setColor(const string& partId, const fvec3& value);
	void setWireframeColor(const string& partId, const fvec3& value);
	void setMeshPath(const string& value);
	void setDiffuseMapPath(const string& partId, const string& value);
	void setEmissionMapPath(const string& partId, const string& value);
	void setSpecularMapPath(const string& partId, const string& value);
	void setReflectionMapPath(const string& partId, const string& value);
	void setNormalMapPath(const string& partId, const string& value);
	void setReflectivity(const string& partId, float value);
	void setLightness(const string& partId, float value);
	void setSpecularShininess(const string& partId, float value);
	void setSpecularIntensity(const string& partId, float value);
	void setOpacity(const string& partId, float value);
	void setTextureRepeat(const string& partId, float value);
	void setEmissionIntensity(const string& partId, float value);
	void setSpecular(const string& partId, bool value);
	void setReflective(const string& partId, bool value);
	void setReflectionType(const string& partId, ReflectionType value);
	void setWireframed(const string& partId, bool value);
	void setFaceCulled(const string& partId, bool value);
	void setRotationOrder(DirectionOrder value);
	void setMinTextureAlpha(const string& partId, float value);

	const vector<string> getPartIds() const;
	const string& getMeshPath() const;
	const string& getLevelOfDetailEntityId() const;
	const string& getPreviousReflectionEntityId() const;
	const string& getCurrentReflectionEntityId() const;
	const string& getDiffuseMapPath(const string& partId) const;
	const string& getEmissionMapPath(const string& partId) const;
	const string& getSpecularMapPath(const string& partId) const;
	const string& getReflectionMapPath(const string& partId) const;
	const string& getNormalMapPath(const string& partId) const;

	const mat44& getTransformation(const string& partId) const;

	const fvec3& getColor(const string& partId) const;
	const fvec3& getWireframeColor(const string& partId) const;
	const fvec3& getLevelOfDetailSize() const;
	const fvec3& getBasePosition() const;
	const fvec3& getBaseRotation() const;
	const fvec3& getBaseRotationOrigin() const;
	const fvec3& getBaseSize() const;
	const fvec3& getPartPosition(const string& partId) const;
	const fvec3& getPartRotation(const string& partId) const;
	const fvec3& getPartRotationOrigin(const string& partId) const;
	const fvec3& getPartSize(const string& partId) const;

	const float getCubeReflectionMixValue() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const float getLevelOfDetailDistance() const;
	const float getReflectivity(const string& partId) const;
	const float getLightness(const string& partId) const;
	const float getSpecularShininess(const string& partId) const;
	const float getSpecularIntensity(const string& partId) const;
	const float getOpacity(const string& partId) const;
	const float getTextureRepeat(const string& partId) const;
	const float getEmissionIntensity(const string& partId) const;
	const float getMinTextureAlpha(const string& partId) const;

	const bool isFrozen() const;
	const bool isDepthMapIncluded() const;
	const bool isLevelOfDetailed() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isBright(const string& partId) const;
	const bool isFaceCulled(const string& partId) const;
	const bool isWireframed(const string& partId) const;
	const bool isSpecular(const string& partId) const;
	const bool isReflective(const string& partId) const;

	const shared_ptr<VertexBuffer> getMesh(const string& partId) const;
	const shared_ptr<TextureBuffer> getDiffuseMap(const string& partId) const;
	const shared_ptr<TextureBuffer> getEmissionMap(const string& partId) const;
	const shared_ptr<TextureBuffer> getSpecularMap(const string& partId) const;
	const shared_ptr<TextureBuffer> getReflectionMap(const string& partId) const;
	const shared_ptr<TextureBuffer> getNormalMap(const string& partId) const;
	const ReflectionType getReflectionType(const string& partId) const;
	const DirectionOrder getRotationOrder() const;

private:
	void _correctPositionTarget(fvec3& current, const fvec3& target, float speed);
	void _correctRotationTarget(fvec3& current, const fvec3& target, float speed);
	void _correctSizeTarget(fvec3& current, const fvec3& target, float speed);

	const unsigned int _getPartIndex(const string& partId) const;

	string _meshPath = "";
	string _levelOfDetailEntityId = "";
	string _previousReflectionEntityId = "";
	string _currentReflectionEntityId = "";

	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseRotation = fvec3(0.0f);
	fvec3 _baseRotationOrigin = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseRotationTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _levelOfDetailSize = fvec3(1.0f);

	float _basePositionTargetSpeed = 0.0f;
	float _baseRotationTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _cubeReflectionMixValue = 1.0f;
	float _levelOfDetailDistance = 0.0f;
	float _minHeight = -FLT_MAX;
	float _maxHeight = FLT_MAX;

	bool _isFrozen = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed = false;

	vector<ModelEntityPart> _parts;
	DirectionOrder _rotationOrder = DirectionOrder::YXZ;
};