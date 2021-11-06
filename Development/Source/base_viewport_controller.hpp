#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"

class BaseViewportController
{
public:
	BaseViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	// Voids
	virtual void initialize() = 0;
	virtual void update() = 0;

	// Decimals
	static const vector<float> calculateButtonPositions(unsigned int buttonCount, float buttonHeight);

	// Decimals
	static const float calculateTextWidth(const string& text, float charWidth);

protected:
	// Miscellaneous
	FabiEngine3D& _fe3d;
	EngineGuiManager& _gui;
};