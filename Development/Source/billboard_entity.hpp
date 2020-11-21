#pragma once

#include "base_entity.hpp"

#include "mathematics.hpp"
#include <GLM\\gtc\\matrix_transform.hpp>

using glm::ivec2;


class BillboardEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~BillboardEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(Vec3 val);
	void rotate(Vec3 val);
	void scale(Vec3 val);

	// Setters
	void setCameraFacingX(bool val);
	void setCameraFacingY(bool val);
	void setTransparent(bool val);
	void setDepthMapIncluded(bool val);
	void setDiffuseMap(GLuint val);
	void setTranslation(Vec3 val);
	void setInitialRotation(Vec3 val);
	void setRotation(Vec3 val);
	void setScaling(Vec3 val);
	void setColor(Vec3 color);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);
	void setDiffuseMapPath(const string& diffuseMapPath);
	void playSpriteAnimation(int maxAnimationRepeats);
	void stopSpriteAnimation();
	void setSpriteRowIndex(int val);
	void setSpriteColumnIndex(int val);
	void setTotalSpriteRows(int val);
	void setTotalSpriteColumns(int val);
	void setMaxFramestep(int val);
	void increasePassedFrames();
	void resetPassedFrames();
	void increaseAnimationRepeats();
	void setOriginalLightness(float val);
	void setLightness(float val);
	void setMaxY(float val);

	// Getters
	const Matrix44 & getModelMatrix() const;
	const GLuint getDiffuseMap() const;
	const Vec3 getTranslation() const;
	const Vec3 getInitialRotation() const;
	const Vec3 getRotation() const;
	const Vec3 getScaling() const;
	const Vec3 getColor() const;
	const string& getTextContent() const;
	const string& getFontPath() const;
	const string& getDiffuseMapPath() const;
	const float getOriginalLightness() const;
	const float getLightness() const;
	const float getMaxY() const;
	const int getPassedFrames() const;
	const int getMaxFramestep() const;
	const int getTotalSpriteRows() const;
	const int getTotalSpriteColumns() const;
	const int getSpriteRowIndex() const;
	const int getSpriteColumnIndex() const;
	const int getAnimationRepeats() const;
	const int getMaxAnimationRepeats() const;
	const bool isTransparent() const;
	const bool hasSpriteAnimation() const;
	const bool isCameraFacingX() const;
	const bool isCameraFacingY() const;
	const bool isDepthMapIncluded() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	Vec3 _translation     = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _rotation        = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _initialRotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _scaling         = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 _color           = Vec3(1.0f);

	float _originalLightness = 1.0f;
	float _lightness = 1.0f;
	float _maxY = (std::numeric_limits<float>::max)();
	
	int _maxFramestep		 = 0;
	int _passedFrames		 = 0;
	int _totalSpriteRows     = 0;
	int _totalSpriteColumns  = 0;
	int _spriteRowIndex      = 0;
	int _spriteColumnIndex   = 0;
	int _animationRepeats    = 0;
	int _maxAnimationRepeats = 0;
	
	GLuint _diffuseMap = 0;

	string _textContent = "";
	string _diffuseMapPath = "";
	string _fontPath = "";

	bool _isTransparent      = false;
	bool _hasSpriteAnimation = false;
	bool _isCameraFacingX	 = false;
	bool _isCameraFacingY	 = false;
	bool _isDepthMapIncluded = true;
};