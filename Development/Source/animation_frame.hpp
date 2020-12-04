#pragma once

#include "fabi_engine_3d.hpp"

struct AnimationFrame
{
	Vec3 translation = Vec3(0.0f);
	Vec3 rotation = Vec3(0.0f);
	Vec3 scaling = Vec3(0.0f);
	Vec3 speed = Vec3(0.0f);
};