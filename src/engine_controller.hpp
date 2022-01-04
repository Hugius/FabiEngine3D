#pragma once

#include "fe3d.hpp"
#include "gui_manager.hpp"
#include "top_viewport_controller.hpp"
#include "left_viewport_controller.hpp"
#include "right_viewport_controller.hpp"
#include "bottom_viewport_controller.hpp"

class EngineController final : public FabiEngine3D
{
public:
	EngineController();

	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE();
	void FE3D_CONTROLLER_TERMINATE();

	const bool mustPromptOnExit() const;

private:
	bool _mustPromptOnExit = false;

	static inline const fvec4 RENDER_COLOR = fvec4(0.25f, 0.25f, 0.25f, 1.0f);

	static inline const float CURSOR_QUAD_SIZE = 0.075f;

	GuiManager _gui;
	LeftViewportController _leftViewportController;
	RightViewportController _rightViewportController;
	TopViewportController _topViewportController;
	BottomViewportController _bottomViewportController;
};