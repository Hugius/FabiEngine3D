#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

#define VPC BaseViewportController

class BaseViewportController
{
public:
	BaseViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

	static inline const vector<float> calculateButtonPositions(unsigned int buttonCount, float buttonHeight)
	{
		// Positions to return
		vector<float> result;

		// Pre-calculations
		float freeSpace = (2.0f - (static_cast<float>(buttonCount) * buttonHeight));
		float gapSpace = freeSpace / static_cast<float>(buttonCount + 1);
		float height = 1.0f;

		// First position
		height -= (gapSpace + (buttonHeight / 2.0f));
		
		// The rest of the positions
		for (unsigned int i = 0; i < buttonCount; i++)
		{
			result.push_back(height);
			height -= (gapSpace + buttonHeight);
		}

		// Return
		return result;
	}

	static inline const float calculateTextWidth(const string& text, float charWidth)
	{
		return static_cast<float>(text.size()) * charWidth;
	}

protected:
	FabiEngine3D& _fe3d;

	EngineGuiManager& _gui;
};