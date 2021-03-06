#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_manager.hpp"

class BaseViewportController
{
public:
	BaseViewportController(FabiEngine3D& fe3d, EngineGuiManager& gui);

	virtual void initialize() = 0;
	virtual void update() = 0;

	// Static stuff for easier GUI function calls
	static inline const float calcTextWidth(const string& text, float charWidth, float maxWidth)
	{
		return std::min(static_cast<float>(text.size()) * charWidth, maxWidth);
	}

protected:
	FabiEngine3D& _fe3d;

	EngineGuiManager& _gui;
};