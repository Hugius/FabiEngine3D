#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class ImageEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateTransformation();
	void updateTransformationMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setDiffuseMap(TextureID value);
	void setDiffuseMapPath(const string& value);
	void setMirroredHorizontally(bool value);
	void setMirroredVertically(bool value);
	void setTransparency(float value);
	void setColor(Vec3 value);
	void setMinPosition(Vec2 value);
	void setMaxPosition(Vec2 value);
	void setPosition(Vec2 value);
	void setRotation(float value);
	void setSize(Vec2 value);
	void move(Vec2 value);
	void rotate(float value);
	void scale(Vec2 value);
	void moveTo(Vec2 target, float speed);
	void rotateTo(float target, float speed);
	void scaleTo(Vec2 target, float speed);
	void setDepth(unsigned int value);
	void startSpriteAnimation(int loops);
	void pauseSpriteAnimation();
	void resumeSpriteAnimation();
	void stopSpriteAnimationAnimation();
	void setSpriteAnimationRowIndex(unsigned int value);
	void setSpriteAnimationColumnIndex(unsigned int value);
	void setTotalSpriteAnimationRowCount(unsigned int value);
	void setTotalSpriteAnimationColumnCount(unsigned int value);
	void setSpriteAnimationFramestep(unsigned int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();
	void setPerspectiveDepthEntity(bool value);
	void setCentered(bool value);

	// Strings
	const string& getDiffuseMapPath() const;

	// Matrices
	const Matrix44 getTransformationMatrix() const;

	// Vectors
	const Vec3 getColor() const;
	const Vec2 getPosition() const;
	const Vec2 getSize() const;
	const Vec2 getMinPosition() const;
	const Vec2 getMaxPosition() const;

	// Decimals
	const float getTransparency() const;
	const float getRotation() const;

	// Integers
	const int getMaxSpriteAnimationLoops() const;
	const unsigned int getPassedSpriteAnimationFrames() const;
	const unsigned int getSpriteAnimationFramestep() const;
	const unsigned int getTotalSpriteAnimationRowCount() const;
	const unsigned int getTotalSpriteAnimationColumnCount() const;
	const unsigned int getSpriteAnimationRowIndex() const;
	const unsigned int getSpriteAnimationColumnIndex() const;
	const unsigned int getSpriteAnimationLoops() const;
	const unsigned int getDepth() const;

	// Booleans
	const bool isCentered() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool isSpriteAnimationStarted() const;
	const bool isSpriteAnimationPaused() const;
	const bool isPerspectiveDepthEntity() const;
	const bool hasRenderBuffer() const;
	const bool hasDiffuseMap() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getDiffuseMap() const;

private:
	// Matrices
	Matrix44 _transformationMatrix = Matrix44(1.0f);

	// Strings
	string _diffuseMapPath = "";

	// Vectors
	Vec3 _color = Vec3(1.0f);
	Vec2 _minPosition = Vec2(-1.0f);
	Vec2 _maxPosition = Vec2(1.0f);
	Vec2 _position = Vec2(0.0f);
	Vec2 _size = Vec2(1.0f);
	Vec2 _positionTarget = Vec2(0.0f);
	Vec2 _sizeTarget = Vec2(1.0f);

	// Decimals
	float _rotation = 0.0f;
	float _rotationTarget = 0.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _transparency = 1.0f;

	// Integers
	int _maxSpriteAnimationLoops = 0;
	unsigned int _spriteAnimationFramestep = 0;
	unsigned int _passedSpriteAnimationFrames = 0;
	unsigned int _totalSpriteAnimationRowCount = 0;
	unsigned int _totalSpriteAnimationColumnCount = 0;
	unsigned int _spriteAnimationRowIndex = 0;
	unsigned int _spriteAnimationColumnIndex = 0;
	unsigned int _spriteAnimationLoops = 0;
	unsigned int _depth = 0;

	// Booleans
	bool _isCentered = false;
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused = false;
	bool _isMirroredHorizontally = false;
	bool _isMirroredVertically = false;
	bool _isPerspectiveDepthEntity = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};