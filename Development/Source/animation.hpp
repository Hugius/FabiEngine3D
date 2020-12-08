#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"
#include "transformation_type.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		// Add default frame
		AnimationFrame frame;
		frame.targetTransformations.insert(make_pair("", Vec3(0.0f)));
		frame.totalTransformations.insert(make_pair("", Vec3(0.0f)));
		frame.speeds.insert(make_pair("", 0.0f));
		frame.speedTypes.insert(make_pair("", AnimationSpeedType::LINEAR));
		frame.partNames.push_back("");
		frames.push_back(frame);
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

	TransformationType transformationType = TransformationType::TRANSLATION;
};