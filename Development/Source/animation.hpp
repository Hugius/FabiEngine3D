#pragma once

#include "fabi_engine_3d.hpp"
#include "animation_frame.hpp"

class Animation final
{
public:
	Animation(const string& ID) : ID(ID)
	{
		modelID = "";
	}

	const string ID;

	string modelID;

	vector<AnimationFrame> frames;
};