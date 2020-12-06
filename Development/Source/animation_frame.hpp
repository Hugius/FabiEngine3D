#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"

struct AnimationFrame
{
	Vec3 targetTransformation = Vec3(0.0f);

	float speed = 0.0f;

	AnimationSpeedType speedType;
};