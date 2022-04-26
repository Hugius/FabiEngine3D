#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "texture_buffer.hpp"

#include <memory>

using std::shared_ptr;

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setLowQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setHighQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setRippleSpeed(const fvec2 & value);
	void setWaveSpeed(const fvec2 & value);
	void setRippleOffset(const fvec2 & value);
	void setWaveOffset(const fvec2 & value);
	void setColor(const fvec3 & value);
	void setDudvMap(shared_ptr<TextureBuffer> value);
	void setNormalMap(shared_ptr<TextureBuffer> value);
	void setDisplacementMap(shared_ptr<TextureBuffer> value);
	void setDudvMapPath(const string & value);
	void setNormalMapPath(const string & value);
	void setDisplacementMapPath(const string & value);
	void setTextureRepeat(int value);
	void setWaveHeight(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setHeight(float value);
	void setSize(float value);
	void setMaxDepth(float value);
	void setEdged(bool value);
	void setSpecular(bool value);
	void setReflective(bool value);
	void setRefractive(bool value);
	void setWireframed(bool value);
	void setWireframeColor(const fvec3 & value);
	void setMinClipPosition(const fvec3 & value);
	void setMaxClipPosition(const fvec3 & value);

	const shared_ptr<VertexBuffer> getLowQualityVertexBuffer() const;
	const shared_ptr<VertexBuffer> getHighQualityVertexBuffer() const;
	const shared_ptr<TextureBuffer> getDudvTextureBuffer() const;
	const shared_ptr<TextureBuffer> getNormalTextureBuffer() const;
	const shared_ptr<TextureBuffer> getDisplacementTextureBuffer() const;

	const string & getDudvMapPath() const;
	const string & getNormalMapPath() const;
	const string & getDisplacementMapPath() const;

	const fvec3 & getColor() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getMinClipPosition() const;
	const fvec3 & getMaxClipPosition() const;

	const fvec2 & getRippleOffset() const;
	const fvec2 & getRippleSpeed() const;
	const fvec2 & getWaveOffset() const;
	const fvec2 & getWaveSpeed() const;

	const float getHeight() const;
	const float getWaveHeight() const;
	const float getMaxDepth() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;
	const float getSize() const;

	const int getTextureRepeat() const;

	const bool isSpecular() const;
	const bool isReflective() const;
	const bool isRefractive() const;
	const bool isWireframed() const;
	const bool isEdged() const;

private:
	static inline constexpr float MAX_SIZE = 1024.0f;

	shared_ptr<VertexBuffer> _lowQualityVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _highQualityVertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _dudvTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _normalTextureBuffer = nullptr;
	shared_ptr<TextureBuffer> _displacementTextureBuffer = nullptr;

	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _minClipPosition = fvec3(-FLT_MAX);
	fvec3 _maxClipPosition = fvec3(FLT_MAX);

	fvec2 _rippleOffset = fvec2(0.0f);
	fvec2 _rippleSpeed = fvec2(0.0f);
	fvec2 _waveSpeed = fvec2(0.0f);
	fvec2 _waveOffset = fvec2(0.0f);

	float _height = 0.0f;
	float _size = 1.0f;
	float _waveHeight = 0.0f;
	float _maxDepth = 0.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;

	unsigned int _textureRepeat = 1;

	bool _isSpecular = false;
	bool _isEdged = 1.0f;
	bool _isReflective = false;
	bool _isRefractive = false;
	bool _isWireframed = false;
};