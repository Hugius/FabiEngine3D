#pragma once

#include "base_entity.hpp"

class ImageEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Model matrix
	void updateModelMatrix();

	// Texture & color
	void setDiffuseMap(GLuint value);
	void setDiffuseMapPath(const string& value);
	void setColor(Vec3 value);
	void setMirroredHorizontally(bool value);
	void setMirroredVertically(bool value);
	void setAlpha(float value);

	// Transformation
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

	// Animation
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

	// Texture & color
	const GLuint getDiffuseMap() const;
	const string& getDiffuseMapPath() const;
	const Vec3 getColor() const;
	const float getAlpha() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool hasDiffuseMap() const;

	// Transformation
	const bool isCentered() const;
	const Matrix44 getModelMatrix() const;
	const Vec2 getPosition() const;
	const float getRotation() const;
	const Vec2 getSize() const;
	const Vec2 getMinPosition() const;
	const Vec2 getMaxPosition() const;
	const unsigned int getDepth() const;

	// Animation
	const bool isSpriteAnimationStarted() const;
	const bool isSpriteAnimationPaused() const;
	const int getPassedSpriteAnimationFrames() const;
	const int getMaxSpriteAnimationFramestep() const;
	const int getTotalSpriteAnimationRows() const;
	const int getTotalSpriteAnimationColumns() const;
	const int getSpriteAnimationRowIndex() const;
	const int getSpriteAnimationColumnIndex() const;
	const int getSpriteAnimationLoops() const;
	const int getMaxSpriteAnimationLoops() const;

	// Miscellaneous
	void setPerspectiveDepthEntity(bool value);
	const bool isPerspectiveDepthEntity() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	GLuint _diffuseMap = 0;

	string _diffuseMapPath = "";

	Vec3 _color = Vec3(1.0f);

	Vec2 _position = Vec2(0.0f);
	Vec2 _minPosition = Vec2(-1.0f);
	Vec2 _maxPosition = Vec2(1.0f);
	Vec2 _size = Vec2(1.0f);

	float _rotation = 0.0f;
	float _alpha    = 1.0f;

	int _maxSpriteAnimationFramestep = 0;
	int _passedSpriteAnimationFrames = 0;
	int _totalSpriteAnimationRows    = 0;
	int _totalSpriteAnimationColumns = 0;
	int _spriteAnimationRowIndex	 = 0;
	int _spriteAnimationColumnIndex  = 0;
	int _spriteAnimationLoops		 = 0;
	int _maxSpriteAnimationLoops     = 0;

	unsigned int _depth = 0;

	bool _isSpriteAnimationStarted = false;
	bool _isSpriteAnimationPaused  = false;
	bool _isMirroredHorizontally   = false;
	bool _isMirroredVertically	   = false;
	bool _isPerspectiveDepthEntity = false;
	bool _isCentered			   = false;
};