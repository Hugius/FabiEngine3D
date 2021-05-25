#pragma once

#include "base_entity.hpp"

class BillboardEntity final: public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

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
	void setTextContent(const string& value);
	void setFontPath(const string& value);
	void setDiffuseMapPath(const string& value);
	void startSpriteAnimation(int loops);
	void pauseSpriteAnimation();
	void resumeSpriteAnimation();
	void stopSpriteAnimation();
	void setSpriteAnimationRowIndex(unsigned int value);
	void setSpriteAnimationColumnIndex(unsigned int value);
	void setTotalSpriteAnimationRows(unsigned int value);
	void setTotalSpriteAnimationColumns(unsigned int value);
	void setMaxSpriteAnimationFramestep(unsigned int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();
	void setLightness(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);

	// Getters
	const Matrix44& getModelMatrix() const;
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
	const int getPassedSpriteAnimationFrames() const;
	const int getMaxSpriteAnimationFramestep() const;
	const int getTotalSpriteAnimationRows() const;
	const int getTotalSpriteAnimationColumns() const;
	const int getSpriteAnimationRowIndex() const;
	const int getSpriteAnimationColumnIndex() const;
	const int getSpriteAnimationLoops() const;
	const int getMaxSpriteAnimationLoops() const;
	const bool isTransparent() const;
	const bool isSpriteAnimationStarted() const;
	const bool isSpriteAnimationPaused() const;
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
	
	unsigned int _maxSpriteAnimationFramestep = 0;
	unsigned int _passedSpriteAnimationFrames = 0;
	unsigned int _totalSpriteAnimationRows    = 0;
	unsigned int _totalSpriteAnimationColumns = 0;
	unsigned int _spriteAnimationRowIndex     = 0;
	unsigned int _spriteAnimationColumnIndex  = 0;
	int _spriteAnimationLoops      = 0;
	int _maxSpriteAnimationLoops   = 0;
	
	GLuint _diffuseMap = 0;

	string _textContent	   = "";
	string _diffuseMapPath = "";
	string _fontPath	   = "";

	bool _isTransparent			   = false;
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused  = false;
	bool _isCameraFacingX	       = false;
	bool _isCameraFacingY	       = false;
	bool _isDepthMapIncluded       = true;
};