#pragma once

#include "base_entity.hpp"

class GuiEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;
	~GuiEntity() = default;

	// Model matrix
	void updateModelMatrix();

	// Texture & color
	void setTexture(GLuint texture);
	void setColor(Vec3 color);
	void setMirroredHorizontally(bool value);
	void setMirroredVertically(bool value);
	void setAlpha(float value);

	// Transformation
	void setCentered(bool value);
	void setTranslation(Vec2 value);
	void setRotation(float value);
	void setScaling(Vec2 value);
	void translate(Vec2 value);
	void rotate(float value);
	void scale(Vec2 value);
	void setMinPosition(Vec2 value);
	void setMaxPosition(Vec2 value);
	void setDepth(unsigned int value);

	// Animation
	void playSpriteAnimation(int maxAnimationRepeats);
	void stopSpriteAnimation();
	void setSpriteRowIndex(int value);
	void setSpriteColumnIndex(int value);
	void setTotalSpriteRows(int value);
	void setTotalSpriteColumns(int value);
	void setMaxFramestep(int value);
	void increasePassedFrames();
	void resetPassedFrames();
	void increaseAnimationRepeats();

	// Texture & color
	const GLuint getTexture() const;
	const Vec3 getColor() const;
	const float getAlpha() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool hasTexture() const;

	// Transformation
	const bool isCentered() const;
	const Matrix44 getModelMatrix() const;
	const Vec2 getTranslation() const;
	const float getRotation() const;
	const Vec2 getScaling() const;
	const Vec2 getMinPosition() const;
	const Vec2 getMaxPosition() const;
	const unsigned int getDepth() const;

	// Animation
	const bool hasSpriteAnimation() const;
	const int getPassedFrames() const;
	const int getMaxFramestep() const;
	const int getTotalSpriteRows() const;
	const int getTotalSpriteColumns() const;
	const int getSpriteRowIndex() const;
	const int getSpriteColumnIndex() const;
	const int getAnimationRepeats() const;
	const int getMaxAnimationRepeats() const;

	// Other
	void setDepthEntity(bool value);
	const bool isDepthEntity() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	GLuint _texture = 0;

	Vec3 _color = Vec3(1.0f);

	Vec2 _translation = Vec2(0.0f);
	Vec2 _scaling     = Vec2(1.0f);
	Vec2 _minPosition = Vec2(-1.0f);
	Vec2 _maxPosition = Vec2(1.0f);

	float _rotation = 0.0f;
	float _alpha = 1.0f;

	int _maxFramestep = 0;
	int _passedFrames = 0;
	int _totalSpriteRows = 0;
	int _totalSpriteColumns = 0;
	int _spriteRowIndex = 0;
	int _spriteColumnIndex = 0;
	int _animationRepeats = 0;
	int _maxAnimationRepeats = 0;

	unsigned int _depth = 0;

	bool _hasSpriteAnimation   = false;
	bool _mirroredHorizontally = false;
	bool _mirroredVertically   = false;
	bool _isDepthEntity        = false;
	bool _isCentered		   = false;
};