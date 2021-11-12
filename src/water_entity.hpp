#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "water_quality.hpp"

#include <memory>

using std::shared_ptr;

class WaterEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void setLowQualityRenderBuffer(shared_ptr<RenderBuffer> value);
	void setHighQualityRenderBuffer(shared_ptr<RenderBuffer> value);
	void setQuality(WaterQuality value);
	void setSpeed(Vec2 value);
	void setRippleOffset(Vec2 value);
	void setWaveOffset(Vec2 value);
	void setColor(Vec3 value);
	void setDudvMap(TextureID value);
	void setNormalMap(TextureID value);
	void setDisplacementMap(TextureID value);
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

	// Strings
	const string& getDudvMapPath() const;
	const string& getNormalMapPath() const;
	const string& getDisplacementMapPath() const;

	// Vectors
	const Vec3 getColor() const;
	const Vec2 getSpeed() const;
	const Vec2 getRippleOffset() const;
	const Vec2 getWaveOffset() const;

	// Decimals
	const float getHeight() const;
	const float getTextureRepeat() const;
	const float getWaveHeight() const;
	const float getSpecularShininess() const;
	const float getSpecularIntensity() const;
	const float getSize() const;
	const float getTransparency() const;

	// Booleans
	const bool isSpecular() const;
	const bool isReflective() const;
	const bool isRefractive() const;
	const bool isWireframed() const;
	const bool hasLowQualityRenderBuffer() const;
	const bool hasHighQualityRenderBuffer() const;
	const bool hasDudvMap() const;
	const bool hasNormalMap() const;
	const bool hasDisplacementMap() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getLowQualityRenderBuffer() const;
	const shared_ptr<RenderBuffer> getHighQualityRenderBuffer() const;
	const WaterQuality getQuality() const;
	const TextureID getDudvMap() const;
	const TextureID getNormalMap() const;
	const TextureID getDisplacementMap() const;

private:
	// Vectors
	Vec3 _color = Vec3(1.0f);
	Vec2 _speed = Vec2(0.0f);
	Vec2 _rippleOffset = Vec2(0.0f);
	Vec2 _waveOffset = Vec2(0.0f);

	// Strings
	string _dudvMapPath = "";
	string _normalMapPath = "";
	string _displacementMapPath = "";

	// Decimals
	float _height = 0.0f;
	float _size = 1.0f;
	float _textureRepeat = 1.0f;
	float _waveHeight = 0.0f;
	float _specularShininess = 1.0f;
	float _specularIntensity = 1.0f;
	float _transparency = 0.0f;

	// Booleans
	bool _isSpecular = false;
	bool _isReflective = false;
	bool _isRefractive = false;
	bool _isWireframed = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _lowQualityRenderBuffer = nullptr;
	shared_ptr<RenderBuffer> _highQualityRenderBuffer = nullptr;
	WaterQuality _quality = WaterQuality::SKY;
	TextureID _dudvMap = 0;
	TextureID _normalMap = 0;
	TextureID _displacementMap = 0;
};