#pragma once

#include "fe3d.hpp"
#include "engine_gui_viewport.hpp"
#include "engine_gui_global_screen.hpp"

class EngineGuiManager final
{
public:
	EngineGuiManager(FabiEngine3D& fe3d);

	// Voids
	void update();

	// Miscellaneous
	shared_ptr<EngineGuiGlobalScreen> getGlobalScreen();
	shared_ptr<EngineGuiViewport> getViewport(const string& ID);

	// Vectors
	static inline const fvec3 FRAME_COLOR = fvec3(0.025f);

private:
	// Miscellaneous
	vector<shared_ptr<EngineGuiViewport>> _viewports;
	shared_ptr<EngineGuiGlobalScreen> _globalScreen;
	FabiEngine3D& _fe3d;
};