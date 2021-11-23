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

	// VOID
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

	// STRING
	const array<string, 6>& getCubeMapPaths() const;

	// MAT44
	const mat44& getRotationMatrix() const;

	// FVEC3
	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;

	// FLOAT
	const float getInitialLightness() const;
	const float getLightness() const;
	const float getRotation() const;

	// BOOL
	const bool hasRenderBuffer() const;
	const bool hasCubeMap() const;
	const bool isWireframed() const;

	// MISCELLANEOUS
	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getCubeMap() const;

private:
	// STRING
	array<string, 6> _cubeMapPaths = {"", "", "", "", "", "" };

	// MAT44
	mat44 _rotationMatrix = mat44(1.0f);

	// FVEC3
	fvec3 _wireframeColor = fvec3(1.0f);
	fvec3 _color = fvec3(1.0f);

	// FLOAT
	float _initialLightness = 1.0f;
	float _lightness = 1.0f;
	float _rotation = 0.0f;

	// BOOL
	bool _isWireframed = false;

	// MISCELLANEOUS
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _cubeMap = 0;
};