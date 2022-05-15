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
	static inline const string CURSOR_ID = "@@cursor";
	static inline const string CURSOR_DEFAULT_TEXTURE_PATH = "engine\\assets\\image\\diffuse_map\\cursor_default.tga";

	static inline const fvec4 RENDER_COLOR = fvec4(0.0f, 0.0f, 0.0f, 1.0f);

	static inline const fvec2 CURSOR_SIZE = fvec2(0.075f);

	shared_ptr<EngineInterface> _fe3d = nullptr;
	shared_ptr<GuiManager> _guiManager = nullptr;
	shared_ptr<LeftViewportController> _leftViewportController = nullptr;
	shared_ptr<RightViewportController> _rightViewportController = nullptr;
	shared_ptr<BottomViewportController> _bottomViewportController = nullptr;
	shared_ptr<TopViewportController> _topViewportController = nullptr;
	shared_ptr<SkyEditor> _skyEditor = nullptr;
	shared_ptr<TerrainEditor> _terrainEditor = nullptr;
	shared_ptr<WaterEditor> _waterEditor = nullptr;
	shared_ptr<ModelEditor> _modelEditor = nullptr;
	shared_ptr<Quad3dEditor> _quad3dEditor = nullptr;
	shared_ptr<Quad2dEditor> _quad2dEditor = nullptr;
	shared_ptr<Text3dEditor> _text3dEditor = nullptr;
	shared_ptr<Text2dEditor> _text2dEditor = nullptr;
	shared_ptr<Animation3dEditor> _animation3dEditor = nullptr;
	shared_ptr<Animation2dEditor> _animation2dEditor = nullptr;
	shared_ptr<AabbEditor> _aabbEditor = nullptr;
	shared_ptr<PointlightEditor> _pointlightEditor = nullptr;
	shared_ptr<SpotlightEditor> _spotlightEditor = nullptr;
	shared_ptr<Sound3dEditor> _sound3dEditor = nullptr;
	shared_ptr<Sound2dEditor> _sound2dEditor = nullptr;
	shared_ptr<WorldEditor> _worldEditor = nullptr;
	shared_ptr<ScriptEditor> _scriptEditor = nullptr;
	shared_ptr<CustomWorldBuilder> _customWorldBuilder = nullptr;
	shared_ptr<Duplicator> _duplicator = nullptr;
	shared_ptr<Script> _script = nullptr;
	shared_ptr<ScriptExecutor> _scriptExecutor = nullptr;
	shared_ptr<ScriptInterpreter> _scriptInterpreter = nullptr;
};