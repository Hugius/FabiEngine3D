#pragma once

#include "engine_interface.hpp"
#include "gui_manager.hpp"
#include "top_viewport_controller.hpp"
#include "left_viewport_controller.hpp"
#include "right_viewport_controller.hpp"
#include "bottom_viewport_controller.hpp"

class EngineController final
{
public:
	EngineController();

	void inject(shared_ptr<EngineInterface> fe3d);

	void initialize();
	void update();
	void terminate();

private:
	bool _mustPromptOnExit = false;

	static inline const fvec4 RENDER_COLOR = fvec4(0.25f, 0.25f, 0.25f, 1.0f);

	static inline const float CURSOR_QUAD_SIZE = 0.075f;

	shared_ptr<EngineInterface> _fe3d = nullptr;

	shared_ptr<GuiManager> _guiManager;
	shared_ptr<LeftViewportController> _leftViewportController;
	shared_ptr<RightViewportController> _rightViewportController;
	shared_ptr<TopViewportController> _topViewportController;
	shared_ptr<BottomViewportController> _bottomViewportController;
};