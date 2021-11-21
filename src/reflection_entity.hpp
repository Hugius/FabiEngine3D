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
	void setPosition(fvec3 value);
	void move(fvec3 value);
	void moveTo(fvec3 target, float speed);
	void setCubeMap(TextureID value);

	// Vectors
	const fvec3 getPosition() const;

	// Booleans
	const bool mustCapture() const;

	// Miscellaneous
	const TextureID getCubeMap() const;

private:
	// Vectors
	fvec3 _position = fvec3(0.0f);
	fvec3 _positionTarget = fvec3(0.0f);

	// Decimals
	float _positionTargetSpeed = 0.0f;

	// Booleans
	bool _mustCapture = false;
	bool _isCaptured = false;

	// Miscellaneous
	TextureID _cubeMap;
};