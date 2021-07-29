#pragma once

#include "base_entity.hpp"
#include "reflection_type.hpp"

class ModelEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	
	// Setters
	void addPart(const string& ID);
	void updateModelMatrix();
	void setDiffuseMap(GLuint value, const string& partID = "");
	void setEmissionMap(GLuint value, const string& partID = "");
	void setReflectionMap(GLuint value, const string& partID = "");
	void setNormalMap(GLuint value, const string& partID = "");
	void setPosition(Vec3 value, const string& partID = "");
	void setRotation(Vec3 value, const string& partID = "");
	void setRotationOrigin(Vec3 value, const string& partID = "");
	void setSize(Vec3 value, const string& partID = "");
	void setColor(Vec3 value, const string& partID = "");
	void setLevelOfDetailSize(Vec3 value);
	void setInversion(float value, const string& partID = "");
	void setMeshPath(const string& value);
	void setDiffuseMapPath(const string& value, const string& partID = "");
	void setEmissionMapPath(const string& value, const string& partID = "");
	void setReflectionMapPath(const string& value, const string& partID = "");
	void setNormalMapPath(const string& value, const string& partID = "");
	void setLodEntityID(const string& value);
	void setLightness(float value);
	void setSpecularFactor(float value);
	void setSpecularIntensity(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setAlpha(float value);
	void setUvRepeat(float value);
	void setTransparent(bool value);
	void setFaceCulled(bool value);
	void setSpecularLighted(bool value);
	void setShadowed(bool value);
	void setReflected(bool value);
	void setCameraStatic(bool value);
	void setDepthMapIncluded(bool value);
	void setLevelOfDetailed(bool value);
	void setWireframed(bool value);
	void setBright(bool value);
	void setReflectionType(ReflectionType value);
	void clearParts();
	
	// Getters
	const Matrix44& getModelMatrix(const string& partID = "");
	const GLuint getDiffuseMap(const string& partID = "");
	const GLuint getEmissionMap(const string& partID = "");
	const GLuint getReflectionMap(const string& partID = "");
	const GLuint getNormalMap(const string& partID = "");
	const Vec3 getPosition(const string& partID = "");
	const Vec3 getRotation(const string& partID = "");
	const Vec3 getRotationOrigin(const string& partID = "");
	const Vec3 getSize(const string& partID = "");
	const Vec3 getLevelOfDetailSize();
	const Vec3 getColor(const string& partID = "");
	const float getInversion(const string& partID = "");
	const vector<string> getPartIDs();
	const string& getMeshPath();
	const string& getDiffuseMapPath(const string& partID = "");
	const string& getEmissionMapPath(const string& partID = "");
	const string& getReflectionMapPath(const string& partID = "");
	const string& getNormalMapPath(const string& partID = "");
	const string& getLodEntityID();
	const float getLightness();
	const float getSpecularFactor();
	const float getSpecularIntensity();
	const float getAlpha();
	const float getUvRepeat();
	const float getMinHeight();
	const float getMaxHeight();
	const bool isTransparent();
	const bool isFaceCulled();
	const bool isSpecularLighted();
	const bool isShadowed();
	const bool isReflected();
	const bool isCameraStatic();
	const bool isDepthMapIncluded();
	const bool isLevelOfDetailed();
	const bool isWireframed();
	const bool isBright();
	const bool hasDiffuseMap(const string& partID = "");
	const bool hasEmissionMap(const string& partID = "");
	const bool hasReflectionMap(const string& partID = "");
	const bool hasNormalMap(const string& partID = "");
	const ReflectionType getReflectionType();

private:
	struct PartData final
	{
		PartData(const string& ID) :
			ID(ID)
		{

		}

		const string ID;
		string diffuseMapPath = "";
		string emissionMapPath = "";
		string reflectionMapPath = "";
		string normalMapPath = "";

		Matrix44 modelMatrix = Matrix44(1.0f);

		Vec3 localPosition = Vec3(0.0f);
		Vec3 localRotation = Vec3(0.0f);
		Vec3 localRotationOrigin = Vec3(0.0f);
		Vec3 localSize = Vec3(1.0f);
		Vec3 color = Vec3(1.0f);

		float inversion = 0.0f;

		GLuint diffuseMap = 0;
		GLuint emissionMap = 0;
		GLuint reflectionMap = 0;
		GLuint normalMap = 0;
	};

	unsigned int _getPartIndex(string partID);

	vector<PartData> _parts;

	string _meshPath = "";
	string _lodEntityID = "";

	Vec3 _basePosition = Vec3(0.0f);
	Vec3 _baseRotation = Vec3(0.0f);
	Vec3 _baseRotationOrigin = Vec3(0.0f);
	Vec3 _baseSize = Vec3(1.0f);
	Vec3 _levelOfDetailSize = Vec3(1.0f);

	float _lightness = 1.0f;
	float _specularFactor = 1.0f;
	float _specularIntensity = 1.0f;
	float _alpha = 1.0f;
	float _uvRepeat = 1.0f;
	float _minHeight = -(std::numeric_limits<float>::max)();
	float _maxHeight = (std::numeric_limits<float>::max)();

	bool _isCameraStatic	 = false;
	bool _isTransparent      = false;
	bool _isFaceCulled       = false;
	bool _isSpecularLighted  = false;
	bool _isShadowed         = true;
	bool _isReflected		 = true;
	bool _isDepthMapIncluded = true;
	bool _isLevelOfDetailed  = false;
	bool _wireframed		 = false;
	bool _isBright			 = false;

	ReflectionType _reflectionType;
};