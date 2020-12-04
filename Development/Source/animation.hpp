#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		modelID = "";
		frames.push_back(AnimationFrame());
	}

	const string ID;

	string modelID;

	vector<AnimationFrame> frames;

	Vec3 totalTranslation = Vec3(0.0f);
	Vec3 totalRotation = Vec3(0.0f);
	Vec3 totalScaling = Vec3(0.0f);
};