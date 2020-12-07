#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"
#include "transformation_type.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		previewModelID = "";
		frames.push_back(AnimationFrame());
	}

	const string ID;

	string previewModelID = "";
	string animatedModelID = "";

	unsigned int frameIndex = 0;

	int timesToPlay = 0;

	vector<AnimationFrame> frames;

	Vec3 initialTranslation = Vec3(0.0f);
	Vec3 initialRotation = Vec3(0.0f);
	Vec3 initialScaling = Vec3(0.0f);
	Vec3 initialColor = Vec3(0.0f);
	Vec3 totalTransformation = Vec3(0.0f);

	TransformationType transformationType = TransformationType::TRANSLATION;
};