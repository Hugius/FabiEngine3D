#pragma once

#include "base_entity.hpp"

class BillboardEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~BillboardEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(Vec3 value);
	void rotate(Vec3 value);
	void scale(Vec3 value);

	// Setters
	void setCameraFacingX(bool value);
	void setCameraFacingY(bool value);
	void setTransparent(bool value);
	void setDepthMapIncluded(bool value);
	void setDiffuseMap(GLuint value);
	void setTranslation(Vec3 value);
	void setInitialRotation(Vec3 value);
	void setRotation(Vec3 value);
	void setScaling(Vec3 value);
	void setColor(Vec3 color);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);
	void setDiffuseMapPath(const string& diffuseMapPath);
	void playSpriteAnimation(int maxAnimationRepeats);
	void stopSpriteAnimation();
	void setSpriteRowIndex(int value);
	void setSpriteColumnIndex(int value);
	void setTotalSpriteRows(int value);
	void setTotalSpriteColumns(int value);
	void setMaxFramestep(int value);
	void setLightness(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void increasePassedFrames();
	void resetPassedFrames();
	void increaseAnimationRepeats();

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
	const float getLightness() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
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
	const bool hasDiffuseMap() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	Vec3 _translation     = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _rotation        = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _initialRotation = Vec3(0.0f, 0.0f, 0.0f);
	Vec3 _scaling         = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 _color           = Vec3(1.0f);

	float _lightness = 1.0f;
	float _minHeight = -(std::numeric_limits<float>::max)();
	float _maxHeight = (std::numeric_limits<float>::max)();
	
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