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
	void updateModelMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setDiffuseMap(TextureID value);
	void setDiffuseMapPath(const string& value);
	void setColor(Vec3 value);
	void setMirroredHorizontally(bool value);
	void setMirroredVertically(bool value);
	void setAlpha(float value);
	void setCentered(bool value);
	void setPosition(Vec2 value);
	void setRotation(float value);
	void setSize(Vec2 value);
	void move(Vec2 value);
	void rotate(float value);
	void scale(Vec2 value);
	void setMinPosition(Vec2 value);
	void setMaxPosition(Vec2 value);
	void setDepth(unsigned int value);
	void startSpriteAnimation(int loops);
	void pauseSpriteAnimation();
	void resumeSpriteAnimation();
	void stopSpriteAnimationAnimation();
	void setSpriteAnimationRowIndex(int value);
	void setSpriteAnimationColumnIndex(int value);
	void setTotalSpriteAnimationRows(int value);
	void setTotalSpriteAnimationColumns(int value);
	void setMaxSpriteAnimationFramestep(int value);
	void increasePassedSpriteAnimationFrames();
	void resetPassedSpriteAnimationFrames();
	void increaseSpriteAnimationLoops();
	void setPerspectiveDepthEntity(bool value);

	// Strings
	const string& getDiffuseMapPath();

	// Matrices
	const Matrix44 getModelMatrix();

	// Vectors
	const Vec3 getColor();
	const Vec2 getPosition();
	const Vec2 getSize();
	const Vec2 getMinPosition();
	const Vec2 getMaxPosition();

	// Floats
	const float getAlpha();
	const float getRotation();

	// Integers
	const int getPassedSpriteAnimationFrames();
	const int getMaxSpriteAnimationFramestep();
	const int getTotalSpriteAnimationRows();
	const int getTotalSpriteAnimationColumns();
	const int getSpriteAnimationRowIndex();
	const int getSpriteAnimationColumnIndex();
	const int getSpriteAnimationLoops();
	const int getMaxSpriteAnimationLoops();
	const unsigned int getDepth();

	// Booleans
	const bool isMirroredHorizonally();
	const bool isMirroredVertically();
	const bool isSpriteAnimationStarted();
	const bool isSpriteAnimationPaused();
	const bool isPerspectiveDepthEntity();
	const bool isCentered();
	const bool hasRenderBuffer();
	const bool hasDiffuseMap();

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer();
	const TextureID getDiffuseMap();

private:

	// Matrices
	Matrix44 _modelMatrix = Matrix44(1.0f);

	// Strings
	string _diffuseMapPath = "";

	// Vectors
	Vec3 _color = Vec3(1.0f);
	Vec2 _position = Vec2(0.0f);
	Vec2 _minPosition = Vec2(-1.0f);
	Vec2 _maxPosition = Vec2(1.0f);
	Vec2 _size = Vec2(1.0f);

	// Floats
	float _rotation = 0.0f;
	float _alpha = 1.0f;

	// Integers
	int _maxSpriteAnimationFramestep = 0;
	int _passedSpriteAnimationFrames = 0;
	int _totalSpriteAnimationRows = 0;
	int _totalSpriteAnimationColumns = 0;
	int _spriteAnimationRowIndex = 0;
	int _spriteAnimationColumnIndex = 0;
	int _spriteAnimationLoops = 0;
	int _maxSpriteAnimationLoops = 0;
	unsigned int _depth = 0;

	// Booleans
	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused = false;
	bool _isMirroredHorizontally = false;
	bool _isMirroredVertically = false;
	bool _isPerspectiveDepthEntity = false;
	bool _isCentered = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};