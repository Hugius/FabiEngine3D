#pragma once

#include "fe3d.hpp"
#include "gui_viewport.hpp"
#include "gui_overlay.hpp"

class GuiManager final
{
public:
	GuiManager(FabiEngine3D& fe3d);

	// VOID
	void update();

	// MISCELLANEOUS
	shared_ptr<GuiViewport> getViewport(const string& ID);
	shared_ptr<GuiOverlay> getOverlay();

	// FVEC3
	static inline const fvec3 FRAME_COLOR = fvec3(0.025f);

private:
	// MISCELLANEOUS
	vector<shared_ptr<GuiViewport>> _viewports;
	shared_ptr<GuiOverlay> _overlay;
	FabiEngine3D& _fe3d;
};