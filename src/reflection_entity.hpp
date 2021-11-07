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
	void updateTransformation();
	void capture();
	void setCaptured();
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void moveTo(Vec3 target, float speed);
	void setCubeMap(TextureID value);

	// Vectors
	const Vec3 getPosition() const;

	// Booleans
	const bool mustCapture() const;

	// Miscellaneous
	const TextureID getCubeMap() const;

private:
	// Vectors
	Vec3 _position = Vec3(0.0f);
	Vec3 _positionTarget = Vec3(0.0f);

	// Decimals
	float _positionTargetSpeed = 0.0f;

	// Booleans
	bool _mustCapture = false;
	bool _isCaptured = false;

	// Miscellaneous
	TextureID _cubeMap;
};