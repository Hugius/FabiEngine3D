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
	void setCubeMapPaths(const array<string, 6>& value);
	void setColor(fvec3 value);
	void setCubeMap(TextureID value);
	void setInitialLightness(float value);
	void setLightness(float value);
	void setRotation(float value);
	void setWireframed(bool value);
	void setWireframeColor(fvec3 value);

	// Strings
	const array<string, 6>& getCubeMapPaths() const;

	// Matrices
	const mat44& getRotationMatrix() const;

	// Vectors
	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;

	// Decimals
	const float getInitialLightness() const;
	const float getLightness() const;
	const float getRotation() const;

	// Booleans
	const bool hasRenderBuffer() const;
	const bool hasCubeMap() const;
	const bool isWireframed() const;

	// Miscellaneous
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getCubeMap() const;

private:
	// Strings
	array<string, 6> _cubeMapPaths = { "", "", "", "", "", "" };

	// Matrices
	mat44 _rotationMatrix = mat44(1.0f);

	// Vectors
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	// Decimals
	float _initialLightness = 1.0f;
	float _lightness = 1.0f;
	float _rotation = 0.0f;

	// Booleans
	bool _isWireframed = false;

	// Miscellaneous
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _cubeMap = 0;
};