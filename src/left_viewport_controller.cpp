#define TW(text) calculateTextWidth(text, CW)

#include "left_viewport_controller.hpp"

using LVPC = LeftViewportController;

LeftViewportController::LeftViewportController()
{
	_skyEditor = make_shared<SkyEditor>();
	_terrainEditor = make_shared<TerrainEditor>();
	_waterEditor = make_shared<WaterEditor>();
	_modelEditor = make_shared<ModelEditor>();
	_billboardEditor = make_shared<BillboardEditor>();
	_quadEditor = make_shared<QuadEditor>();
	_animation2dEditor = make_shared<Animation2dEditor>();
	_animation3dEditor = make_shared<Animation3dEditor>();
	_soundEditor = make_shared<SoundEditor>();
	_worldEditor = make_shared<WorldEditor>();
	_scriptEditor = make_shared<ScriptEditor>();
}

void LeftViewportController::inject(shared_ptr<EngineInterface> fe3d)
{
	_skyEditor->inject(fe3d);
	_terrainEditor->inject(fe3d);
	_waterEditor->inject(fe3d);
	_modelEditor->inject(fe3d);
	_billboardEditor->inject(fe3d);
	_quadEditor->inject(fe3d);
	_animation2dEditor->inject(fe3d);
	_animation3dEditor->inject(fe3d);
	_soundEditor->inject(fe3d);
	_worldEditor->inject(fe3d);
	_scriptEditor->inject(fe3d);

	_fe3d = fe3d;
}

void LeftViewportController::inject(shared_ptr<GuiManager> gui)
{
	_skyEditor->inject(gui);
	_terrainEditor->inject(gui);
	_waterEditor->inject(gui);
	_modelEditor->inject(gui);
	_billboardEditor->inject(gui);
	_quadEditor->inject(gui);
	_animation2dEditor->inject(gui);
	_animation3dEditor->inject(gui);
	_soundEditor->inject(gui);
	_worldEditor->inject(gui);
	_scriptEditor->inject(gui);

	_gui = gui;
}

