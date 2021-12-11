#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"

#include <memory>

using std::shared_ptr;

class ImageEntity : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// VOID
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
	void setMultiplierUV(fvec2 value);
	void setAdderUV(fvec2 value);
	void setPerspectiveDepthEntity(bool value);
	void setCentered(bool value);
	void setWireframed(bool value);

	// STRING
	const string& getDiffuseMapPath() const;

	// MAT44
	const mat44 getTransformationMatrix() const;

	// FVEC3
	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;

	// FVEC2
	const fvec2 getPosition() const;
	const fvec2 getSize() const;
	const fvec2 getMinPosition() const;
	const fvec2 getMaxPosition() const;
	const fvec2 getMultiplierUV() const;
	const fvec2 getAdderUV() const;

	// FLOAT
	const float getTransparency() const;
	const float getRotation() const;

	// UNSIGNED INT
	const unsigned int getDepth() const;

	// BOOL
	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isMirroredHorizonally() const;
	const bool isMirroredVertically() const;
	const bool isPerspectiveDepthEntity() const;
	const bool hasRenderBuffer() const;
	const bool hasDiffuseMap() const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getDiffuseMap() const;

private:
	// MAT44
	mat44 _transformationMatrix = mat44(1.0f);

	// STRING
	string _diffuseMapPath = "";

	// FVEC3
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	// FVEC2
	fvec2 _minPosition = fvec2(-1.0f);
	fvec2 _maxPosition = fvec2(1.0f);
	fvec2 _position = fvec2(0.0f);
	fvec2 _size = fvec2(1.0f);
	fvec2 _positionTarget = fvec2(0.0f);
	fvec2 _sizeTarget = fvec2(1.0f);
	fvec2 _multiplierUV = fvec2(1.0f);
	fvec2 _adderUV = fvec2(0.0f);

	// FLOAT
	float _rotation = 0.0f;
	float _rotationTarget = 0.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _transparency = 1.0f;

	// UNSIGNED INT
	unsigned int _depth = 0;

	// BOOL
	bool _isCentered = false;
	bool _isMirroredHorizontally = false;
	bool _isMirroredVertically = false;
	bool _isPerspectiveDepthEntity = false;
	bool _isWireframed = false;

	// MISCELLANEOUS
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};