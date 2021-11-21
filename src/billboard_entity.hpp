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
	void setWireframed(bool value);
	void setDiffuseMap(TextureID value, bool isTextual);
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
	void setTotalSpriteAnimationRowCount(unsigned int value);
	void setTotalSpriteAnimationColumnCount(unsigned int value);
	void setSpriteAnimationFramestep(unsigned int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();
	void setLightness(float value);
	void setColorInversion(float value);
	void setTransparency(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setTextureRepeat(float value);
	void setEmissionIntensity(float value);

	// Strings
	const string& getTextContent() const;
	const string& getFontPath() const;
	const string& getDiffuseMapPath() const;
	const string& getEmissionMapPath() const;

	// Matrices
	const Matrix44& getTransformationMatrix() const;

	// Vectors
	const Vec3 getPosition() const;
	const Vec3 getRotation() const;
	const Vec3 getColor() const;
	const Vec2 getSize() const;

	// Decimals
	const float getLightness() const;
	const float getColorInversion() const;
	const float getTransparency() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const float getTextureRepeat() const;
	const float getEmissionIntensity() const;

	// Integers
	const int getMaxSpriteAnimationLoops() const;
	const unsigned int getPassedSpriteAnimationFrames() const;
	const unsigned int getSpriteAnimationFramestep() const;
	const unsigned int getTotalSpriteAnimationRowCount() const;
	const unsigned int getTotalSpriteAnimationColumnCount() const;
	const unsigned int getSpriteAnimationRowIndex() const;
	const unsigned int getSpriteAnimationColumnIndex() const;
	const unsigned int getSpriteAnimationLoops() const;

	// Booleans
	const bool isSpriteAnimationStarted() const;
	const bool isSpriteAnimationPaused() const;
	const bool isFacingCameraX() const;
	const bool isFacingCameraY() const;
	const bool isDepthMapIncluded() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isBright() const;
	const bool isTextual() const;
	const bool isWireframed() const;
	const bool hasRenderBuffer() const;
	const bool hasDiffuseMap() const;
	const bool hasEmissionMap() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getDiffuseMap() const;
	const TextureID getEmissionMap() const;

private:
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

	// Decimals
	float _emissionIntensity = 1.0f;
	float _textureRepeat = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _colorInversion = 0.0f;
	float _transparency = 1.0f;
	float _minHeight = -(numeric_limits<float>::max)();
	float _maxHeight = (numeric_limits<float>::max)();

	// Integers
	int _maxSpriteAnimationLoops = 0;
	unsigned int _spriteAnimationFramestep = 0;
	unsigned int _passedSpriteAnimationFrames = 0;
	unsigned int _totalSpriteAnimationRowCount = 0;
	unsigned int _totalSpriteAnimationColumnCount = 0;
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
	bool _isWireframed = false;
	bool _isTextual = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
	TextureID _emissionMap = 0;
};