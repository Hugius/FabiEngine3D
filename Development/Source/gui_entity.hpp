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
	void setDiffuseMap(GLuint diffuseMap);
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

	// Texture & color
	const GLuint getDiffuseMap() const;
	const Vec3 getColor() const;
	const float getAlpha() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool hasDiffuseMap() const;

	// Transformation
	const bool isCentered() const;
	const Matrix44 getModelMatrix() const;
	const Vec2 getTranslation() const;
	const float getRotation() const;
	const Vec2 getScaling() const;
	const Vec2 getMinPosition() const;
	const Vec2 getMaxPosition() const;
	const unsigned int getDepth() const;

	// Other
	void setDepthEntity(bool value);
	const bool isDepthEntity() const;

private:
	Matrix44 _modelMatrix = Matrix44(1.0f);

	GLuint _diffuseMap = 0;

	Vec3 _color = Vec3(1.0f);

	Vec2  _translation = Vec2(0.0f);
	float _rotation    = 0.0f;
	Vec2  _scaling     = Vec2(1.0f);

	Vec2 _minPosition = Vec2(-1.0f);
	Vec2 _maxPosition = Vec2(1.0f);

	float _alpha = 1.0f;

	unsigned int _depth = 0;

	bool _mirroredHorizontally = false;
	bool _mirroredVertically   = false;
	bool _isDepthEntity        = false;
	bool _isCentered		   = false;
};