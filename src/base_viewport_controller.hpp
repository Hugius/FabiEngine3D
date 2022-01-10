#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"

class BaseViewportController
{
public:
	BaseViewportController(EngineInterface& fe3d, GuiManager& gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

	static const vector<float> calculateButtonPositions(unsigned int buttonCount, float buttonHeight);

	static const float calculateTextWidth(const string& text, float charWidth);

protected:
	EngineInterface& _fe3d;
	GuiManager& _gui;
};