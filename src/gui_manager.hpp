#pragma once

#include "engine_interface.hpp"
#include "gui_viewport.hpp"
#include "gui_overlay.hpp"

class GuiManager final
{
public:
	void inject(shared_ptr<EngineInterface> fe3d);
	void construct();
	void updateOverlay();
	void updateViewports();

	const shared_ptr<GuiViewport> getLeftViewport();
	const shared_ptr<GuiViewport> getRightViewport();
	const shared_ptr<GuiViewport> getBottomViewport();
	const shared_ptr<GuiViewport> getTopViewport();
	const shared_ptr<GuiOverlay> getOverlay();

private:
	static inline const fvec3 FRAME_COLOR = fvec3(0.2f);

	static inline const fvec2 LEFT_VIEWPORT_POSITION = fvec2(-0.875f, 0.15f);
	static inline const fvec2 LEFT_VIEWPORT_SIZE = fvec2(0.25f, 1.5f);
	static inline const fvec2 RIGHT_VIEWPORT_POSITION = fvec2(0.875f, 0.15f);
	static inline const fvec2 RIGHT_VIEWPORT_SIZE = fvec2(0.25f, 1.5f);
	static inline const fvec2 BOTTOM_VIEWPORT_POSITION = fvec2(0.0f, -0.8f);
	static inline const fvec2 BOTTOM_VIEWPORT_SIZE = fvec2(2.0f, 0.4f);
	static inline const fvec2 TOP_VIEWPORT_POSITION = fvec2(0.0f, 0.95f);
	static inline const fvec2 TOP_VIEWPORT_SIZE = fvec2(2.0f, 0.1f);

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiViewport> _leftViewport = nullptr;
	shared_ptr<GuiViewport> _rightViewport = nullptr;
	shared_ptr<GuiViewport> _bottomViewport = nullptr;
	shared_ptr<GuiViewport> _topViewport = nullptr;
	shared_ptr<GuiOverlay> _overlay = nullptr;
};