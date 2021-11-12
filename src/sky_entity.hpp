#pragma once

#include "base_entity.hpp"
#include "render_buffer.hpp"
#include "direction.hpp"

#include <array>
#include <memory>

using std::array;
using std::shared_ptr;

class SkyEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void updateRotationMatrix();
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setDiffuseMapPaths(const array<string, 6>& value);
	void setColor(Vec3 value);
	void setCubeMap(TextureID value);
	void setOriginalLightness(float value);
	void setLightness(float value);
	void setRotation(float value);
	void setRotationSpeed(float value);
	void setWireframed(bool value);

	// Strings
	const array<string, 6>& getDiffuseMapPaths() const;

	// Matrices
	const Matrix44& getRotationMatrix() const;

	// Vectors
	const Vec3 getColor() const;

	// Decimals
	const float getOriginalLightness() const;
	const float getLightness() const;
	const float getRotation() const;
	const float getRotationSpeed() const;

	// Booleans
	const bool hasRenderBuffer() const;
	const bool hasCubeMap() const;
	const bool isWireframed() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getDiffuseMap() const;

private:
	// Strings
	array<string, 6> _diffuseMapPaths = { "", "", "", "", "", "" };

	// Matrices
	Matrix44 _rotationMatrix = Matrix44(1.0f);

	// Vectors
	Vec3 _color = Vec3(1.0f);

	// Decimals
	float _originalLightness = 1.0f;
	float _lightness = 1.0f;
	float _rotationSpeed = 0.0f;
	float _rotation = 0.0f;

	// Booleans
	bool _isWireframed = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _diffuseMap = 0;
};