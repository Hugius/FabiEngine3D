#pragma once

#include "base_entity.hpp"
#include "vertex_buffer.hpp"
#include "direction.hpp"
#include "texture_buffer.hpp"

#include <array>

using std::array;

class SkyEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	void updateTransformation();
	void setMesh(shared_ptr<VertexBuffer> value);
	void setCubeMapPaths(const array<string, 6>& value);
	void setColor(const fvec3& value);
	void setCubeMap(shared_ptr<TextureBuffer> value);
	void setLightness(float value);
	void setRotation(float value);
	void setWireframed(bool value);
	void setWireframeColor(const fvec3& value);

	const array<string, 6>& getCubeMapPaths() const;

	const mat44& getTransformation() const;

	const fvec3& getWireframeColor() const;
	const fvec3& getColor() const;

	const float getLightness() const;
	const float getRotation() const;

	const bool isWireframed() const;

	const shared_ptr<VertexBuffer> getMesh() const;
	const shared_ptr<TextureBuffer> getCubeMap() const;

private:
	array<string, 6> _cubeMapPaths = {"", "", "", "", "", ""};

	mat44 _transformation = mat44(1.0f);

	fvec3 _color = fvec3(1.0f);
	fvec3 _wireframeColor = fvec3(1.0f);

	float _lightness = 1.0f;
	float _rotation = 0.0f;

	bool _isWireframed = false;

	shared_ptr<VertexBuffer> _mesh = nullptr;
	shared_ptr<TextureBuffer> _cubeMap = nullptr;
};