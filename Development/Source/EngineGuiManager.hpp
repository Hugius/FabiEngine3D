#pragma once

#include "FabiEngine3D.hpp"
#include "EngineGuiViewport.hpp"
#include "EngineGuiGlobalScreen.hpp"

class EngineGuiManager final
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void load();
	void update(float delta);
	void unload();

	shared_ptr<EngineGuiViewport> getViewport(const string& ID);

private:
	FabiEngine3D& _fe3d;

	std::vector<shared_ptr<EngineGuiViewport>> _viewports;

	EngineGuiGlobalScreen _globalScreen;

	float _delta = 0.0f;

	void _updateTopViewport();
	void _updateLeftViewport();
	void _updateRightViewport();
	void _updateBottomViewport();
};