#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "reflection_type.hpp"

#include <memory>

using std::shared_ptr;
using std::numeric_limits;

class ModelEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// VOID
	void createPart(const string& ID);
	void updateTransformation();
	void updateTransformationMatrix();
	void setShadowed(bool value);
	void setReflected(bool value);
	void setFrozen(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setLevelOfDetailSize(fvec3 value);
	void setLevelOfDetailEntityID(const string& value);
	void setMeshPath(const string& value);
	void setPreviousReflectionEntityID(const string& value);
	void setCurrentReflectionEntityID(const string& value);
	void setCubeReflectionMixValue(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setLevelOfDetailDistance(float value);
	void setBright(bool value);
	void clearParts();
	void setRenderBuffer(const string& partID, shared_ptr<RenderBuffer> value);
	void setDiffuseMap(const string& partID, TextureID value);
	void setEmissionMap(const string& partID, TextureID value);
	void setSpecularMap(const string& partID, TextureID value);
	void setReflectionMap(const string& partID, TextureID value);
	void setNormalMap(const string& partID, TextureID value);
	void setBasePosition(fvec3 value);
	void setBaseRotation(fvec3 value);
	void setBaseRotationOrigin(fvec3 value);
	void setBaseSize(fvec3 value);
	void setPartPosition(const string& partID, fvec3 value);
	void setPartRotation(const string& partID, fvec3 value);
	void setPartRotationOrigin(const string& partID, fvec3 value);
	void setPartSize(const string& partID, fvec3 value);
	void moveBase(fvec3 value);
	void rotateBase(fvec3 value);
	void scaleBase(fvec3 value);
	void movePart(const string& partID, fvec3 value);
	void rotatePart(const string& partID, fvec3 value);
	void scalePart(const string& partID, fvec3 value);
	void moveBaseTo(fvec3 target, float speed);
	void rotateBaseTo(fvec3 target, float speed);
	void scaleBaseTo(fvec3 target, float speed);
	void movePartTo(const string& partID, fvec3 target, float speed);
	void rotatePartTo(const string& partID, fvec3 target, float speed);
	void scalePartTo(const string& partID, fvec3 target, float speed);
	void setColor(const string& partID, fvec3 value);
	void setWireframeColor(const string& partID, fvec3 value);
	void setDiffuseMapPath(const string& partID, const string& value);
	void setEmissionMapPath(const string& partID, const string& value);
	void setSpecularMapPath(const string& partID, const string& value);
	void setReflectionMapPath(const string& partID, const string& value);
	void setNormalMapPath(const string& partID, const string& value);
	void setReflectivity(const string& partID, float value);
	void setLightness(const string& partID, float value);
	void setSpecularShininess(const string& partID, float value);
	void setSpecularIntensity(const string& partID, float value);
	void setTransparency(const string& partID, float value);
	void setTextureRepeat(const string& partID, float value);
	void setEmissionIntensity(const string& partID, float value);
	void setSpecular(const string& partID, bool value);
	void setReflective(const string& partID, bool value);
	void setReflectionType(const string& partID, ReflectionType value);
	void setWireframed(const string& partID, bool value);
	void setFaceCulled(bool value);
	void setRotationOrder(DirectionOrder value);

	// STRING
	const vector<string> getPartIDs() const;
	const string& getMeshPath() const;
	const string& getLevelOfDetailEntityID() const;
	const string& getPreviousReflectionEntityID() const;
	const string& getCurrentReflectionEntityID() const;
	const string& getDiffuseMapPath(const string& partID) const;
	const string& getEmissionMapPath(const string& partID) const;
	const string& getSpecularMapPath(const string& partID) const;
	const string& getReflectionMapPath(const string& partID) const;
	const string& getNormalMapPath(const string& partID) const;

	// MAT44
	const mat44& getTransformationMatrix(const string& partID) const;

	// FVEC3
	const fvec3 getColor(const string& partID) const;
	const fvec3 getWireframeColor(const string& partID) const;
	const fvec3 getLevelOfDetailSize() const;
	const fvec3 getBasePosition() const;
	const fvec3 getBaseRotation() const;
	const fvec3 getBaseRotationOrigin() const;
	const fvec3 getBaseSize() const;
	const fvec3 getPartPosition(const string& partID) const;
	const fvec3 getPartRotation(const string& partID) const;
	const fvec3 getPartRotationOrigin(const string& partID) const;
	const fvec3 getPartSize(const string& partID) const;

	// FLOAT
	const float getCubeReflectionMixValue() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const float getLevelOfDetailDistance() const;
	const float getReflectivity(const string& partID) const;
	const float getLightness(const string& partID) const;
	const float getSpecularShininess(const string& partID) const;
	const float getSpecularIntensity(const string& partID) const;
	const float getTransparency(const string& partID) const;
	const float getTextureRepeat(const string& partID) const;
	const float getEmissionIntensity(const string& partID) const;

	// BOOL
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isFrozen() const;
	const bool isDepthMapIncluded() const;
	const bool isLevelOfDetailed() const;
	const bool isBright() const;
	const bool isFaceCulled() const;
	const bool isWireframed(const string& partID) const;
	const bool isSpecular(const string& partID) const;
	const bool isReflective(const string& partID) const;
	const bool hasRenderBuffer(const string& partID) const;
	const bool hasDiffuseMap(const string& partID) const;
	const bool hasEmissionMap(const string& partID) const;
	const bool hasSpecularMap(const string& partID) const;
	const bool hasReflectionMap(const string& partID) const;
	const bool hasNormalMap(const string& partID) const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getRenderBuffer(const string& partID) const;
	const TextureID getDiffuseMap(const string& partID) const;
	const TextureID getEmissionMap(const string& partID) const;
	const TextureID getSpecularMap(const string& partID) const;
	const TextureID getReflectionMap(const string& partID) const;
	const TextureID getNormalMap(const string& partID) const;
	const ReflectionType getReflectionType(const string& partID) const;
	const DirectionOrder getRotationOrder() const;

private:
	struct PartData final
	{
		PartData(const string& ID)
			:
			ID(ID)
		{

		}

		// STRING
		const string ID;
		string diffuseMapPath = "";
		string emissionMapPath = "";
		string specularMapPath = "";
		string reflectionMapPath = "";
		string normalMapPath = "";

		// MAT44
		mat44 transformationMatrix = mat44(1.0f);

		// FVEC3
		fvec3 position = fvec3(0.0f);
		fvec3 rotation = fvec3(0.0f);
		fvec3 rotationOrigin = fvec3(0.0f);
		fvec3 size = fvec3(1.0f);
		fvec3 positionTarget = fvec3(0.0f);
		fvec3 rotationTarget = fvec3(0.0f);
		fvec3 sizeTarget = fvec3(1.0f);
		fvec3 color = fvec3(1.0f);
		fvec3 wireframeColor = fvec3(1.0f);

		// FLOAT
		float positionTargetSpeed = 0.0f;
		float rotationTargetSpeed = 0.0f;
		float sizeTargetSpeed = 0.0f;
		float reflectivity = 0.5f;
		float lightness = 1.0f;
		float specularShininess = 1.0f;
		float specularIntensity = 1.0f;
		float transparency = 1.0f;
		float emissionIntensity = 1.0f;
		float textureRepeat = 1.0f;

		// BOOL
		bool isSpecular = false;
		bool isReflective = false;
		bool isWireframed = false;

		// MISCELLANEOUS
		shared_ptr<RenderBuffer> renderBuffer = nullptr;
		TextureID diffuseMap = 0;
		TextureID emissionMap = 0;
		TextureID specularMap = 0;
		TextureID reflectionMap = 0;
		TextureID normalMap = 0;
		ReflectionType reflectionType = ReflectionType::CUBE;
	};

	// VOID
	void _correctPositionTarget(fvec3& current, fvec3 target, float speed);
	void _correctRotationTarget(fvec3& current, fvec3 target, float speed);
	void _correctSizeTarget(fvec3& current, fvec3 target, float speed);

	// UNSIGNED INT
	const unsigned int _getPartIndex(const string& partID) const;

	// STRING
	string _meshPath = "";
	string _levelOfDetailEntityID = "";
	string _previousReflectionEntityID = "";
	string _currentReflectionEntityID = "";

	// FVEC3
	fvec3 _basePosition = fvec3(0.0f);
	fvec3 _baseRotation = fvec3(0.0f);
	fvec3 _baseRotationOrigin = fvec3(0.0f);
	fvec3 _baseSize = fvec3(1.0f);
	fvec3 _basePositionTarget = fvec3(0.0f);
	fvec3 _baseRotationTarget = fvec3(0.0f);
	fvec3 _baseSizeTarget = fvec3(1.0f);
	fvec3 _levelOfDetailSize = fvec3(1.0f);

	// FLOAT
	float _basePositionTargetSpeed = 0.0f;
	float _baseRotationTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _cubeReflectionMixValue = 1.0f;
	float _levelOfDetailDistance = 0.0f;
	float _minHeight = numeric_limits<float>::lowest();
	float _maxHeight = numeric_limits<float>::max();

	// BOOL
	bool _isFrozen = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed = false;
	bool _isBright = false;
	bool _isFaceCulled = false;

	// MISCELLANEOUS
	vector<PartData> _parts;
	DirectionOrder _rotationOrder = DirectionOrder::YXZ;
};