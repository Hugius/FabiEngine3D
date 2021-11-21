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
	void setWireframeColor(fvec3 value);
	void setColor(fvec3 value);
	void setMinPosition(fvec2 value);
	void setMaxPosition(fvec2 value);
	void setPosition(fvec2 value);
	void setRotation(float value);
	void setSize(fvec2 value);
	void move(fvec2 value);
	void rotate(float value);
	void scale(fvec2 value);
	void moveTo(fvec2 target, float speed);
	void rotateTo(float target, float speed);
	void scaleTo(fvec2 target, float speed);
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
	void setWireframed(bool value);

	// Strings
	const string& getDiffuseMapPath() const;

	// Matrices
	const mat44 getTransformationMatrix() const;

	// Vectors
	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;
	const fvec2 getPosition() const;
	const fvec2 getSize() const;
	const fvec2 getMinPosition() const;
	const fvec2 getMaxPosition() const;

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
	const bool isWireframed() const;
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
	mat44 _transformationMatrix = mat44(1.0f);

	// Strings
	string _diffuseMapPath = "";

	// Vectors
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec2 _minPosition = fvec2(-1.0f);
	fvec2 _maxPosition = fvec2(1.0f);
	fvec2 _position = fvec2(0.0f);
	fvec2 _size = fvec2(1.0f);
	fvec2 _positionTarget = fvec2(0.0f);
	fvec2 _sizeTarget = fvec2(1.0f);

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
	bool _isWireframed = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};