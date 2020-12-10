#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		// Empty partname = whole model
		partNames.push_back("");
		totalTransformations.insert(make_pair("", Vec3(0.0f)));

		// Add default frame
		frames.push_back(AnimationFrame(""));
	}

	const string ID;

	string previewModelID = "";
	string oldPreviewModelID = "";
	string animatedModelID = "";

	unsigned int frameIndex = 0;

	int timesToPlay = 0;

	vector<AnimationFrame> frames;
	vector<string> partNames;

	Vec3 initialTranslation = Vec3(0.0f);
	Vec3 initialRotation = Vec3(0.0f);
	Vec3 initialScaling = Vec3(0.0f);
	Vec3 initialColor = Vec3(0.0f);

	map<string, Vec3> totalTransformations;
};