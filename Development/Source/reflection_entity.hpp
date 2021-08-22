#pragma once

#include "base_entity.hpp"
#include "mathematics.hpp"
#include "render_utils.hpp"
#include "capture_buffer.hpp"

#include <array>

using std::array;

class ReflectionEntity final : public BaseEntity
{
public:
	using BaseEntity::BaseEntity;

	// Voids
	void setPosition(Vec3 value);
	void move(Vec3 value);
	void setEnvironmentMap(TextureID value);

	// Instances
	CaptureBuffer& getCaptureBuffer(unsigned int index);

	// Vectors
	const Vec3 getPosition();

	// Miscellaneous
	const TextureID getEnvironmentMap();

private:
	// Instances
	array<CaptureBuffer, 6> _captureBuffers;

	// Vectors
	Vec3 _position = Vec3(0.0f);

	// Miscellaneous
	TextureID _environmentMap;
};