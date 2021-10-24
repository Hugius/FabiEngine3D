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
	void setAlpha(float value);
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
	void setTotalSpriteAnimationRows(unsigned int value);
	void setTotalSpriteAnimationColumns(unsigned int value);
	void setMaxSpriteAnimationFramestep(unsigned int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();
	void setPerspectiveDepthEntity(bool value);

	// Strings
	const string& getDiffuseMapPath();

	// Matrices
	const Matrix44 getTransformationMatrix();

	// Vectors
	const Vec3 getColor();
	const Vec2 getPosition();
	const Vec2 getSize();
	const Vec2 getMinPosition();
	const Vec2 getMaxPosition();

	// Decimals
	const float getAlpha();
	const float getRotation();

	// Integers
	const int getMaxSpriteAnimationLoops();
	const unsigned int getPassedSpriteAnimationFrames();
	const unsigned int getMaxSpriteAnimationFramestep();
	const unsigned int getTotalSpriteAnimationRows();
	const unsigned int getTotalSpriteAnimationColumns();
	const unsigned int getSpriteAnimationRowIndex();
	const unsigned int getSpriteAnimationColumnIndex();
	const unsigned int getSpriteAnimationLoops();
	const unsigned int getDepth();

	// Booleans
	const bool isMirroredHorizonally();
	const bool isMirroredVertically();
	const bool isSpriteAnimationStarted();
	const bool isSpriteAnimationPaused();
	const bool isPerspectiveDepthEntity();
	const bool hasRenderBuffer();
	const bool hasDiffuseMap();

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer();
	const TextureID getDiffuseMap();

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
	float _alpha = 1.0f;

	// Integers
	int _maxSpriteAnimationLoops = 0;
	unsigned int _maxSpriteAnimationFramestep = 0;
	unsigned int _passedSpriteAnimationFrames = 0;
	unsigned int _totalSpriteAnimationRows = 0;
	unsigned int _totalSpriteAnimationColumns = 0;
	unsigned int _spriteAnimationRowIndex = 0;
	unsigned int _spriteAnimationColumnIndex = 0;
	unsigned int _spriteAnimationLoops = 0;
	unsigned int _depth = 0;

	// Booleans
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused = false;
	bool _isMirroredHorizontally = false;
	bool _isMirroredVertically = false;
	bool _isPerspectiveDepthEntity = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};