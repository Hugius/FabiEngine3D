#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"

class AnimationFrame
{
public:
	map<string, Vec3> targetTransformations;
	map<string, Vec3> totalTransformations;

	map<string, float> originalSpeeds;
	map<string, float> speeds;

	map<string, AnimationSpeedType> speedTypes;

	vector<string> partNames;
};