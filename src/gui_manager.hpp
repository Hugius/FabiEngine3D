#pragma once

#include "engine_interface.hpp"
#include "gui_viewport.hpp"
#include "gui_overlay.hpp"

class GuiManager final
{
public:
	GuiManager(EngineInterface& fe3d);

	void update();

	shared_ptr<GuiViewport> getViewport(const string& ID);
	shared_ptr<GuiOverlay> getOverlay();

	static inline const fvec3 FRAME_COLOR = fvec3(0.025f);

private:
	vector<shared_ptr<GuiViewport>> _viewports;
	shared_ptr<GuiOverlay> _overlay;
	EngineInterface& _fe3d;
};