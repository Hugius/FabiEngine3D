#pragma once

#include "engine_interface.hpp"
#include "gui_viewport.hpp"
#include "gui_overlay.hpp"

class GuiManager final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void initialize();
	void update();

	const shared_ptr<GuiViewport> getLeftViewport();
	const shared_ptr<GuiViewport> getRightViewport();
	const shared_ptr<GuiViewport> getBottomViewport();
	const shared_ptr<GuiViewport> getTopViewport();
	const shared_ptr<GuiOverlay> getOverlay();

private:
	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiViewport> _leftViewport = nullptr;
	shared_ptr<GuiViewport> _rightViewport = nullptr;
	shared_ptr<GuiViewport> _bottomViewport = nullptr;
	shared_ptr<GuiViewport> _topViewport = nullptr;
	shared_ptr<GuiOverlay> _overlay = nullptr;

	static inline const fvec3 FRAME_COLOR = fvec3(0.025f);
};