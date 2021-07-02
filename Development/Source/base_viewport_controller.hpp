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

	static inline const float calculateTextWidth(const string& text, float charWidth)
	{
		return static_cast<float>(text.size()) * charWidth;
	}

protected:
	FabiEngine3D& _fe3d;

	EngineGuiManager& _gui;
};