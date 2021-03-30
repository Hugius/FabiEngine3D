#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_speed_type.hpp"
#include "transformation_type.hpp"

class AnimationFrame
{
public:
	AnimationFrame() = default;

	AnimationFrame(const string& partID)
	{
		// Default data
		targetTransformations.insert(make_pair(partID, Vec3(0.0f)));
		rotationOrigins.insert(make_pair(partID, Vec3(0.0f)));
		speeds.insert(make_pair(partID, 0.0f));
		speedTypes.insert(make_pair(partID, AnimationSpeedType::LINEAR));
		transformationTypes.insert(make_pair(partID, TransformationType::TRANSLATION));
	}

	map<string, Vec3> targetTransformations;
	map<string, Vec3> rotationOrigins;

	map<string, float> speeds;

	map<string, AnimationSpeedType> speedTypes;

	map<string, TransformationType> transformationTypes;
};