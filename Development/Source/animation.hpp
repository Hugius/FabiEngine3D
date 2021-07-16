#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		// Empty part = whole model
		partIDs.push_back("");
		totalTranslations.insert(make_pair("", Vec3(0.0f)));
		totalRotations.insert(make_pair("", Vec3(0.0f)));
		totalScalings.insert(make_pair("", Vec3(0.0f)));

		// Add default frame
		frames.push_back(AnimationFrame(""));
	}

	void updateValueLimits()
	{
		for (auto& [partID, totalScaling] : totalScalings)
		{
			totalScaling = Vec3(std::max(0.0f, totalScaling.x), std::max(0.0f, totalScaling.y), std::max(0.0f, totalScaling.z));
		}
		speedMultiplier = std::max(0.0f, speedMultiplier);
		initialScaling = Vec3(std::max(0.0f, initialScaling.x), std::max(0.0f, initialScaling.y), std::max(0.0f, initialScaling.z));
	}

	const string ID;

	vector<AnimationFrame> frames;
	vector<string> partIDs;

	map<string, Vec3> totalTranslations;
	map<string, Vec3> totalRotations;
	map<string, Vec3> totalScalings;

	Vec3 initialScaling = Vec3(0.0f);

	string previewModelID = "";
	string oldPreviewModelID = "";
	string animatedModelID = "";

	float speedMultiplier = 1.0f;

	int timesToPlay = 0;
	int fadeFramestep = -1;
	int fadeFrameIndex = -1;

	unsigned int frameIndex = 0;

	bool isPaused = false;
	bool isAutoPaused = false;
};