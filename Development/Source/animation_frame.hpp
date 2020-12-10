#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"
#include "transformation_type.hpp"

class AnimationFrame
{
public:
	AnimationFrame() = default;

	AnimationFrame(const string& partName)
	{
		// Default data
		targetTransformations.insert(make_pair(partName, Vec3(0.0f)));
		rotationOrigins.insert(make_pair(partName, Vec3(0.0f)));
		speeds.insert(make_pair(partName, 0.0f));
		speedTypes.insert(make_pair(partName, AnimationSpeedType::LINEAR));
		transformationTypes.insert(make_pair(partName, TransformationType::TRANSLATION));
	}

	map<string, Vec3> targetTransformations;
	map<string, Vec3> rotationOrigins;

	map<string, float> speeds;

	map<string, AnimationSpeedType> speedTypes;

	map<string, TransformationType> transformationTypes;
};