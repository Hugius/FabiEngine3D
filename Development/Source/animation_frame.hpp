#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"
#include "transformation_type.hpp"

struct AnimationFrame final
{
	map<string, Vec3> targetTransformations;

	map<string, Vec3> rotationOrigins;

	map<string, Vec3> speeds;

	map<string, AnimationSpeedType> speedTypes;

	map<string, TransformationType> transformationTypes;
};