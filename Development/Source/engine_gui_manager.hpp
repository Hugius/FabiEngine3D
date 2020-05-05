#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_viewport.hpp"
#include "engine_gui_global_screen.hpp"

class EngineGuiManager final
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void update(float delta);
	void setFocus(bool focused);

	shared_ptr<EngineGuiGlobalScreen> getGlobalScreen();
	shared_ptr<EngineGuiViewport> getViewport(const string& ID);

private:
	FabiEngine3D& _fe3d;

	shared_ptr<EngineGuiGlobalScreen> _globalScreen;
	std::vector<shared_ptr<EngineGuiViewport>> _viewports;

	bool _isFocused = false;
};