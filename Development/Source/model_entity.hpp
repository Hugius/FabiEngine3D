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

	// Voids
	void createPart(const string& ID);
	void updateTransformation();
	void updateTransformationMatrix();
	void setShadowed(bool value);
	void setReflected(bool value);
	void setCameraStatic(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setLevelOfDetailSize(Vec3 value);
	void setLevelOfDetailEntityID(const string& value);
	void setMeshPath(const string& value);
	void setPreviousReflectionEntityID(const string& value);
	void setCurrentReflectionEntityID(const string& value);
	void setCubeReflectionMixValue(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setBright(bool value);
	void clearParts();
	void setRenderBuffer(const string& partID, shared_ptr<RenderBuffer> value);
	void setDiffuseMap(const string& partID, TextureID value);
	void setEmissionMap(const string& partID, TextureID value);
	void setSpecularMap(const string& partID, TextureID value);
	void setReflectionMap(const string& partID, TextureID value);
	void setNormalMap(const string& partID, TextureID value);
	void setBasePosition(Vec3 value);
	void setBaseRotation(Vec3 value);
	void setBaseRotationOrigin(Vec3 value);
	void setBaseSize(Vec3 value);
	void setPartPosition(const string& partID, Vec3 value);
	void setPartRotation(const string& partID, Vec3 value);
	void setPartRotationOrigin(const string& partID, Vec3 value);
	void setPartSize(const string& partID, Vec3 value);
	void moveBase(Vec3 value);
	void rotateBase(Vec3 value);
	void scaleBase(Vec3 value);
	void movePart(const string& partID, Vec3 value);
	void rotatePart(const string& partID, Vec3 value);
	void scalePart(const string& partID, Vec3 value);
	void moveBaseTo(Vec3 target, float speed);
	void rotateBaseTo(Vec3 target, float speed);
	void scaleBaseTo(Vec3 target, float speed);
	void movePartTo(const string& partID, Vec3 target, float speed);
	void rotatePartTo(const string& partID, Vec3 target, float speed);
	void scalePartTo(const string& partID, Vec3 target, float speed);
	void setColor(const string& partID, Vec3 value);
	void setColorInversion(const string& partID, float value);
	void setDiffuseMapPath(const string& partID, const string& value);
	void setEmissionMapPath(const string& partID, const string& value);
	void setSpecularMapPath(const string& partID, const string& value);
	void setReflectionMapPath(const string& partID, const string& value);
	void setNormalMapPath(const string& partID, const string& value);
	void setReflectivity(const string& partID, float value);
	void setLightness(const string& partID, float value);
	void setSpecularShininess(const string& partID, float value);
	void setSpecularIntensity(const string& partID, float value);
	void setAlpha(const string& partID, float value);
	void setTextureRepeat(const string& partID, float value);
	void setEmissionIntensity(const string& partID, float value);
	void setSpecular(const string& partID, bool value);
	void setReflective(const string& partID, bool value);
	void setReflectionType(const string& partID, ReflectionType value);
	void setWireFramed(bool value);
	void setFaceCulled(bool value);
	void setRotationOrder(DirectionOrder order);

	// Instances
	const shared_ptr<RenderBuffer> getRenderBuffer(const string& partID);

	// Strings
	const vector<string> getPartIDs();
	const string& getMeshPath();
	const string& getLevelOfDetailEntityID();
	const string& getPreviousReflectionEntityID();
	const string& getCurrentReflectionEntityID();
	const string& getDiffuseMapPath(const string& partID);
	const string& getEmissionMapPath(const string& partID);
	const string& getSpecularMapPath(const string& partID);
	const string& getReflectionMapPath(const string& partID);
	const string& getNormalMapPath(const string& partID);

	// Matrices
	const Matrix44& getTransformationMatrix(const string& partID);

	// Vectors
	const Vec3 getColor(const string& partID);
	const Vec3 getLevelOfDetailSize();
	const Vec3 getBasePosition();
	const Vec3 getBaseRotation();
	const Vec3 getBaseRotationOrigin();
	const Vec3 getBaseSize();
	const Vec3 getPartPosition(const string& partID);
	const Vec3 getPartRotation(const string& partID);
	const Vec3 getPartRotationOrigin(const string& partID);
	const Vec3 getPartSize(const string& partID);

	// Floats
	const float getCubeReflectionMixValue();
	const float getMinHeight();
	const float getMaxHeight();
	const float getColorInversion(const string& partID);
	const float getReflectivity(const string& partID);
	const float getLightness(const string& partID);
	const float getSpecularShininess(const string& partID);
	const float getSpecularIntensity(const string& partID);
	const float getAlpha(const string& partID);
	const float getTextureRepeat(const string& partID);
	const float getEmissionIntensity(const string& partID);

	// Booleans
	const bool isShadowed();
	const bool isReflected();
	const bool isCameraStatic();
	const bool isDepthMapIncluded();
	const bool isLevelOfDetailed();
	const bool isBright();
	const bool isWireFramed();
	const bool isFaceCulled();
	const bool isSpecular(const string& partID);
	const bool isReflective(const string& partID);
	const bool hasRenderBuffer(const string& partID);
	const bool hasDiffuseMap(const string& partID);
	const bool hasEmissionMap(const string& partID);
	const bool hasSpecularMap(const string& partID);
	const bool hasReflectionMap(const string& partID);
	const bool hasNormalMap(const string& partID);

	// Miscellaneous
	const TextureID getDiffuseMap(const string& partID);
	const TextureID getEmissionMap(const string& partID);
	const TextureID getSpecularMap(const string& partID);
	const TextureID getReflectionMap(const string& partID);
	const TextureID getNormalMap(const string& partID);
	const ReflectionType getReflectionType(const string& partID);
	const DirectionOrder getRotationOrder();

private:
	struct PartData final
	{
		PartData(const string& ID)
			:
			ID(ID)
		{

		}

		// Instances
		shared_ptr<RenderBuffer> renderBuffer = nullptr;

		// Strings
		const string ID;
		string diffuseMapPath = "";
		string emissionMapPath = "";
		string specularMapPath = "";
		string reflectionMapPath = "";
		string normalMapPath = "";

		// Matrices
		Matrix44 transformationMatrix = Matrix44(1.0f);

		// Vectors
		Vec3 position = Vec3(0.0f);
		Vec3 rotation = Vec3(0.0f);
		Vec3 rotationOrigin = Vec3(0.0f);
		Vec3 size = Vec3(1.0f);
		Vec3 positionTarget = Vec3(0.0f);
		Vec3 rotationTarget = Vec3(0.0f);
		Vec3 sizeTarget = Vec3(1.0f);
		Vec3 color = Vec3(1.0f);

		// Floats
		float positionTargetSpeed = 0.0f;
		float rotationTargetSpeed = 0.0f;
		float sizeTargetSpeed = 0.0f;
		float colorInversion = 0.0f;
		float reflectivity = 0.5f;
		float lightness = 1.0f;
		float specularShininess = 1.0f;
		float specularIntensity = 1.0f;
		float alpha = 1.0f;
		float emissionIntensity = 1.0f;
		float textureRepeat = 1.0f;

		// Booleans
		bool isSpecular = false;
		bool isReflective = false;

		// Miscellaneous
		TextureID diffuseMap = 0;
		TextureID emissionMap = 0;
		TextureID specularMap = 0;
		TextureID reflectionMap = 0;
		TextureID normalMap = 0;
		ReflectionType reflectionType = ReflectionType::CUBE;
	};

	// Voids
	void _correctPositionTarget(Vec3& current, Vec3 target, float speed);
	void _correctRotationTarget(Vec3& current, Vec3 target, float speed);
	void _correctSizeTarget(Vec3& current, Vec3 target, float speed);

	// Integers
	unsigned int _getPartIndex(const string& partID);

	// Instances
	vector<PartData> _parts;

	// Strings
	string _meshPath = "";
	string _levelOfDetailEntityID = "";
	string _previousReflectionEntityID = "";
	string _currentReflectionEntityID = "";

	// Vectors
	Vec3 _basePosition = Vec3(0.0f);
	Vec3 _baseRotation = Vec3(0.0f);
	Vec3 _baseRotationOrigin = Vec3(0.0f);
	Vec3 _baseSize = Vec3(1.0f);
	Vec3 _basePositionTarget = Vec3(0.0f);
	Vec3 _baseRotationTarget = Vec3(0.0f);
	Vec3 _baseSizeTarget = Vec3(1.0f);
	Vec3 _levelOfDetailSize = Vec3(1.0f);

	// Floats
	float _basePositionTargetSpeed = 0.0f;
	float _baseRotationTargetSpeed = 0.0f;
	float _baseSizeTargetSpeed = 0.0f;
	float _cubeReflectionMixValue = 1.0f;
	float _minHeight = -(numeric_limits<float>::max)();
	float _maxHeight = (numeric_limits<float>::max)();

	// Booleans
	bool _isCameraStatic = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed = false;
	bool _isBright = false;
	bool _isWireFramed = false;
	bool _isFaceCulled = false;

	// Miscellaneous
	DirectionOrder _rotationOrder = DirectionOrder::YXZ;
};