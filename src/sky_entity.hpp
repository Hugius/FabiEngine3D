#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "direction_type.hpp"
#include "texture_buffer.hpp"

#include <array>

using std::array;

class SkyEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTarget();
	void updateTransformation();
	void setVertexBuffer(shared_ptr<VertexBuffer> value);
	void setCubeMapPaths(const array<string, 6> & value);
	void setColor(const fvec3 & value);
	void setCubeMap(shared_ptr<TextureBuffer> value);
	void setLightness(float value);
	void setRotation(const fvec3 & value);
	void rotate(const fvec3 & change);
	void rotateTo(const fvec3 & target, float speed);
	void setWireframed(bool value);
	void setWireframeColor(const fvec3 & value);

	const array<string, 6> & getCubeMapPaths() const;

	const shared_ptr<VertexBuffer> getVertexBuffer() const;
	const shared_ptr<TextureBuffer> getCubeTextureBuffer() const;

	const mat44 & getTransformation() const;

	const fvec3 & getRotation() const;
	const fvec3 & getWireframeColor() const;
	const fvec3 & getColor() const;

	const float getLightness() const;

	const bool isWireframed() const;

private:
	array<string, 6> _cubeMapPaths = {"", "", "", "", "", ""};

	shared_ptr<VertexBuffer> _vertexBuffer = nullptr;
	shared_ptr<TextureBuffer> _cubeTextureBuffer = nullptr;

	mat44 _transformation = mat44(1.0f);

	fvec3 _rotation = fvec3(0.0f);
	fvec3 _rotationTarget = fvec3(0.0f);
	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	float _rotationTargetSpeed = 0.0f;
	float _lightness = 1.0f;

	bool _isWireframed = false;
};