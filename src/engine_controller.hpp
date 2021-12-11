#pragma once

#include "fe3d.hpp"
#include "engine_gui_manager.hpp"
#include "top_viewport_controller.hpp"
#include "left_viewport_controller.hpp"
#include "right_viewport_controller.hpp"
#include "bottom_viewport_controller.hpp"

class EngineController final : public FabiEngine3D
{
public:
	EngineController();

	// VOID
	void FE3D_CONTROLLER_INIT();
	void FE3D_CONTROLLER_UPDATE();
	void FE3D_CONTROLLER_TERMINATE();

	// BOOL
	const bool mustPromptOnExit() const;

private:
	// BOOL
	bool _mustPromptOnExit = false;

	// FVEC3
	static inline const fvec3 RENDER_COLOR = fvec3(0.25f);

	// FLOAT
	static inline const float CURSOR_IMAGE_SIZE = 0.075f;

	// MISCELLANEOUS
	EngineGuiManager _gui;
	LeftViewportController _leftViewportController;
	RightViewportController _rightViewportController;
	TopViewportController _topViewportController;
	BottomViewportController _bottomViewportController;
};