#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"

#include <array>

using std::array;

class ReflectionEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void capture();
	void setCaptured();
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void setCubeMap(TextureID value);

	// Vectors
	const Vec3 getPosition();

	// Booleans
	const bool mustCapture();

	// Miscellaneous
	const TextureID getCubeMap();

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);

	// Boolean
	bool _mustCapture = false;
	bool _isCaptured = false;

	// Miscellaneous
	TextureID _cubeMap;
};