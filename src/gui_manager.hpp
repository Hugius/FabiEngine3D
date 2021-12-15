#pragma once

#include "fe3d.hpp"
#include "gui_viewport.hpp"
#include "gui_global_screen.hpp"

class GuiManager final
{
public:
	GuiManager(FabiEngine3D& fe3d);

	// VOID
	void update();

	// MISCELLANEOUS
	shared_ptr<GuiGlobalScreen> getGlobalScreen();
	shared_ptr<GuiViewport> getViewport(const string& ID);

	// FVEC3
	static inline const fvec3 FRAME_COLOR = fvec3(0.025f);

private:
	// MISCELLANEOUS
	vector<shared_ptr<GuiViewport>> _viewports;
	shared_ptr<GuiGlobalScreen> _globalScreen;
	FabiEngine3D& _fe3d;
};