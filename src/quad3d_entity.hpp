#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>

using std::shared_ptr;

class Quad3dEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTarget();
	void updateTransformation();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setFacingCameraHorizontally(bool value);
	void setFacingCameraVertically(bool value);
	void setShadowed(bool value);
	void setCentered(bool value);
	void setReflected(bool value);
	void setBright(bool value);
	void setWireframed(bool value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value);
	void setEmissionMap(shared_ptr<TextureBuffer> value);
	void setPosition(const fvec3 & value);
	void setRotation(const fvec3 & value);
	void setSize(const fvec2 & value);
	void move(const fvec3 & value);
	void rotate(const fvec3 & value);
	void scale(const fvec2 & value);
	void moveTo(const fvec3 & target, float speed);
	void rotateTo(const fvec3 & target, float speed);
	void scaleTo(const fvec2 & target, float speed);
	void setColor(const fvec3 & value);
	void setUvMultiplier(const fvec2 & value);
	void setUvOffset(const fvec2 & value);
	void setWireframeColor(const fvec3 & value);
	void setDiffuseMapPath(const string & value);
	void setEmissionMapPath(const string & value);
	void setLightness(float value);
	void setOpacity(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setTextureRepeat(unsigned int value);
	void setEmissionIntensity(float value);
	void setFrozen(bool value);
	void setMinTextureAlpha(float value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getEmissionTextureBuffer() const;

	const string & getDiffuseMapPath() const;
	const string & getEmissionMapPath() const;

	const mat44 & getTransformation() const;

	const fvec3 & getPosition() const;
	const fvec3 & getRotation() const;
	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;

	const fvec2 & getSize() const;
	const fvec2 & getUvMultiplier() const;
	const fvec2 & getUvOffset() const;

	const float getLightness() const;
	const float getOpacity() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const float getEmissionIntensity() const;
	const float getMinTextureAlpha() const;

	const unsigned int getTextureRepeat() const;

	const bool isFacingCameraHorizontally() const;
	const bool isFacingCameraVertically() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isBright() const;
	const bool isFrozen() const;
	const bool isWireframed() const;
	const bool isCentered() const;

private:
	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _diffuseTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _emissionTextureBuffer = nullptr;

	string _diffuseMapPath = "";
	string _emissionMapPath = "";

	mat44 _transformation = mat44(1.0f);

	fvec3 _position = fvec3(0.0f);
	fvec3 _rotation = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);
	fvec3 _rotationTarget = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	fvec2 _size = fvec2(1.0f);
	fvec2 _sizeTarget = fvec2(1.0f);
	fvec2 _uvMultiplier = fvec2(1.0f);
	fvec2 _uvOffset = fvec2(0.0f);

	float _minTextureAlpha = 1.0f;
	float _emissionIntensity = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _opacity = 1.0f;
	float _minHeight = -FLT_MAX;
	float _maxHeight = FLT_MAX;

	unsigned int _textureRepeat = 1;

	bool _isFacingCameraHorizontally = false;
	bool _isFacingCameraVertically = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isBright = false;
	bool _isWireframed = false;
	bool _isFrozen = false;
	bool _isCentered = false;
};