void LeftViewportController::initialize()
{
	_gui->getViewport("left")->createWindow("main", fvec2(0.0f), fvec2(1.9f, 2.0f), LVPC::FRAME_COLOR);
	auto window = _gui->getViewport("left")->getWindow("main");

	auto positions = calculateButtonPositions(11, CH);
	window->createScreen("main");
	window->getScreen("main")->createButton("skyEditor", fvec2(0.0f, positions[0]), fvec2(TW("Sky"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sky", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("terrainEditor", fvec2(0.0f, positions[1]), fvec2(TW("Terrain"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Terrain", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("waterEditor", fvec2(0.0f, positions[2]), fvec2(TW("Water"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Water", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("modelEditor", fvec2(0.0f, positions[3]), fvec2(TW("Model"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Model", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("billboardEditor", fvec2(0.0f, positions[4]), fvec2(TW("Billboard"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Billboard", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("quadEditor", fvec2(0.0f, positions[5]), fvec2(TW("Quad"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Quad", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation2dEditor", fvec2(0.0f, positions[6]), fvec2(TW("Animation2D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation2D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("animation3dEditor", fvec2(0.0f, positions[7]), fvec2(TW("Animation3D"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Animation3D", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("soundEditor", fvec2(0.0f, positions[8]), fvec2(TW("Sound"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Sound", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("worldEditor", fvec2(0.0f, positions[9]), fvec2(TW("World"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "World", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);
	window->getScreen("main")->createButton("scriptEditor", fvec2(0.0f, positions[10]), fvec2(TW("Script"), CH), LVPC::BUTTON_COLOR, LVPC::BUTTON_HOVER_COLOR, "Script", LVPC::TEXT_COLOR, LVPC::TEXT_HOVER_COLOR, true);

	window->setActiveScreen("main");
}

void LeftViewportController::update()
{
	auto window = _gui->getViewport("left")->getWindow("main");
	auto screen = window->getActiveScreen();

	if(screen->getID() == "main")
	{
		if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("skyEditor")->isHovered())
		{
			if(_skyEditor->loadFromFile())
			{
				_skyEditor->load();
				window->setActiveScreen("skyEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("terrainEditor")->isHovered())
		{
			if(_terrainEditor->loadFromFile())
			{
				_terrainEditor->load();
				window->setActiveScreen("terrainEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("waterEditor")->isHovered())
		{
			if(_waterEditor->loadFromFile())
			{
				_waterEditor->load();
				window->setActiveScreen("waterEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("modelEditor")->isHovered())
		{
			if(_modelEditor->loadFromFile())
			{
				_modelEditor->load();
				window->setActiveScreen("modelEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("billboardEditor")->isHovered())
		{
			if(_billboardEditor->loadFromFile())
			{
				_billboardEditor->load();
				window->setActiveScreen("billboardEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("quadEditor")->isHovered())
		{
			if(_quadEditor->loadFromFile())
			{
				_quadEditor->load();
				window->setActiveScreen("quadEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation2dEditor")->isHovered())
		{
			if(_animation2dEditor->loadFromFile(true))
			{
				_animation2dEditor->load();
				window->setActiveScreen("animation2dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("animation3dEditor")->isHovered())
		{
			if(_modelEditor->loadFromFile() && _animation3dEditor->loadFromFile(true))
			{
				_animation3dEditor->load();
				window->setActiveScreen("animation3dEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("soundEditor")->isHovered())
		{
			if(_soundEditor->loadFromFile())
			{
				_soundEditor->load();
				window->setActiveScreen("soundEditorMenuMain");
			}
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("worldEditor")->isHovered())
		{
			_worldEditor->load();
			window->setActiveScreen("worldEditorMenuMain");
		}
		else if(_fe3d->input_isMousePressed(InputType::MOUSE_BUTTON_LEFT) && screen->getButton("scriptEditor")->isHovered())
		{
			if(_scriptEditor->loadScriptFiles(true))
			{
				_scriptEditor->load();
				window->setActiveScreen("scriptEditorMenuMain");
			}
		}
	}

	_skyEditor->update();
	_terrainEditor->update();
	_waterEditor->update();
	_modelEditor->update();
	_billboardEditor->update();
	_quadEditor->update();
	_animation2dEditor->update();
	_animation3dEditor->update();
	_soundEditor->update();
	_worldEditor->update();
	_scriptEditor->update();
}

const shared_ptr<SkyEditor> LeftViewportController::getSkyEditor() const
{
	return _skyEditor;
}

const shared_ptr<TerrainEditor> LeftViewportController::getTerrainEditor() const
{
	return _terrainEditor;
}

const shared_ptr<WaterEditor> LeftViewportController::getWaterEditor() const
{
	return _waterEditor;
}

const shared_ptr<ModelEditor> LeftViewportController::getModelEditor() const
{
	return _modelEditor;
}

const shared_ptr<BillboardEditor> LeftViewportController::getBillboardEditor() const
{
	return _billboardEditor;
}

const shared_ptr<QuadEditor> LeftViewportController::getQuadEditor() const
{
	return _quadEditor;
}

const shared_ptr<Animation2dEditor> LeftViewportController::getAnimation2dEditor() const
{
	return _animation2dEditor;
}

const shared_ptr<Animation3dEditor> LeftViewportController::getAnimation3dEditor() const
{
	return _animation3dEditor;
}

const shared_ptr<SoundEditor> LeftViewportController::getSoundEditor() const
{
	return _soundEditor;
}

const shared_ptr<WorldEditor> LeftViewportController::getWorldEditor() const
{
	return _worldEditor;
}

const shared_ptr<ScriptEditor> LeftViewportController::getScriptEditor() const
{
	return _scriptEditor;
}