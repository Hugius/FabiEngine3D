#pragma once

#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>
#include <string>

using std::string;
using std::shared_ptr;

class Quad3d final
{
public:
	Quad3d(const string & id);

	void updateTarget();
	void updateTransformation();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setFacingCameraHorizontally(bool value);
	void setFacingCameraVertically(bool value);
	void setShadowed(bool value);
	void setCentered(bool value);
	void setReflected(bool value);
	void setRefracted(bool value);
	void setBright(bool value);
	void setWireframed(bool value);
	void setDiffuseMap(shared_ptr<TextureBuffer> value);
	void setEmissionMap(shared_ptr<TextureBuffer> value);
	void setPosition(const fvec3 & value);
	void setRotation(const fvec3 & value);
	void setSize(const fvec2 & value);
	void move(const fvec3 & change);
	void rotate(const fvec3 & change);
	void scale(const fvec2 & change);
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
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);
	void setTextureRepeat(int value);
	void setEmissionIntensity(float value);
	void setMinAlpha(float value);
	void setHorizontallyFlipped(bool value);
	void setVerticallyFlipped(bool value);
	void setRotationOrder(DirectionOrderType value);
	void setVisible(bool value);

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDiffuseTextureBuffer() const;
	const shared_ptr<TextureBuffer> getEmissionTextureBuffer() const;

	const string & getId() const;
	const string & getDiffuseMapPath() const;
	const string & getEmissionMapPath() const;

	const mat44 & getTransformation() const;

	const fvec3 & getPosition() const;
	const fvec3 & getRotation() const;
	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const fvec2 & getSize() const;
	const fvec2 & getUvMultiplier() const;
	const fvec2 & getUvOffset() const;

	const float getLightness() const;
	const float getOpacity() const;
	const float getEmissionIntensity() const;
	const float getMinAlpha() const;

	const int getTextureRepeat() const;

	const bool isVisible() const;
	const bool isFacingCameraHorizontally() const;
	const bool isFacingCameraVertically() const;
	const bool isShadowed() const;
	const bool isReflected() const;
	const bool isRefracted() const;
	const bool isBright() const;
	const bool isWireframed() const;
	const bool isCentered() const;
	const bool isHorizontallyFlipped() const;
	const bool isVerticallyFlipped() const;

	const DirectionOrderType getRotationOrder() const;

private:
	const string _id;

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
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	fvec2 _size = fvec2(1.0f);
	fvec2 _sizeTarget = fvec2(1.0f);
	fvec2 _uvMultiplier = fvec2(1.0f);
	fvec2 _uvOffset = fvec2(0.0f);

	float _minAlpha = 1.0f;
	float _emissionIntensity = 1.0f;
	float _positionTargetSpeed = 0.0f;
	float _rotationTargetSpeed = 0.0f;
	float _sizeTargetSpeed = 0.0f;
	float _lightness = 1.0f;
	float _opacity = 1.0f;

	int _textureRepeat = 1;

	bool _isFacingCameraHorizontally = false;
	bool _isFacingCameraVertically = false;
	bool _isShadowed = true;
	bool _isReflected = true;
	bool _isRefracted = true;
	bool _isBright = false;
	bool _isWireframed = false;
	bool _isCentered = false;
	bool _isHorizontallyFlipped = false;
	bool _isVerticallyFlipped = false;
	bool _isVisible = true;

	DirectionOrderType _rotationOrder = DirectionOrderType::YXZ;
};