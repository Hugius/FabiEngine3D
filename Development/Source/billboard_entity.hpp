#pragma once

#include "base_entity.hpp"

#include <GLM\\glm.hpp>
#include <GLM\\gtc\\matrix_transform.hpp>

using glm::ivec2;
using glm::mat4;

class BillboardEntity final: public BaseEntity
{
public:
	BillboardEntity()  = default;
	~BillboardEntity() = default;

	// Updates
	void updateModelMatrix();
	void translate(vec3 val);
	void rotate(vec3 val);
	void scale(vec3 val);

	// Setters
	void setCameraFacingX(bool val);
	void setCameraFacingY(bool val);
	void setDiffuseMap(GLuint val);
	void setTranslation(vec3 val);
	void setInitialRotation(vec3 val);
	void setRotation(vec3 val);
	void setScaling(vec3 val);
	void setColor(vec3 color);
	void setTextContent(const string& text);
	void setFontPath(const string& fontPath);
	void setDiffuseMapPath(const string& diffuseMapPath);
	void setTransparent(bool val);
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
	void setUvRepeat(float val);
	void setMaxY(float val);

	// Getters
	const mat4 & getModelMatrix() const;
	const GLuint getDiffuseMap() const;
	const vec3 getTranslation() const;
	const vec3 getInitialRotation() const;
	const vec3 getRotation() const;
	const vec3 getScaling() const;
	const vec3 getColor() const;
	const string& getTextContent() const;
	const string& getFontPath() const;
	const string& getDiffuseMapPath() const;
	const float getOriginalLightness() const;
	const float getLightness() const;
	const float getUvRepeat() const;
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

private:
	mat4 _modelMatrix = mat4(1.0f);

	vec3 _translation     = vec3(0.0f, 0.0f, 0.0f);
	vec3 _rotation        = vec3(0.0f, 0.0f, 0.0f);
	vec3 _initialRotation = vec3(0.0f, 0.0f, 0.0f);
	vec3 _scaling         = vec3(1.0f, 1.0f, 1.0f);
	vec3 _color           = vec3(1.0f);

	float _originalLightness = 1.0f;
	float _lightness = 1.0f;
	float _uvRepeat = 1.0f;
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
};