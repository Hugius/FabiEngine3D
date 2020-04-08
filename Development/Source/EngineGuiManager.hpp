#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiViewport.hpp"

class EngineGuiManager
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void load();
	void update(float delta);
	void unload();

private:
	FabiEngine3D& FE3D;

	std::vector<EngineGuiViewport> _viewports;

	float _delta = 0.0f;
};