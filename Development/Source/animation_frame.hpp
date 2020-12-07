#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"

class AnimationFrame
{
public:
	AnimationFrame()
	{
		targetTransformations.insert(make_pair("", Vec3(0.0f)));
		originalSpeeds.insert(make_pair("", 0.0f));
		speeds.insert(make_pair("", 0.0f));
		speedTypes.insert(make_pair("", AnimationSpeedType::LINEAR));
	}

	map<string, Vec3> targetTransformations;

	map<string, float> originalSpeeds;
	map<string, float> speeds;

	map<string, AnimationSpeedType> speedTypes;
};