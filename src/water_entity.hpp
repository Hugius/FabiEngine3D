#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "water_quality.hpp"

#include <memory>

using std::shared_ptr;

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void setLowQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setHighQualityVertexBuffer(shared_ptr<VertexBuffer> value);
	void setQuality(WaterQuality value);
	void setSpeed(fvec2 value);
	void setRippleOffset(fvec2 value);
	void setWaveOffset(fvec2 value);
	void setColor(fvec3 value);
	void setDudvMap(shared_ptr<TextureBuffer> value);
	void setNormalMap(shared_ptr<TextureBuffer> value);
	void setDisplacementMap(shared_ptr<TextureBuffer> value);
	void setDudvMapPath(const string& value);
	void setNormalMapPath(const string& value);
	void setDisplacementMapPath(const string& value);
	void setTextureRepeat(float value);
	void setWaveHeight(float value);
	void setSpecularShininess(float value);
	void setSpecularIntensity(float value);
	void setHeight(float value);
	void setSize(float value);
	void setTransparency(float value);
	void setSpecular(bool value);
	void setReflective(bool value);
	void setRefractive(bool value);
	void setWireframed(bool value);
	void setWireframeColor(fvec3 value);

	const string& getDudvMapPath() const;
	const string& getNormalMapPath() const;
	const string& getDisplacementMapPath() const;

	const fvec3 getColor() const;
	const fvec3 getWireframeColor() const;

	const fvec2 getSpeed() const;
	const fvec2 getRippleOffset() const;
	const fvec2 getWaveOffset() const;

	const float getHeight() const;
	const float getTextureRepeat() const;
	const float getWaveHeight() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;
	const float getSize() const;
	const float getTransparency() const;

	const bool isSpecular() const;
	const bool isReflective() const;
	const bool isRefractive() const;
	const bool isWireframed() const;
	const bool hasLowQualityVertexBuffer() const;
	const bool hasHighQualityVertexBuffer() const;
	const bool hasDudvMap() const;
	const bool hasNormalMap() const;
	const bool hasDisplacementMap() const;

	const shared_ptr<VertexBuffer> getLowQualityVertexBuffer() const;
	const shared_ptr<VertexBuffer> getHighQualityVertexBuffer() const;
	const WaterQuality getQuality() const;
	const shared_ptr<TextureBuffer> getDudvMap() const;
	const shared_ptr<TextureBuffer> getNormalMap() const;
	const shared_ptr<TextureBuffer> getDisplacementMap() const;

private:
	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	fvec2 _speed = fvec2(0.0f);
	fvec2 _rippleOffset = fvec2(0.0f);
	fvec2 _waveOffset = fvec2(0.0f);

	float _height = 0.0f;
	float _size = 1.0f;
	float _textureRepeat = 1.0f;
	float _waveHeight = 0.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;
	float _transparency = 0.0f;

	bool _isSpecular = false;
	bool _isReflective = false;
	bool _isRefractive = false;
	bool _isWireframed = false;

	shared_ptr<VertexBuffer> _lowQualityVertexBuffer = nullptr;
	shared_ptr<VertexBuffer> _highQualityVertexBuffer = nullptr;
	WaterQuality _quality = WaterQuality::SKY;
	shared_ptr<TextureBuffer> _dudvMap = 0;
	shared_ptr<TextureBuffer> _normalMap = 0;
	shared_ptr<TextureBuffer> _displacementMap = 0;
};