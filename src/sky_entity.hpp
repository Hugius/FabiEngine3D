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
	SkyEntity(const string& ID);

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

	const array<string, 6>& getCubeMapPaths() const;

	const mat44& getRotationMatrix() const;

	const fvec3 getWireframeColor() const;
	const fvec3 getColor() const;

	const float getInitialLightness() const;
	const float getLightness() const;
	const float getRotation() const;

	const bool hasRenderBuffer() const;
	const bool hasCubeMap() const;
	const bool isWireframed() const;

	const shared_ptr<RenderBuffer> getRenderBuffer() const;
	const TextureID getCubeMap() const;

private:
	array<string, 6> _cubeMapPaths = {"", "", "", "", "", ""};

	mat44 _rotationMatrix = mat44(1.0f);

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	float _initialLightness = 1.0f;
	float _lightness = 1.0f;
	float _rotation = 0.0f;

	bool _isWireframed = false;

	shared_ptr<RenderBuffer> _renderBuffer = nullptr;
	TextureID _cubeMap = 0;
};