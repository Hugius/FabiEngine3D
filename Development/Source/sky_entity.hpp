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
	void setVisible(bool value);
	void setRenderBuffer(shared_ptr<RenderBuffer> value);
	void setDiffuseMapPaths(const array<string, 6>& value);
	void setColor(Vec3 value);
	void setCubeMap(TextureID value);
	void setOriginalLightness(float value);
	void setLightness(float value);
	void setRotation(float value);
	void setRotationSpeed(float value);
	void setWireFramed(bool value);

	// Instances
	const shared_ptr<RenderBuffer> getRenderBuffer();

	// Strings
	const array<string, 6>& getDiffuseMapPaths();

	// Matrices
	const Matrix44& getRotationMatrix();

	// Vectors
	const Vec3 getColor();

	// Floats
	const float getOriginalLightness();
	const float getLightness();
	const float getRotation();
	const float getRotationSpeed();

	// Booleans
	const bool isVisible();
	const bool hasRenderBuffer();
	const bool hasCubeMap();
	const bool isWireFramed();

	// Miscellaneous
	const TextureID getCubeMap();

private:
	// Instances
	shared_ptr<RenderBuffer> _renderBuffer = nullptr;

	// Strings
	array<string, 6> _diffuseMapPaths = { "", "", "", "", "", "" };

	// Matrices
	Matrix44 _rotationMatrix = Matrix44(1.0f);

	// Vectors
	Vec3 _color = Vec3(1.0f);

	// Floats
	float _originalLightness = 1.0f;
	float _lightness = 1.0f;
	float _rotationSpeed = 0.0f;
	float _rotation = 0.0f;

	// Booleans
	bool _isVisible = true;
	bool _isWireFramed = false;

	// Miscellaneous
	TextureID _cubeMap = 0;
};