#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"

struct Animation final
{
	Animation(const string& ID)
		:
		ID(ID)
	{
		// Empty part = whole model
		partIDs.push_back("");
		totalMovements.insert(make_pair("", Vec3(0.0f)));
		totalRotations.insert(make_pair("", Vec3(0.0f)));
		totalScalings.insert(make_pair("", Vec3(0.0f)));

		// Add default frame
		AnimationFrame defaultFrame;
		defaultFrame.targetTransformations.insert(make_pair("", Vec3(0.0f)));
		defaultFrame.rotationOrigins.insert(make_pair("", Vec3(0.0f)));
		defaultFrame.speeds.insert(make_pair("", Vec3(0.0f)));
		defaultFrame.speedTypes.insert(make_pair("", AnimationSpeedType::LINEAR));
		defaultFrame.transformationTypes.insert(make_pair("", TransformationType::MOVEMENT));
		frames.push_back(defaultFrame);
	}

	void updateValueLimits()
	{
		for (auto& [partID, totalScaling] : totalScalings)
		{
			totalScaling = Vec3(std::max(0.0f, totalScaling.x), std::max(0.0f, totalScaling.y), std::max(0.0f, totalScaling.z));
		}
		speedMultiplier = std::max(0.0f, speedMultiplier);
		initialSize = Vec3(std::max(0.0f, initialSize.x), std::max(0.0f, initialSize.y), std::max(0.0f, initialSize.z));
	}

	const string ID;

	vector<AnimationFrame> frames;
	vector<string> partIDs;

	map<string, Vec3> totalMovements;
	map<string, Vec3> totalRotations;
	map<string, Vec3> totalScalings;

	Vec3 initialSize = Vec3(0.0f);

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