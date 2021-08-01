#pragma once

#include "fabi_engine_3d.hpp"
#include "engine_gui_viewport.hpp"
#include "engine_gui_global_screen.hpp"

class EngineGuiManager final
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	void update();

	shared_ptr<EngineGuiGlobalScreen> getGlobalScreen();
	shared_ptr<EngineGuiViewport> getViewport(const string& ID);

	static inline const Vec3 FRAME_COLOR = Vec3(0.025f);

private:
	FabiEngine3D& _fe3d;

	shared_ptr<EngineGuiGlobalScreen> _globalScreen;

	vector<shared_ptr<EngineGuiViewport>> _viewports;
};