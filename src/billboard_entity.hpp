#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>

using std::shared_ptr;
using std::numeric_limits;

class BillboardEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void updateTransformation();
	void updateTransformationMatrix();
	void setFacingCameraX(bool value);
	void setFacingCameraY(bool value);
	void setDepthMapIncluded(bool value);
	void setShadowed(bool value);
	void setCentered(bool value);
	void setReflected(bool value);
	void setBright(bool value);
	void setWireframed(bool value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value, bool isTextual);
	void setEmissionMap(shared_ptr<TextureBuffer> value);
	void setPosition(fvec3 value);
	void setRotation(fvec3 value);
	void setSize(fvec2 value);
	void move(fvec3 value);
	void rotate(fvec3 value);
	void scale(fvec2 value);
	void moveTo(fvec3 target, float speed);
	void rotateTo(fvec3 target, float speed);
	void scaleTo(fvec2 target, float speed);
	void setColor(fvec3 value);
	void setUvMultiplier(fvec2 value);
	void setUvOffset(fvec2 value);
	void setWireframeColor(fvec3 value);
	void setTextContent(const string& value);
	void setFontPath(const string& value);
	void setDiffuseMapPath(const string& value);
	void setEmissionMapPath(const string& value);
	void setLightness(float value);
	void setTransparency(float value);
	void setMinHeight(float value);
	void setMaxHeight(float value);
	void setTextureRepeat(float value);
	void setEmissionIntensity(float value);
	void setFrozen(bool value);

	const string& getTextContent() const;
	const string& getFontPath() const;
	const string& getDiffuseMapPath() const;
	const string& getEmissionMapPath() const;

	const mat44& getTransformationMatrix() const;

	const fvec3 getPosition() const;
	const fvec3 getRotation() const;
	const fvec3 getColor() const;
	const fvec3 getWireframeColor() const;

	const fvec2 getSize() const;
	const fvec2 getUvMultiplier() const;
	const fvec2 getUvOffset() const;

	const float getLightness() const;
	const float getTransparency() const;
	const float getMinHeight() const;
	const float getMaxHeight() const;
	const float getTextureRepeat() const;
	const float getEmissionIntensity() const;

	const bool isFacingCameraX() const;
	const bool isFacingCameraY() const;
	const bool isDepthMapIncluded() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isBright() const;
	const bool isTextual() const;
	const bool isFrozen() const;
	const bool isWireframed() const;
	const bool hasVertexBuffer() const;
	const bool hasDiffuseMap() const;
	const bool hasEmissionMap() const;
	const bool isCentered() const;

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDiffuseMap() const;
	const shared_ptr<TextureBuffer> getEmissionMap() const;

private:
	string _textContent = "";
	string _diffuseMapPath = "";
	string _emissionMapPath = "";
	string _fontPath = "";

	mat44 _transformationMatrix = mat44(1.0f);

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

	float _emissionIntensity = 1.0f;
	float _textureRepeat = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _transparency = 1.0f;
	float _minHeight = numeric_limits<float>::lowest();
	float _maxHeight = numeric_limits<float>::max();

	bool _isFacingCameraX = false;
	bool _isFacingCameraY = false;
	bool _isDepthMapIncluded = true;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isBright = false;
	bool _isWireframed = false;
	bool _isTextual = false;
	bool _isFrozen = false;
	bool _isCentered = false;

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _diffuseMap = nullptr;
	shared_ptr<TextureBuffer> _emissionMap = nullptr;
};