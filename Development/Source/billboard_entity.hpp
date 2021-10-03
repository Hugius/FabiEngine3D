#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;
using std::numeric_limits;

class BillboardEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void updateTransformationMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setCameraFacingX(bool value);
	void setCameraFacingY(bool value);
	void setDepthMapIncluded(bool value);
	void setShadowed(bool value);
	void setReflected(bool value);
	void setBright(bool value);
	void setWireFramed(bool value);
	void setDiffuseMap(TextureID value, bool isText);
	void setEmissionMap(TextureID value);
	void setPosition(Vec3 value);
	void setRotation(Vec3 value);
	void setSize(Vec2 value);
	void move(Vec3 value);
	void rotate(Vec3 value);
	void scale(Vec2 value);
	void moveTo(Vec3 target, float speed);
	void rotateTo(Vec3 target, float speed);
	void scaleTo(Vec2 target, float speed);
	void setColor(Vec3 color);
	void setTextContent(const string& value);
	void setFontPath(const string& value);
	void setDiffuseMapPath(const string& value);
	void setEmissionMapPath(const string& value);
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
	void setColorInversion(float value);
	void setAlpha(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setTextureRepeat(float value);
	void setEmissionIntensity(float value);

	// Instances
	const shared_ptr<RenderBuffer> getRenderBuffer();

	// Strings
	const string& getTextContent();
	const string& getFontPath();
	const string& getDiffuseMapPath();
	const string& getEmissionMapPath();

	// Matrices
	const Matrix44& getTransformationMatrix();

	// Vectors
	const Vec3 getPosition();
	const Vec3 getRotation();
	const Vec3 getColor();
	const Vec2 getSize();

	// Floats
	const float getLightness();
	const float getColorInversion();
	const float getAlpha();
	const float getMinHeight();
	const float getMaxHeight();
	const float getTextureRepeat();
	const float getEmissionIntensity();

	// Integers
	const int getMaxSpriteAnimationLoops();
	const unsigned int getPassedSpriteAnimationFrames();
	const unsigned int getMaxSpriteAnimationFramestep();
	const unsigned int getTotalSpriteAnimationRows();
	const unsigned int getTotalSpriteAnimationColumns();
	const unsigned int getSpriteAnimationRowIndex();
	const unsigned int getSpriteAnimationColumnIndex();
	const unsigned int getSpriteAnimationLoops();

	// Booleans
	const bool isSpriteAnimationStarted();
	const bool isSpriteAnimationPaused();
	const bool isFacingCameraX();
	const bool isFacingCameraY();
	const bool isDepthMapIncluded();
	const bool isShadowed();
	const bool isReflected();
	const bool isBright();
	const bool isText();
	const bool isWireFramed();
	const bool hasRenderBuffer();
	const bool hasDiffuseMap();
	const bool hasEmissionMap();

	// Miscellaneous
	const TextureID getDiffuseMap();
	const TextureID getEmissionMap();

private:
	// Instances
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;

	// Strings
	string _textContent = "";
	string _diffuseMapPath = "";
	string _emissionMapPath = "";
	string _fontPath = "";

	// Matrices
	Matrix44 _transformationMatrix = Matrix44(1.0f);

	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _rotation = Vec3(0.0f);
	Vec3 _positionTarget = Vec3(0.0f);
	Vec3 _rotationTarget = Vec3(0.0f);
	Vec3 _color = Vec3(1.0f);
	Vec2 _size = Vec2(1.0f);
	Vec2 _sizeTarget = Vec2(1.0f);

	// Floats
	float _emissionIntensity = 1.0f;
	float _textureRepeat = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _colorInversion = 0.0f;
	float _alpha = 1.0f;
	float _minHeight = -(numeric_limits<float>::max)();
	float _maxHeight = (numeric_limits<float>::max)();

	// Integers
	int _maxSpriteAnimationLoops = 0;
	unsigned int _maxSpriteAnimationFramestep = 0;
	unsigned int _passedSpriteAnimationFrames = 0;
	unsigned int _totalSpriteAnimationRows = 0;
	unsigned int _totalSpriteAnimationColumns = 0;
	unsigned int _spriteAnimationRowIndex = 0;
	unsigned int _spriteAnimationColumnIndex = 0;
	unsigned int _spriteAnimationLoops = 0;

	// Booleans
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused = false;
	bool _isFacingCameraX = false;
	bool _isFacingCameraY = false;
	bool _isDepthMapIncluded = true;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isBright = false;
	bool _isWireFramed = false;
	bool _isText = false;

	// Miscellaneous
	TextureID _diffuseMap = 0;
	TextureID _emissionMap = 0;
};