#pragma once

#include "base_viewport_controller.hpp"
#include "animation3d_editor.hpp"
#include "animation2d_editor.hpp"
#include "sound2d_editor.hpp"
#include "world_editor.hpp"
#include "script_editor.hpp"

class RightViewportController final : public BaseViewportController
{
public:
	using BaseViewportController::inject;

	void inject(shared_ptr<Animation3dEditor> animation3dEditor);
	void inject(shared_ptr<Animation2dEditor> animation2dEditor);
	void inject(shared_ptr<Sound2dEditor> sound2dEditor);
	void inject(shared_ptr<WorldEditor> worldEditor);
	void inject(shared_ptr<ScriptEditor> scriptEditor);
	void inject(shared_ptr<ModelEditor> modelEditor);
	void initialize();
	void update();

private:
	static inline const fvec3 FRAME_COLOR = fvec3(0.175f);
	static inline const fvec3 BUTTON_COLOR = fvec3(0.1f, 0.1f, 1.0f);
	static inline const fvec3 BUTTON_HOVER_COLOR = fvec3(0.5f, 0.5f, 1.0f);
	static inline const fvec3 TEXT_COLOR = fvec3(1.0f);
	static inline const fvec3 TEXT_HOVER_COLOR = fvec3(0.0f);

	static inline constexpr float CW = 0.11f;
	static inline constexpr float CH = 0.085f;

	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<Sound2dEditor> _sound2dEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
};